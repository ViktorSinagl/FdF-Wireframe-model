#include "../includes/fdf.h"
#include <unistd.h>

int	window_init(t_metadata *meta)
{
	meta->mlx = mlx_init();
	if (meta->mlx == NULL)
	{
		my_aterror(meta);
		(put_err_fd(MLX_MLX, 2), exit(2));
	}
	meta->win = mlx_new_window(meta->mlx, WIDTH, HEIGHT, "Good grade plz :)");
	if (meta->win == NULL)
	{
		my_aterror(meta);
		(put_err_fd(MLX_WIN, 2), exit(2));
	}
	meta->img.img = create_img(meta->mlx);
	if (meta->img.img == NULL)
	{
		my_aterror(meta);
		mlx_destroy_window(meta->mlx, meta->win);
		(put_err_fd(MLX_IMG, 2), exit(2));
	}
	meta->img.addr = mlx_get_data_addr(meta->img.img,
								&meta->img.bits_per_pixel,
								&meta->img.line_length,
								&meta->img.endian);
	return(0);
}

int	process_args(int argc, char **argv, t_metadata *meta)
{
	int	fd;

	if (argc != 2)
		(put_err_fd(ERR_ARG, 2), exit(1));
	fd = open(argv[1],O_RDONLY);
	if (fd < 0)
		(put_err_fd(ERR_READ, 2), exit(1));
	meta->map = create_map(fd, argv);
	if (meta->map == NULL)
		(put_err_fd(ERR_MAP, 2), exit(1));
	meta->matrix_len = meta->map->n_lines * meta->map->n_cols;
	printf("%i ...\n", meta->matrix_len);
	meta->izo_matrix = (t_point*)malloc(sizeof(t_point) * meta->map->n_lines * meta->map->n_cols);
	meta->dim_matrix = (t_point*)malloc(sizeof(t_point) * meta->map->n_lines * meta->map->n_cols);
	return(0);
}

int	init_metadata(t_metadata *meta)
{
	create_menu(meta);
	//create_menu(meta, &meta->menu_img2, "misc/menu_dimetric.xpm");
	return(0);
}

/*
void	create_menu(t_metadata *meta)
{
	meta->menu_izo = mlx_xpm_file_to_image(meta->mlx, "misc/menu_izo", &meta->picture_w, &meta->picture_h);
	if (meta->menu_izo == NULL)
		(put_err_fd(MLX_MENU, 2), exit(2));
	meta->menu_izo = mlx_xpm_file_to_image(meta->mlx, "misc/menu_izo", &meta->picture_w, &meta->picture_h);
}
*/


//hooking strategy:
/*
 * > map can be updated, so i will call update functions.
 * > > check that init function initialize all the needed structures and matrix. There will be one matrix containg 2D draw coordinates for basic view(e.g izometric, dimetric) and second one with updated values.
 * > > update function update the map-> matrix on based parametrs(angles,at first run  it will upate map based on default value in metadata.
 *			THIS FUNCTION SHOUDL BE THEN CALLED IN MLX_HOOK
 *	
	then the function for drawing is called also in mlx_hhok
 *
 * > after key pressed, the parametrs(angle, zoom, sidelen etc.) is updated, then map drawn (for angle) then matrix computed and then matrix drawn!.
 STEPS:
 3D coordinates transformation --> transform to 2D coordinates(create 2D view of 3D object) --> draw mesh on screen
 * >  free and clear actual image
 * > create new image
 * > draw image
 *

 *
 */
int	hook(void *param)
{
	t_metadata *meta;

	meta = param;
	//printf("loping %p\n", meta->map);
	if (meta == NULL)
		printf("what the hack\n");
	
	return(0);
}

int	run_program(t_metadata *meta)
{
	//t_point *matrix;
	printf("running program...\n");
	meta->izo_matrix = izometric3D(meta->map, meta->izo_matrix, meta->map->x_offset, meta->map->y_offset);
	printf("na hovnov\n");
	meta->p_matrix = meta->izo_matrix;
	printf("na hovno 2\n");
	draw_mesh2(meta);
	printf("na hovno 3\n");
	offset_matrix(meta, 10, 10);
	printf("na hovno 4\n");
	draw_mesh2(meta);
	sleep(2);
	printf("na hovno 5\n");
	printf("meta->mlx %p\n", meta->mlx);
	printf("meta->win %p\n", meta->win);
	printf("meta->img %p\n", meta->img.img);
//	mlx_put_image_to_window(meta->mlx, meta->win, meta->img.img, MENUWIDTH + 60, 0);
	printf("na hovno 6\n");
//	mlx_put_image_to_window(meta->mlx, meta->win, meta->menu_izo, 50, 0);
	printf("x_offset: %i\n", meta->map->x_offset);
	sleep(2);
	mlx_key_hook(meta->win, close_program, &meta);
	mlx_loop_hook(meta->mlx, &hook, meta);
	mlx_loop(meta->mlx);
	printf("session succesfully ended\n");
	return(0);
}

int main(int argc, char **argv)
{
	t_metadata	meta;

	process_args(argc, argv, &meta);
	window_init(&meta);
	create_menu(&meta);
	//handle_erros(err);
	run_program(&meta);
	return(0);

}
