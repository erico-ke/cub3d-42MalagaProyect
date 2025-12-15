/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 00:33:19 by fracurul          #+#    #+#             */
/*   Updated: 2025/12/16 00:45:51 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Validation of RGB string (no spaces, tabs and trash)
int	is_valid_rgb_number(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (i > 0);
}

// Valida formato RGB completo: "R,G,B" sin espacios ni basura
int	validate_rgb_format(char *line)
{
	char	**rgb;
	int		valid;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_map(rgb), 0);
	valid = is_valid_rgb_number(rgb[0]) && is_valid_rgb_number(rgb[1])
		&& is_valid_rgb_number(rgb[2]);
	if (!valid)
		return (free_map(rgb), 0);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_map(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}
// Validation of texture
int	validate_texture(char **texture_ptr, char *line, char *name)
{
	if (*texture_ptr)
	{
		ft_printf("Error: Duplicated %s texture\n", name);
		return (0);
	}
	if (!line[0] || line[0] == '\n')
	{
		ft_printf("Error: Empty %s texture path\n", name);
		return (0);
	}
	*texture_ptr = ft_strdup(line);
	return (1);
}

// Parse & validate RGB color one by one
int	parse_color_line(char *line, int *r, int *g, int *b, char *name)
{
	char	**rgb;

	if (*r != -1)
	{
		ft_printf("Error: Duplicated %s color\n", name);
		return (0);
	}
	if (!validate_rgb_format(line))
	{
		ft_printf("Error: Invalid %s color format\n", name);
		return (0);
	}
	rgb = ft_split(line, ',');
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	free_map(rgb);
	return (1);
}