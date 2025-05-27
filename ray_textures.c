#include "cub3d.h"

// void put_tex_NSEW(int NSEW, int hauteur, int x, int y, int tex_x)
// {
//     // int relative_y = y - (HEIGHT / 2 - hauteur / 2);  // position dans la colonne (0 -> hauteur colonne)
//     // int tex_y = relative_y % s()->t[NSEW].h;  // reboucle verticalement
//     // if (tex_y < 0)
//     //     tex_y += s()->t[NSEW].h;
//     // int i = tex_y * s()->t[NSEW].line_len + tex_x * (s()->t[NSEW].bpp / 8);
//     // int color = *(int *)(s()->t[NSEW].addr + i);

//     // put_pixel(x, y, color, s());

//     int texY = (int)texPos & (texture->h - 1);
//     texPos += step;
//     int color = *(int *)(texture->addr + (texY * texture->line_len + texX * (texture->bpp / 8)));
//     put_pixel(x, y, color, s());
// }