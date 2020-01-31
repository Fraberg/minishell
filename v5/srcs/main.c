/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:44:33 by fberger           #+#    #+#             */
/*   Updated: 2020/01/31 04:44:34 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** store env inside list
*/

int		store_env(char **env_tab)
{
	int		i;
	t_env	*var;
	t_env	*last;
	int		len;
	
	i = -1;
	last = NULL;
	if (!env_tab || !*env_tab) // env -i
		return (0);
	while (env_tab[++i])
	{
		var = NULL;
		if (!(var = (t_env *)malloc(sizeof(t_env))))
			return (0);
		len = (int)(ft_strchr(env_tab[i], '=') - env_tab[i]);
		var->name = ft_substr(env_tab[i], 0, len);
		var->value = ft_substr(env_tab[i], len + 1, ft_strlen(env_tab[i]));
		var->next = NULL;
		if (last)
			last->next = var;
		else
			g_env = var;
		last = var;
	}
	return (1);
}

/*
** parse_and_root_cmds()
** 3 possibilités : pipeline || single builtin || single execv
*/

void	parse_and_root_cmds(char **cmds)
{
	int		i;
	char	**cmd_tab;

	i = -1;
	while (cmds[++i])
	{
		if (!(cmd_tab = ft_split_set_quotes_chevrons(cmds[i], " \t")))
			continue ;
		if (DEBUG)
			ft_print_str_tab(cmd_tab, "inside parse_and_root_cmds");
		replace_dollar_vars(cmd_tab);
		if (count_pipe(cmd_tab) > 0)
		{
			if (!process_pipeline(cmd_tab, 0))
				ft_putstr("minishell: broken pipe error\n");
		}
		else if (is_builtin(cmd_tab))
			single_builtin(cmd_tab);
		else if (cmd_tab[0]) // meaning if at leat 1 arg
			single_execv(cmd_tab);
		ft_free_str_tab(cmd_tab);
	}
}

/*
** put prompt isolé pour pouvoir l'appeler depuis les fonctions de gestion des sig
*/

void	put_prompt(void)
{
	char	*tmp;
	char	*pwd;

	tmp = NULL;
	if ((tmp = var_value("PWD")))
	{
		pwd = NULL;
		if ((pwd = ft_strrchr(tmp, '/') + 1))
			ft_printf("%s~ %s%s%s >%s ", BOLDGREEN, BOLDMAGENTA, pwd, BOLDGREEN, RESET);
	}
	else
		ft_printf("%s~ %s%s%s >%s ", BOLDGREEN, BOLDMAGENTA, "bash", BOLDGREEN, RESET);
}

/*
** good old main
*/

int		main(int argc, char **argv, char **env_tab)
{
	char	*line;
	char	**cmds;

	if (argc != 1)
		return (0);
	(void)argv[argc];
	if (!store_env(env_tab))
		return (0);
	while (42)
	{
		listen_sig();
		put_prompt();
		if (!get_next_line(STDIN_FILENO, &line) || parse_error(line)) // if GNL ret 0 it means CTRL + D was hit which occurs EOF, that quits shell
			free_and_exit(EXIT_FAILURE, NULL);
		else
		{
			if (!(cmds = ft_split_cmds(line, ";")))
				continue ;
			parse_and_root_cmds(cmds);
			free_cmds(line, cmds);
		}
	}
	return (0);
}

/*
** TODO

** remove # include <stdio.h> in .h

** ls -la | cat -e | sort > filename ne fonctionne pas

** comprendre le pb 'Uninitialised value was created by a heap allocation' avec 'make re && valgrind --leak-check=full --track-origins=yes ./minishell'

** apparement ok car c'est juste un pb dans valgrind cf slack : trouver comment free les leaks des fork (exemple faire la cmd 'env | cat -e | sort' avec valgrind)

** norme

** cat < filename

** est-ce que le echo < filename (left redirection) existe/est à faire ?

** comprendre pq le prompt se decale avec cette commande
~ v5 > ls -la > 1
 v5 >
 v5 >
~ v5 >

** protection des mallocs ?

** mettre certaines fonctions en static pour la forme

** cleaner split_cmds.c (fonctionnel), renommer les fonctions de facon explicite, repenser le code etc

** compiler avec -fsanitize=address (attention ne pas combiner fsanitize avec valgrind sinon bug)

** regler les pb de 'valgrind --leak-check=full --track-origins=yes ./minishell'

** si on lance ./minishell dans ./minishell il faut que le second ait bien les variables d'env du premier ?

** lister tous les tests qui passent / passent pas, en attendant d'avoir le sujet d'exam

** env > filename

*/