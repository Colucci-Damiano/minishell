/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:58:07 by vguidoni          #+#    #+#             */
/*   Updated: 2023/05/15 15:41:18 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_new_cmd(char **full_cmds, int x, int y)
{
	
}

t_list	*ft_create_cmds(char **full_cmds)
{
	t_list	*cmds;
	t_list	*new;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (full_cmds == NULL)
		return (NULL);
	while(full_cmds[x])
	{
		if(full_cmds[x][0] == '|')
		{
        	new = ft_new_cmd(full_cmds, x, y);
        	y = x;
		}
		x++;
	}
	new = ft_new_cmd(fulls_cmds, x, y);
	return (cmds)
}
