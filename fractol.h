/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisaev <aisaev@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:25:12 by aisaev            #+#    #+#             */
/*   Updated: 2025/07/04 15:48:26 by aisaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <string.h>

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 150

# define KEY_ESC 53
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_C 8

// Byte order (endianness) of the image
// The address of the beginning of the
// pixel data of the image
// image color depth
// Number of bytes per image line (width in bytes)
typedef struct s_fractol
{
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	double	zoom;
	double	shift_x;
	double	shift_y;
	char	*type;
	double	const_real;
	double	const_imaginary;
	int		color_scheme;
	int		needs_redraw;
	int		iterations_limits;
}	t_fractol;

void	put_pixel(t_fractol *f, int x, int y, int color);
void	draw_mandelbrot(t_fractol *f);
void	draw_julia(t_fractol *f);
int		mouse_hook(int button, int x, int y, t_fractol *f);
int		key_hook(int keycode, t_fractol *f);
int		close_window(t_fractol *f);
int		loop_hook(t_fractol *f);
int		get_color(int i, int max_iter, int scheme);
#endif
