/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisaev <aisaev@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:32:12 by aisaev            #+#    #+#             */
/*   Updated: 2025/06/12 15:12:12 by aisaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
/**
 * @brief Initializes the MLX graphics window and image.
 * prepares the graphics window and image
 * Sets up MLX, creates a window, and prepares image memory.
 * Create an image and get access to its pixel data
 * gets information about the image buffer in memory
 * This will point to the start of the image data (pixels in memory)
 * This will store bits per pixel (for example, 32 bits = 4 bytes)
 * This will store the number of bytes per row (line) in the image
 * This will store information about byte order (endianness)
 * @param f Pointer to the fractal structure.
 * @return 1 if successful, 0 if there was an error.
 */
int	init_mlx(t_fractol *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
	{
		ft_printf("Error: mlx_init() failed\n");
		return (0);
	}
	f->window = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fract'ol");
	if (!f->window)
	{
		ft_printf("Error: mlx_new_window() failed\n");
		return (0);
	}
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	f->addr = mlx_get_data_addr(f->img, &f->bpp, &f->line_len, &f->endian);
	f->zoom = 1.0;
	f->shift_x = 0.0;
	f->shift_y = 0.0;
	f->iterations_limits = 50;
	f->color_scheme = 0;
	return (1);
}

int	is_valid_float(const char *str)
{
	int	i = 0;
	int	dot_count = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0); // пустая строка после знака
	while (str[i])
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (dot_count > 1)
				return (0); // больше одной точки
		}
		else if (!ft_isdigit(str[i]))
			return (0); // не цифра и не точка
		i++;
	}
	return (1);
}
/**
 * @brief Initializes Julia set values from command line.
 * Get Julia constants from the command line.
 * Reads the constants for the Julia fractal from command-line input
 * Parses the real and imaginary values of the constant c.
 * Save the real and imaginary parts of the Julia constant
 * @param f Pointer to the fractal structure.
 * @param argc Argument count.
 * @param argv Argument values.
 * @return 1 if successful, 0 if arguments are wrong.
 */
static int	init_julia(t_fractol *f, int argc, char *argv[])
{
	if (argc != 4)
	{
		ft_printf("Error: Julia requires two parameters (c_re and c_im)\n");
		return (0);
	}
	if (!is_valid_float(argv[2]) || !is_valid_float(argv[3]))
	{
		ft_printf("Error: Invalid float format for Julia parameters.\n");
		return (0);
	}
	f->const_real = ft_atof(argv[2]);
	f->const_imaginary = ft_atof(argv[3]);
	return (1);
}

int	close_window(t_fractol *f)
{
	if (f->img)
		mlx_destroy_image(f->mlx, f->img);
	if (f->window)
		mlx_destroy_window(f->mlx, f->window);
	exit(0);
	return (0);
}

/*
 * https://www.geogebra.org/m/mfewjrek
 * custom structure to store the fractal state
 * Creates a structure f to store fractal settings and data
 * Saves the type of fractal chosen by the user
 * Initializes the graphics window and fractal values.
 * Sets a function to handle keyboard input
 * Sets a function to handle mouse actions
 * Updates the image only when needed
 * The program keeps running and waits for user actions
*/
int	main(int argc, char *argv[])
{
	t_fractol	f;

	if (!((argc == 2 && ft_strcmp(argv[1], "mandelbrot") == 0) ||
		(argc == 4 && ft_strcmp(argv[1], "julia") == 0)))
	{
		ft_printf("Usage:\n ./fractol mandelbrot\n ./fractol julia <real> <imag>\n");
		return (1);
	}
	f.type = argv[1];
	if (!init_mlx(&f))
		return (1);
	if (ft_strcmp(argv[1], "julia") == 0 && !init_julia(&f, argc, argv))
		return (1);
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		draw_mandelbrot(&f);
	else
		draw_julia(&f);
	mlx_key_hook(f.window, key_hook, &f);
	mlx_mouse_hook(f.window, mouse_hook, &f);
	mlx_loop_hook(f.mlx, loop_hook, &f);
	mlx_hook(f.window, 17, 0, close_window, &f);
	mlx_loop(f.mlx);
	return (0);
}
