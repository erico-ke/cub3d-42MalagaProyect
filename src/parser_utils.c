/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:00:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/12/23 10:06:32 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	parse_color(t_plane *plane)
{
	plane->ccolor = (plane->c_red << 24) | (plane->c_green << 16)
		| (plane->c_blue << 8) | 255;
	plane->fcolor = (plane->f_red << 24) | (plane->f_green << 16)
		| (plane->f_blue << 8) | 255;
}

char	*read_map_lines(int fd, t_data *data)
{
	char	*line;
	char	*map_content;

	map_content = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == ' ' || line[0] == '\t' || ft_isdigit(line[0])
			|| line[0] == '1')
			map_content = ft_strjoin_g(map_content, line);
		else if (!textures_n_colors(line, data))
			return (free(line), NULL);
		free(line);
		line = get_next_line(fd);
	}
	return (map_content);
}
