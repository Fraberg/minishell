/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 03:52:42 by fberger           #+#    #+#             */
/*   Updated: 2020/02/06 18:06:56 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** echo écrit chaque message sur la sortie standard, avec un
** espace  entre  chacun  d'eux, et un saut de ligne après le
** dernier.
** option ’-n’ = ne pas effectuer le saut de ligne final.
**
** observations :
** echo -n -n n'affiche rien
*/

void	builtin_echo(char **cmd_tab)
{
	int		i;
	char	**args;

	i = 0;
	if (cmd_tab[1] == 0)
		write(1, "\n", 1);
	else
	{
		if (DEBUG)
			ft_print_str_tab(cmd_tab, "builtin_echo 1"); // pour debug
		args = format_args(cmd_tab);
		if (DEBUG)
			ft_print_str_tab(args, "builtin_echo 2"); // pour debug
		i = 0;
		while (args[++i])
		{
			// if (DEBUG)
			// 	printf("args[i] = %s\n", args[i]); // pour debug
			if (ft_strlen(args[i]) == 0 || is_n_option(i, args))
				continue ;
			if (i > 1 && !is_n_option(i - 1, args))
				write(1, " ", 1);
			write(1, args[i], ft_strlen(args[i]));
		}
		write(1, "\n", no_option_n(args));
		ft_free_str_tab(args);
	}
	*last_cmd_exit() = EXIT_SUCCESS;;
}