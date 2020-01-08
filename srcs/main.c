/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:44:33 by fberger           #+#    #+#             */
/*   Updated: 2020/01/08 05:04:47 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** root towards the right function
*/

void	root(t_env *env, char *path, char **cmd_tab)
{
	if (env || path)
		;
	if (!ft_strcmp(cmd_tab[0], "echo"))
		builtin_echo(cmd_tab);
	else if (!ft_strcmp(cmd_tab[0], "cd"))
		builtin_cd(cmd_tab);
	else if (!ft_strcmp(cmd_tab[0], "pwd"))
		builtin_cd(cmd_tab);
	else if (!ft_strcmp(cmd_tab[0], "export"))
		builtin_export(cmd_tab);
	else if (!ft_strcmp(cmd_tab[0], "unset"))
		builtin_unset(cmd_tab);
	else if (!ft_strcmp(cmd_tab[0], "env"))
		builtin_env(cmd_tab);
	else if (!ft_strcmp(cmd_tab[0], "exit"))
	{
		free_env(env);
		exit(0);
	}
	else
		exec(cmd_tab);
}

/*
** get value from var name
*/

char	*var_value(t_env *env, char *name)
{
	t_env	*var;

	var = env;
	while (var)
	{
		if (!ft_strcmp(var->name, name))
			return (var->value);
		var = var->next;
	}
	return (NULL);
}

/*
** store env inside list
*/

int		store_env(char **env_tab, t_env **env)
{
	int		i;
	t_env	*var;
	t_env	*last;
	
	i = -1;
	last = NULL;
	while (env_tab[++i])
	{
		if (!(var = (t_env *)malloc(sizeof(t_env) * 1)))
			return (0);
		var->name = ft_substr(env_tab[i], 0, (int)(ft_strchr(env_tab[i], '=') - env_tab[i]));
		var->value = ft_substr(env_tab[i], (int)(ft_strchr(env_tab[i], '=') - env_tab[i]) + 1, ft_strlen(env_tab[i]));
		var->next = NULL;
		// printf("----------------\n[%s] = [%s]\n", var->name, var->value);
		if (last)
			last->next = var;
		else
			*env = var;
		last = var;
	}
	return (1);
}

/*
** En C, on peut récupérer l’ensemble des variables d’environment par le 3e
** argument de la fonction main, char **env.
*/

int		main(int argc, char **argv, char **env_tab)
{
	t_env	*env;
	char	*cmd;
	char	**cmd_tab;
	
  	(void)argc;
  	(void)argv;
	env = NULL;
	store_env(env_tab, &env);
	// print_env(env);
	while (1)
	{
		ft_printf("~ %s > ", ft_strrchr(var_value(env, "PWD"), '/') + 1);
		get_next_line(0, &cmd);
		cmd_tab = ft_split(cmd, ' ');
		root(env, var_value(env, "PATH"), cmd_tab);
		free_cmds(cmd, cmd_tab);
	}
	return (0);
}