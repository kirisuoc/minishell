/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:56:12 by ecousill          #+#    #+#             */
/*   Updated: 2025/12/19 13:35:03 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

/*
En mac:
	cc main.c -g \
	-I/opt/homebrew/opt/readline/include \
	-L/opt/homebrew/opt/readline/lib \
	-lreadline \
	-o minishell

	clear_history() en Linux
*/

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

char	**parse(char *line)
{
	char	**args;
	char	*token;
	int		i;

	i = 0;
	args = malloc(128 * sizeof(char *)); // espacio para 128 tokens
	token = strtok(line, " \t\n");
	while (token != NULL)
	{
		args[i] = strdup(token); // duplicar string
		i++;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL; // execve necesita NULL al final
	return args;
}

void exec_command(char **args, char **envp)
{
	pid_t	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		// proceso hijo
		if (has_slash(args[0]))
		{
			if (execve(args[0], args, envp) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
/* 		else
		{
			if (execve(args[0], args, envp) == -1)
			{
				perror("execve");
				exit(1);
			}
		} */
	}
	else
	{
		// proceso padre
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **envp)
{
	if (ac > 3000)
		return (0);
	while (1)
	{
		char	*line;
		char	**args;

		line = readline("minishell$ ");
		if (!line)
			break;
		if (*line)
			add_history(line);

		args = parse(line);
		if (args[0])
			exec_command(args, envp);

		for (int i = 0; args[i]; i++)
			free(args[i]);
		free(args);
		free(line);
	}
	rl_clear_history();

	return (0);
}


/*
1. Flujo general: ✔️ correcto
	Tu descripción del flujo es esencialmente esta:
		readline() lee una línea del usuario
		Si devuelve NULL → salir (Ctrl-D)
		Si la línea no está vacía → add_history
		Parseas la línea en un array args
		Si hay comando → ejecutas
		Creas un proceso hijo con fork
		En el hijo llamas a execve
		El hijo se transforma en el programa
		El padre espera
		Vuelves al prompt
*/
