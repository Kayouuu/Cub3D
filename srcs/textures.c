/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:18:05 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/23 12:57:57 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	loader(t_data *data, t_orientation orien, char *path)
{
	if (path[ft_strlen(path) - 1] == '\n')
		path[ft_strlen(path) - 1] = '\0';
	data->text[orien].img = mlx_xpm_file_to_image(data->mlx.mlx,
			path, &data->text[orien].img_width, &data->text[orien].img_height);
	if (data->text[orien].img == NULL)
	{
		ft_putendl_fd("Error\nTexture not found", 2);
		exit(1); // à faire proprement
	}
	data->text[orien].addr = (int *)mlx_get_data_addr(
			data->text[orien].img, &data->text[orien].bits_per_pixel,
			&data->text[orien].size_line,
			&data->text[orien].endian);
	if (!is_power_of_two(data->text[orien].img_width)
		|| !is_power_of_two(data->text[orien].img_height))
	{
		ft_putendl_fd("Error\nOne of the texture don't have the good resolution", 2);
		exit(0); // à faire proprement
	}
}

void	load_textures(t_data *data)
{
	data->text = malloc(sizeof(t_text) * 4);
	if (!data->text)
	{
		// free
		exit(1);
	}
	loader(data, NORTH, data->sprites.no);
	loader(data, WEST, data->sprites.we);
	loader(data, EAST, data->sprites.ea);
	loader(data, SOUTH, data->sprites.so);
}

void	apply_textures(t_data *data)
{
	int	i;
	int	j;
	int	y;

	j = 0;
	while (j < 4)
	{
		y = 0;
		while (y < data->text[j].img_width)
		{
			i = 0;
			while (i < data->text[j].img_height)
			{
				data->texture[j][data->text[j].img_width
					* y + i] = data->text[j].addr[data->text[j].img_width
					* y + i];
				i++;
			}
			y++;
		}
		j++;
	}
}
