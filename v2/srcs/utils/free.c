/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:22:59 by fberger           #+#    #+#             */
/*   Updated: 2020/01/15 18:16:34 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** free 2D str array
*/

void	free_str_tab(char **str_tab)
{
	int i;

    i = -1;
    while (str_tab && str_tab[++i])
    	ft_strdel(&str_tab[i]);
    if (str_tab)
	{
		free(str_tab);
		str_tab = NULL;
	}
}

/*
** free cmds
*/

void	free_cmds(char *line, char **cmds)
{
    free_str_tab(cmds);		
    ft_strdel(&line);
}

/*
** free env list
*/

void   free_env(t_env *elem)
{
    t_env *tmp;

	while (elem)
	{
		tmp = elem->next;
		ft_strdel(&elem->name);
		ft_strdel(&elem->value);
		elem = tmp;
	}
}

/*
** free_and_exit
*/

void	free_and_exit(t_env *env, int exit_value, char *msg)
{
	if (msg)
		ft_printf("%s\n", msg);
	free_env(env);
	exit(exit_value);
}