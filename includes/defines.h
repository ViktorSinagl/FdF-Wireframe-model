/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 08:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/05/31 17:18:15 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

//error messages
# define ERR_ARG	"Error: wrong number of arguments\n"
# define MLX_ADD	"Error : mlx_get_data_addr error\n"
# define ERR_OPEN	"Error : Error opening the file\n"
# define ERR_READ	"Error : Error reading the file\n"
# define ERR_FILE	"Error : Unsuported filetype\n"
# define MLX_MLX	"Error : mlx_connection\n"
# define MLX_WIN	"Error : mlx_new_window error\n"
# define MLX_IMG	"Error : mlx_new_image error\n"
# define MLX_MENU	"Error : mlx_img for side menu error\n"
# define ERR_MAL	"Error : malloc error\n"
# define ERR_MAP	"Error : map reading, source file is probably corrupted\n"

# define WIDTH		1920
# define HEIGHT		1080
# define MENUWIDTH	400
# define DEFAULTCOLOR 0xFFFFFF
# define DEFAULTSIDELEN	15
# define DEF_MOVE 45
# define DEF_ROT 90
# define DEF_ZOOM 5

# define ESC		65307
# define UP			65362
# define DOWN		65364
# define RIGHT		65363
# define LEFT		65361

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	ovalue;
}	t_color;

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}	t_point;

typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_imgdata;

typedef struct s_element
{
	float	x;
	float	y;
	float	z;
	float	color;
}	t_element;

typedef struct s_map2
{
	t_element	*matrix;
	int			n_lines;
	int			n_cols;
	int			sidelen;
	int			az;
	int			x_offset;
	int			y_offset;
}	t_map2;

typedef struct s_metadata
{
	void		*mlx;
	void		*win;
	t_imgdata	img;
	t_map2		*map;
	t_point		*p_matrix;
	void		*menu_izo;
	void		*menu_2;
	void		*menu_3;
	int			picture_w;
	int			picture_h;
	int			matrix_len;
	int			projection;
	float		camera_angle;
	int			end;
}	t_metadata;

typedef struct s_mappoint
{
	int					x;
	int					y;
	int					z;
	int					color;
	struct s_mappoint	*next;
}	t_mappoint;

typedef struct s_diff
{
	int	x;
	int	y;
	int	po;
	int	inc;
	int	step;
}	t_diff;

typedef struct s_points
{
	t_point	a;
	t_point	b;
}	t_points;

#endif
