/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 05:42:59 by fberger           #+#    #+#             */
/*   Updated: 2020/01/25 21:45:21 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** root towards the right function
**
** nb :
** else if (cmd_tab[0]) sert à protéger la fonction execute 
** contre la commande constituee d'une chaine d'espaces + enter
*/

void	root(char **cmd_tab, int pdesread, int pdeswrite)
{
	ft_print_str_tab(cmd_tab, "root"); // pour debug
	if (is_dollar_env_var(cmd_tab[0]))
		ft_printf("%s\n", var_value(cmd_tab[0] + 1));
	else if (ft_strequci(cmd_tab[0], "echo"))
		builtin_echo(cmd_tab);
	else if (ft_strequci(cmd_tab[0], "cd"))
		builtin_cd(cmd_tab);
	else if (ft_strequci(cmd_tab[0], "pwd"))
		builtin_pwd();
	else if (ft_strequci(cmd_tab[0], "env")
	|| ft_strequci(cmd_tab[0], "setenv")
	|| ft_strequci(cmd_tab[0], "export")
	|| ft_strequci(cmd_tab[0], "unset"))
		builtins_env(cmd_tab, pdesread, pdeswrite);
	else if (ft_strequci(cmd_tab[0], "exit"))
		exit_minishell(cmd_tab);
	// else if (cmd_tab[0])
	// 	execute(cmd_tab);
}

/*
** real stuff happens here
*/

// void	connect_cmds(char **cmd_tab)
// {
//     int         pdes[2];
//     int	const   READ = 0;
// 	int	const	WRITE = 1;
// 	int 		i;

//     replace_dollar_vars(cmd_tab);
// 	i = 0;
//     while (cmd_tab[i])
// 	{
// 		if (count_pipe(cmd_tab) > 0)
// 		{
// 			execute_pipe(cmd_tab);
// 			// position_i_after_pipe(cmd_tab, &i);
// 		}
// 		else
// 			execute_cmd(cmd_tab, &i);
// 	}
// }