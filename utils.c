/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 08:31:40 by ecousill          #+#    #+#             */
/*   Updated: 2025/12/21 08:31:42 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	has_slash(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '/')
			return (1);
		cmd++;
	}
	return (0);
}

void	print_error(char *cmd, enum e_error_type type)
{
	if (type == ERR_CMD_NOT_FOUND)
	{
		write(STDERR, "minishell: ", 11);
		write(STDERR, cmd, ft_strlen(cmd));
		write(STDERR, ": command not found\n", 20);
	}
	else if (type == ERR_NO_FILE)
	{
		write(STDERR, "minishell: ", 11);
		write(STDERR, cmd, ft_strlen(cmd));
		write(STDERR, ": No such file or directory\n", 28);
	}
	else if (type == ERR_SYSCALL)
	{
		// errno debe estar seteado por la syscall
		write(STDERR, "minishell: ", 11);
		write(STDERR, cmd, ft_strlen(cmd));
		write(STDERR, ": ", 2);
		perror(""); // perror añade la descripción del error
	}
}
