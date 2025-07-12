/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisaev <aisaev@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:19:17 by aisaev            #+#    #+#             */
/*   Updated: 2025/06/05 10:43:42 by aisaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief Handles mouse actions like zooming in and out.
 *
 * Uses the scroll wheel to zoom and updates the offset.
 * Update the position so zoom follows the mouse.
 * Redraws the fractal after zooming.
 *
 * @param button The mouse button pressed.
 * @param x X position of the mouse.
 * @param y Y position of the mouse.
 * @param f Pointer to the fractal structure.
 * @return Always returns 0.
 */
int	mouse_hook(int button, int x, int y, t_fractol *f)
{
	if (button == 4)
		f->zoom *= 1.1;
	else if (button == 5)
		f->zoom /= 1.1;
	else
		return (0);
	f->shift_x += (x - WIDTH / 2.0) / (WIDTH * f->zoom) / 2;
	f->shift_y += (y - HEIGHT / 2.0) / (HEIGHT * f->zoom) / 2;
	if (ft_strcmp(f->type, "mandelbrot") == 0)
		draw_mandelbrot(f);
	else if (ft_strcmp(f->type, "julia") == 0)
		draw_julia(f);
	return (0);
}

/**
 * @brief Returns a color based on the number of iterations.
 *
 * Uses different color schemes depending on the selected mode.
 *
 * @param iter Number of iterations for the pixel.
 * @param max_iter Maximum number of iterations.
 * @param scheme Selected color scheme number.
 * @return An integer representing the color.
 */
int	get_color(int iter, int max_iter, int scheme)
{
	if (iter == max_iter)
		return (0x000000);
	if (scheme == 0)
		return (iter * 0x045611);
	else if (scheme == 1)
		return (iter * 0x1E90FF);
	else if (scheme == 2)
		return (iter * 0x8A2BE2);
	else if (scheme == 3)
		return (iter * 0xFF4500);
	else if (scheme == 4)
		return (iter * 0x00FF7F);
	else if (scheme == 5)
		return (iter * 0xFFD700);
	else if (scheme == 6)
		return (iter * 0xFF1493);
	else if (scheme == 7)
		return (iter * 0x00CED1);
	return (0x000000);
}

/**
 * @brief Redraws the fractal only if needed.
 * Called many times per second. called constantly
 * Checks if "needs_redraw" is set and calls the right draw function.
 * Only redraw if the image has changed
 * Draw the right fractal
 * Reset the flag so we don’t keep redrawing
 * @param f Pointer to the fractal structure.
 * @return Always returns 0.
 */
int	loop_hook(t_fractol *f)
{
	if (f->needs_redraw)
	{
		if (ft_strcmp(f->type, "mandelbrot") == 0)
			draw_mandelbrot(f);
		else if (ft_strcmp(f->type, "julia") == 0)
			draw_julia(f);
		f->needs_redraw = 0;
	}
	return (0);
}

/**
 * @brief Handles keyboard input for controls.
 *
 * Supports arrow keys for moving, plus/minus for iterations,
 * and ESC to close the window.
 * Mark that the screen needs to be updated
 * @param keycode The key that was pressed.
 * @param f Pointer to the fractal structure.
 * @return Always returns 0.
 */
int	key_hook(int keycode, t_fractol *f)
{
	if (keycode == KEY_ESC)
		close_window(f);
	else if (keycode == KEY_LEFT)
		f->shift_x -= 0.15 / f->zoom;
	else if (keycode == KEY_RIGHT)
		f->shift_x += 0.15 / f->zoom;
	else if (keycode == KEY_DOWN)
		f->shift_y += 0.15 / f->zoom;
	else if (keycode == KEY_UP)
		f->shift_y -= 0.15 / f->zoom;
	else if (keycode == KEY_C)
		f->color_scheme = (f->color_scheme + 1) % 8;
	else if (keycode == KEY_PLUS)
		f->iterations_limits += 10;
	else if (keycode == KEY_MINUS)
		f->iterations_limits -= 10;
	f->needs_redraw = 1;
	return (0);
}

/**
 * @brief Puts a pixel with a specific color on the image.
 * Calculates the pixel’s memory position and writes the color there
 * The start address of the image in memory
 * (where all pixels are stored)
 * How many bytes to skip to go to row number y in the image
 * How many bytes to skip in that row to go to pixel number x
 * Bits per pixel — how many bits one pixel uses (for example, 32 bits)
 * @param f Pointer to the fractal structure.
 * @param x X position on the screen.
 * @param y Y position on the screen.
 * @param color The color value to draw.
 */
void	put_pixel(t_fractol *f, int x, int y, int color)
{
	char	*dst;

	dst = f->addr + (y * f->line_len + x * (f->bpp / 8));
	*(unsigned int *)dst = color;
}
