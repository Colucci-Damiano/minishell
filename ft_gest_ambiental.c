/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_ambiental.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 10:13:45 by vguidoni          #+#    #+#             */
/*   Updated: 2023/06/06 12:27:58 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

 char	*ft_sub_dollar(char *av, char *envp, int i, int k)
{
	char	*ex;
	char	*tmp;
	char	*tmp2;
	int		x;

	x = 0;
	while (envp[x] != '=' && envp[x])
		x++;
	tmp = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(tmp, av, i + 1);
	ex = ft_strdup(&envp[x + 1]);
	tmp2 = ft_strjoin(tmp, ex);
	free(tmp);
	free(ex);
	tmp = ft_strdup(&av[k]);
	ex = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	free(av);
	return (ex);
}

char	*ft_rm_exp(char *av, int i, int k)
{
	char	*tmp;
	char	*tmp2;
	char	*join;

	tmp = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(tmp, av, i + 1);
	tmp2 = ft_strdup(&av[k]);
	join = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	return (join);
}

char	*ft_dollar(char **envp, char *to_exp)
{
	char	*separator;
	char	*var;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	separator = "<>\\/|+-.,;:~{}[]()&%%\"^'#@*$= ";
	while (to_exp[i])
	{
		if (to_exp[i] == '$')
		{
			if (!ft_strchr(separator, to_exp[i + 1]))
				j = i + 1;
			else
				j = i;
			while (!ft_strchr(separator, to_exp[j]) && to_exp[j])
				j++;
			if (to_exp[i + 1] == '?')
				to_exp = ft_substitute_string(to_exp, ft_itoa(g_status), i, 2);
			else
			{
				var = (char *) malloc (sizeof (char) * (j - i + 1));
				ft_strlcpy(var, &to_exp[i + 1], (j - i));
				value = ft_getenv(var, envp);
				to_exp = ft_substitute_string(to_exp, value, i, j - i);
			}
			if (!to_exp[j])
				break ;
			i = j + 1;
		}
		else
			i++;
	}
	return (to_exp);
}

int		ft_next_quote_exp(char *s, int i)
{
	char	q;

	q = 0;
	if (in_set(s[i], "\'\""))
	{
		q = s[i++];
		while (s[i] && s[i] != q)
			i++;
	}
	else
	{
		while (s[i] && !in_set(s[i], "\'\""))
			i++;
		if (in_set(s[i], "\'\""))
			i--;
	}
	return (i);
}

char	*ft_expander(char *exp, char **envp)
{
	char	*join;
	char	*tmp_join;
	char	*tmp;
	char	*expanded;
	int 	x;
	int 	k;

	x = 0;
	join = 0;
	while (exp[x])
	{
		k = ft_next_quote_exp(exp, x);
		if (exp[x] == '\'')
		{
			tmp = (char *) malloc (sizeof(char) * (k - x + 2));
			ft_strlcpy(tmp, &exp[x], (k - x + 2));
			tmp_join = join;
			join = ft_strjoin_null(join, tmp);
			ft_safe_free(tmp);
			ft_safe_free(tmp_join);
		}
		else
		{
			tmp = (char *) malloc (sizeof(char) * (k - x + 2));
			ft_strlcpy(tmp, &exp[x], (k - x + 2));
			expanded = ft_dollar(envp, tmp);
			tmp_join = join;
			join = ft_strjoin_null(join, expanded);
			ft_safe_free(tmp);
			ft_safe_free(expanded);
			ft_safe_free(tmp_join);
		}
		x = k + 1;
		if (!exp[k])
			break ;
		if (!exp[k + 1])
			break ;
	}
	return (join);
}


/*
	Description:
		The function ft_gest_ambiental expand every $ variable in every string
		of av starting with double quotes (") or not starting with single quotes
		(');
	Return value:
		It returns a double char pointer with the $variable replaced
		by its corresponding environment variable.
		If no variable is found the $xxx character (not in separators set) 
		are removed from the string.
*/

char	**ft_gest_ambiental(char **spl, char **envp)
{
	int		x;
	char	*tmp;

	x = 0;
	if (spl == NULL)
		return (NULL);
	while (spl[x])
	{
		tmp = spl[x];
		spl[x] = ft_expander(spl[x], envp);
		free(tmp);
		x++;
	}
	return (spl);
}
