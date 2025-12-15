/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:00:00 by fracurul          #+#    #+#             */
/*   Updated: 2025/12/15 00:00:00 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_map_debug(char **map)
{
	int	i;

	if (!map)
	{
		ft_printf("Map is NULL\n");
		return ;
	}
	ft_printf("=== MAP CONTENT DEBUG ===\n");
	i = 0;
	while (map[i])
	{
		ft_printf("Line %d: [%s]\n", i, map[i]);
		i++;
	}
	ft_printf("========================\n");
}
