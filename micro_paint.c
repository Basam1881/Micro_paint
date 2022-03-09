#include "micro_paint.h"


void	draw(t_rect *rect)
{
	int	i = 0, j;
	while (i < rect->b_hight)
	{
		j = 0;
		while (j < rect->b_width)
		{
			write(1, &rect->str[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		rect->str[i][j] = 0;
		i++;
	}
	rect->str[i] = NULL;
}

void	store_line(t_rect *rect)
{
	int	y = 0, x;
	while (y < rect->b_hight)
	{
		x = 0;
		while (x < rect->b_width)
		{
			if (x >= rect->x && x <= rect->x + rect->width && y >= rect->y && y <= rect->y + rect->hight)
			{
				if (x - rect->x >= 1 && rect->x + rect->width - x >= 1 && y - rect->y >= 1 && rect->y + rect->hight - y >= 1)
				{
					if (rect->fill_flag == 'R')
						rect->str[y][x] = rect->c;
				}
				else 
					rect->str[y][x] = rect->c;
			}
			x++;
		}
		y++;
	}
}

int	check_lines(t_rect *rect)
{
	int	parms = 0;
	while (1)
	{
		parms = fscanf(rect->fd, "%c %f %f %f %f %c\n", &rect->fill_flag, &rect->x, &rect->y, &rect->width, &rect->hight, &rect->c);
		if (parms == -1)
			break ;
		if (parms != 6)
			return (1);
		if ((rect->b_c == 'R' && rect->b_c == 'r') || rect->width <= 0 || rect->hight <= 0)
			return (1);
		store_line(rect);
	}
	return (0);
}

void	main_store(t_rect *rect)
{
	int	i = 0, j;
	while (i < rect->b_hight)
	{
		j = 0;
		while (j < rect->b_width)
		{
			rect->str[i][j]= rect->b_c;
			j++;
		}
		rect->str[i][j] = 0;
		i++;
	}
	rect->str[i] = NULL;
}

int	file_reader(t_rect *rect)
{
	int i = 0;
	rect->fd = fopen(rect->path, "r");
	if (!rect->fd)
		return (1);
	if (fscanf(rect->fd, "%d %d %c\n", &rect->b_width, &rect->b_hight, &rect->b_c) == 3)
	{
		if (rect->b_width <= 0 || rect->b_width > 300 || rect->b_hight <= 0 || rect->b_hight > 300)
			return (1);
		rect->str = (char **)malloc(sizeof(char *) * (rect->b_hight + 1));
		if (!rect->str)
			return (1);
		while (i < rect->b_hight)
		{
			rect->str[i] = (char *)malloc(sizeof(char) * (rect->b_width + 1));
			if (!rect->str[i])
				return (1);
			i++;
		}
		main_store(rect);
		if (check_lines(rect))
			return (1);
		draw(rect);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_rect rect;
	if (ac != 2)
	{
		write (1, "Error: argument\n", 16);
		return (1);
	}
	rect.path = av[1];
	if (file_reader(&rect))
	{
		write (1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	return (0);
}