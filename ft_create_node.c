/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:00:19 by dcolucci          #+#    #+#             */
/*   Updated: 2023/06/10 20:28:19 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	ft_check_fdk_infile(t_node *node, char *infile, int fd_k, int fd)
{
	if (fd_k == -1)
	{
		if (node->str_infile)
			free(node->str_infile);
		node->str_infile = ft_strdup(infile);
		return (-1);
	}
	else
	{
		if (fd != STDIN_FILENO)
			close(fd);
		fd = fd_k;
		if (node->str_infile)
			free(node->str_infile);
		node->str_infile = ft_strdup(infile);
	}
	return (fd);
}

int	ft_check_fdk_outfile(t_node *node, char *outfile, int fd_k, int fd)
{
	if (fd_k == -1)
	{
		if (node->str_outfile)
			free(node->str_outfile);
		node->str_outfile = ft_strdup(outfile);
		return (-1);
	}
	else
	{
		if (fd != STDOUT_FILENO)
			close(fd);
		fd = fd_k;
		if (node->str_outfile)
			free(node->str_outfile);
		node->str_outfile = ft_strdup(outfile);
	}
	return (fd);
}

int	ft_infile(char **sub_cmd, t_node *node)
{
	int	x;
	int	fd_k;
	int	fd;

	x = -1;
	fd = STDIN_FILENO;
	node->str_infile = 0;
	while (sub_cmd[++x] && fd != -1)
	{
		if ((sub_cmd[x][0] == '<') && ft_strlen(sub_cmd[x]) == 1)
		{
			if (sub_cmd[x + 1][0] == '<')
			{
				if (fd != 0)
					close(fd);
				fd = ft_heredoc(sub_cmd[++x + 1]);
			}
			else
			{
				fd_k = open(sub_cmd[x + 1], O_RDONLY);
				fd = ft_check_fdk_infile(node, sub_cmd[x + 1], fd_k, fd);
			}
		}
	}
	return (fd);
}

int	ft_outfile(char **sub_cmd, t_node *node)
{
	int	x;
	int	fd;
	int	fd_k;

	x = 0;
	fd = STDOUT_FILENO;
	node->str_outfile = 0;
	while (sub_cmd[x] && fd != -1)
	{
		if (sub_cmd[x][0] == '>' && ft_strlen(sub_cmd[x]) == 1)
		{
			if (sub_cmd[x + 1][0] == '>')
				fd_k = open(sub_cmd[++x + 1], \
				O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
			else
				fd_k = open(sub_cmd[x + 1], \
				O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
			fd = ft_check_fdk_outfile(node, sub_cmd[x + 1], fd_k, fd);
			x = x + 1;
		}
		else
			x++;
	}
	return (fd);
}
