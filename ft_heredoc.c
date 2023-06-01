/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:23:36 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/31 17:28:35 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

int	ft_heredoc(char *delimiter)
{
	char	*inp_heredoc;
	int		fd;
	int		i;

	i = 0;
	g_status = 0;
	signal(SIGQUIT, SIG_IGN);
	fd = open("heredoc", O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
	while (1)
	{
		inp_heredoc = readline("\033[33m🤟🍀🤟>\033[0m");
		if (!inp_heredoc)
		{
			printf("bash: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		if (g_status == 130)
			break ;
		if (!ft_strncmp(inp_heredoc, delimiter, \
		ft_max(ft_strlen(inp_heredoc), ft_strlen(delimiter))))
			break ;
		if (i++ != 0)
			ft_putstr_fd("\n", fd);
		ft_putstr_fd(inp_heredoc, fd);
	}
	close(fd);
	fd = open("heredoc", O_RDONLY);
	return (fd);
}
