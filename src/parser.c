/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:00:00 by fracurul          #+#    #+#             */
/*   Updated: 2025/12/26 08:57:34 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	process_line(char *line, t_data *data, char **map_content)
{
	if (line[0] == ' ' || line[0] == '\t' || ft_isdigit(line[0])
		|| line[0] == '1')
	{
		*map_content = ft_strjoin_g(*map_content, line);
		return (1);
	}
	return (textures_n_colors(line, data));
}

int	read_cub(const char *filecub, t_data *data)
{
	int		fd;
	char	*line;
	char	*map_content;

	fd = open(filecub, O_RDONLY);
	line = get_next_line(fd);
	map_content = NULL;
	if (fd < 0)
		return (ft_printf("Error opening file\n"), 1);
	while (line)
	{
		if (!process_line(line, data, &map_content))
			return (free(line), close(fd), 1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!map_content)
		return (ft_printf("No map found in file\n"), 1);
	data->map = ft_split(map_content, '\n');
	free(map_content);
	return (1);
}

int	textures_n_colors(char *line, t_data *data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (validate_texture(&data->plane->no_texture, line + 3, "North"));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (validate_texture(&data->plane->so_texture, line + 3, "South"));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (validate_texture(&data->plane->we_texture, line + 3, "West"));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (validate_texture(&data->plane->ea_texture, line + 3, "East"));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color_line(line + 2, data->plane, "floor"));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color_line(line + 2, data->plane, "ceiling"));
	return (1);
}
