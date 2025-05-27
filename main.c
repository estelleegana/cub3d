#include "cub3d.h"

void print_all_data(void)
{
	t_config *conf = s();
	printf("Map:\n");
	for (int i = 0; i < conf->map.line; i++)
	{
		for (int j = 0; j < conf->map.columns; j++)
			printf("%c", conf->map.data[i][j]);
		printf("\n");
	}
	printf("Player position: (%f, %f)\n", conf->p.X, conf->p.Y);
	printf("Player direction: (%f, %f)\n", conf->p.dirX, conf->p.dirY);
	printf("Player plane: (%f, %f)\n", conf->p.planeX, conf->p.planeY);

}

int main(int argc , char *argv[])
{
	(void)argv;
	(void)argc;
	if(argc != 2)
		return (write(2,"Error // Wrong number of arguments\n", 35), 1);
	if(!parse_cub(argv[1]))
		return (write(2,"Error // Invalid .cub file\n", 27), 1);
	init_player();
	print_all_data();
	init_game();
	free_map();
	free_textures();
	return (0);
}