/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:50:29 by lbattest          #+#    #+#             */
/*   Updated: 2022/06/22 11:22:43 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_map(t_data *data)
{
	int		x;
	int		y;
	t_obj	obj;
	char	**map;

	map = data->map.map;
	y = -1;
	obj.spawn = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '1' && map[y][x + 1] != ' ')
				obj.wall = 1;
			if (map[y][x] == '1' && map[y][x + 1] == ' ')
				obj.wall = 0;
			if (map[y][x] == 'N')
			{
				obj.spawn++;
				puts("spawn");
			}
			if (obj.wall == 1 && map[y][x] == ' ')
				puts("espace entre mur");
			if (map[y][x] != '1' && data->map.map[y][x] != '0' &&
			data->map.map[y][x] != 'N' && data->map.map[y][x] != ' ')
				puts("mauvais charactere");
			if (obj.spawn > 1)
				puts("trop de spawn");
			// if ((obj.wall == 1 && map[y][x] == ' ') ||
			// (map[y][x] != '1' && data->map.map[y][x] != '0' &&
			// data->map.map[y][x] != 'N' && data->map.map[y][x] != ' ') ||
			// obj.spawn > 1)
			// 	error("Error\nInvalid map", 1);
		}
	}
}

static void	get_player_orientation(t_data *data, char c)
{
	if (c == 'N')
		data->player.orientation = NORTH;
	else if (c == 'W')
		data->player.orientation = WEST;
	else if (c == 'S')
		data->player.orientation = SOUTH;
	else if (c == 'E')
		data->player.orientation = EAST;
	else
	{
		ft_putstr_fd("Invalid map\n", 2);
		exit(0); // à faire proprement
	}
}

static void	fill_map(t_data *data, int line_nbr, t_list *tmp_map)
{
	t_list	*tmp_ptr;
	int		i;
	int		j;

	i = 0;
	data->map.map = malloc(sizeof(char *) * (line_nbr + 1));
	while (i < line_nbr)
	{
		j = 0;
		data->map.map[i] = tmp_map->content;
		while (data->map.map[i][j])
		{
			if (ft_isalpha(data->map.map[i][j]))
			{
				data->player.pos_x = j;
				data->player.pos_y = i;
				get_player_orientation(data, data->map.map[i][j]);
				data->map.map[i][j] = '0';
			}
			j++;
		}
		tmp_map = tmp_map->next;
		i++;
	}
	data->map.map[i] = NULL;
	ft_lstclear(&tmp_ptr, NULL);
}

void	get_map(int fd, t_data *data)
{
	t_list	*tmp_map;
	t_list	*new_elem;
	char	*line;
	int		line_nbr;

	line_nbr = 0;
	tmp_map = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		new_elem = ft_lstnew(line);
		if (!new_elem)
		{
			free(line);
			error("", 0);
		}
		ft_lstadd_back(&tmp_map, new_elem);
		line_nbr++;
	}
	fill_map(data, line_nbr, tmp_map);
}
