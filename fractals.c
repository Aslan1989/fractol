/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisaev <aisaev@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:18:33 by aisaev            #+#    #+#             */
/*   Updated: 2025/06/04 15:13:12 by aisaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief Calculates number of iterations for
 * a fractal point (Julia or Mandelbrot).
 * calculates how fast a complex number escapes
 * @param z_re Starting real part of z.
 * @param z_im Starting imaginary part of z.
 * @param c_re Real part of constant c.
 * @param c_im Imaginary part of constant c.
 * @return Number of iterations before escaping.
 */
int	calculate_fractal(double z_re, double z_im, double c_re, double c_im)
{
	int		i;
	double	old_re;
	double	old_im;

	i = 0;
	while (z_re * z_re + z_im * z_im <= 4 && i < MAX_ITER)
	{
		old_re = z_re;
		old_im = z_im;
		z_re = old_re * old_re - old_im * old_im + c_re;
		z_im = 2 * old_re * old_im + c_im;
		i++;
	}
	return (i);
}

/**
 * @brief Draws one pixel of the Mandelbrot set.
 *
 * Converts screen coordinates (x, y) to complex plane coordinates.
 * Then calculates the color and draws the pixel.
 * scales the coordinates, depending on the zoom
 * allows you to move the "camera" along the fractal
 * If the point escaped, calculate its color based on
 * the number of iterations.
 * Draw the pixel with the calculated color.
 * @param f Pointer to the fractal structure.
 * @param x X position on the screen.
 * @param y Y position on the screen.
 */
static void	mandelbrot_pixel(t_fractol *f, int x, int y)
{
	double	real_part;
	double	imag_part;
	int		i;
	int		color;

	real_part = (x - WIDTH / 2.0) / (0.5 * f->zoom * WIDTH) + f->shift_x;
	imag_part = (y - HEIGHT / 2.0) / (0.5 * f->zoom * HEIGHT) + f->shift_y;
	i = calculate_fractal(0.0, 0.0, real_part, imag_part);
	color = 0;
	if (i < f->iterations_limits)
		color = get_color(i, MAX_ITER, f->color_scheme);
	put_pixel(f, x, y, color);
}

/**
 * @brief Draws one pixel of the Julia set.
 *
 * Converts screen coordinates (x, y) to complex coordinates.
 * Then calculates the color and draws the pixel on the image.
 * Calculate the pixel’s color depending on how fast it escaped
 * @param f Pointer to the fractal structure.
 * @param x X position on the screen.
 * @param y Y position on the screen.
 */
static void	julia_pixel(t_fractol *f, int x, int y)
{
	double	real_part;
	double	imag_part;
	int		i;
	int		color;

	real_part = (x - WIDTH / 2.0) / (0.5 * f->zoom * WIDTH) + f->shift_x;
	imag_part = (y - HEIGHT / 2.0) / (0.5 * f->zoom * HEIGHT) + f->shift_y;
	i = calculate_fractal(real_part, imag_part, f->const_real, \
		f->const_imaginary);
	color = 0;
	if (i < f->iterations_limits)
		color = get_color(i, MAX_ITER, f->color_scheme);
	put_pixel(f, x, y, color);
}

/**
 * @brief Draws the full Mandelbrot fractal.
 *
 * Goes through all pixels and draws each one using mandelbrot_pixel.
 * Start drawing at the top-left of the window.
 * Loop over every row
 * @param f Pointer to the fractal structure.
 */
void	draw_mandelbrot(t_fractol *f)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mandelbrot_pixel(f, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx, f->window, f->img, 0, 0);
}

/**
 * @brief Draws the full Julia fractal.
 *
 * Goes through all pixels and draws each one using julia_pixel.
 * After all pixels are drawn into memory,
 * puts the image on the screen.
 * @param f Pointer to the fractal structure.
 */
void	draw_julia(t_fractol *f)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			julia_pixel(f, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx, f->window, f->img, 0, 0);
}
