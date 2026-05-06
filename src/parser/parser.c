/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:00:00 by fracurul          #+#    #+#             */
/*   Updated: 2025/12/26 14:49:15 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_map_content(t_data *data, char *map)
{
	if ((!data->plane->no_texture || !data->plane->so_texture
			|| !data->plane->we_texture || !data->plane->ea_texture
			|| data->plane->c_red == -1 || data->plane->f_red == -1)
		&& map)
		return (0);
	return (1);
}

static int	free_gnl(char *map, char *line, int fd)
{
	free(map);
	close(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

static int	process_line(char *line, t_data *data, char **map_content)
{
	int	i;

	if (line[0] == ' ' || ((line[0] >= 9 && line[0] <= 13) && line[0] != '\n')
		|| ft_isdigit(line[0])
		|| line[0] == '1' || (line[0] == '\n' && *map_content))
	{
		*map_content = ft_strjoin_g(*map_content, line);
		i = -1;
		while (map_content[0][++i] && map_content[0][i + 1])
		{
			if ((map_content[0][i] == '\n' && map_content[0][i + 1] == '\n')
				|| ((map_content[0][i] >= 9 && map_content[0][i] <= 13)
				&& map_content[0][i] != '\n'))
				return (printf("Error: invalid map\n"), 0);
		}
		i = 0;
		while (map_content[0][i] == ' '
			|| ((map_content[0][i] >= 9 && map_content[0][i] <= 13)
			&& map_content[0][i] != '\n'))
			i++;
		if (map_content[0][i] == '\n')
			return (printf("Error: blank line in file\n"), 0);
		return (1);
	}
	return (textures_n_colors(line, data));
}

int	read_cub(const char *filecub, t_data *data, int fd)
{
	char	*line;
	char	*map_content;

	fd = open(filecub, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error opening file\n"), 1);
	line = get_next_line(fd);
	map_content = NULL;
	while (line)
	{
		if (!check_map_content(data, map_content))
			return (printf("Error: invalid content position\n")
				, free_gnl(map_content, line, fd));
		if (!process_line(line, data, &map_content))
			return (free_gnl(map_content, line, fd), 1);
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
	else if (ft_strncmp(line, "\n", 1) != 0)
		return (printf ("Error blank in map\n"), 0);
	return (1);
}
