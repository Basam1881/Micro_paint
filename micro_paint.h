#ifndef MICRO_PAINT_H
# define MICRO_PAINT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_rect
{
	char	*path;
	char	**str;
	FILE	*fd;
	int		b_width, b_hight;
	float	x, y, width, hight;
	char	b_c, c, fill_flag;
}				t_rect;

#endif