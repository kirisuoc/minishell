/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:56:12 by ecousill          #+#    #+#             */
/*   Updated: 2025/12/21 01:37:57 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

#define STDERR 2

enum e_error_type {
	ERR_CMD_NOT_FOUND,
	ERR_NO_FILE,
	ERR_SYSCALL
};

void	print_error(char *cmd, enum e_error_type type)
{
	if (type == ERR_CMD_NOT_FOUND) {
		write(STDERR, "minishell: ", 11);
		write(STDERR, cmd, ft_strlen(cmd));
		write(STDERR, ": command not found\n", 20);
	}
	else if (type == ERR_NO_FILE) {
		write(STDERR, "minishell: ", 11);
		write(STDERR, cmd, ft_strlen(cmd));
		write(STDERR, ": No such file or directory\n", 28);
	}
	else if (type == ERR_SYSCALL) {
		// errno debe estar seteado por la syscall
		write(STDERR, "minishell: ", 11);
		write(STDERR, cmd, ft_strlen(cmd));
		write(STDERR, ": ", 2);
		perror(""); // perror añade la descripción del error
	}
}

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
	token = strtok(line, " \t\n");										// Función no permitida, usar ft_split?
	while (token != NULL)
	{
		args[i] = strdup(token); // duplicar string
		i++;
		token = strtok(NULL, " \t\n");									// Función no permitida, usar ft_split?
	}
	args[i] = NULL; // execve necesita NULL al final
	return args;
}

char *find_in_path(char *cmd, char **envp)
{
	char **paths;
	char *full_path;
	char *temp;

	paths = ft_split(getenv("PATH"), ':');
	for (int i = 0; paths[i]; i++){
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			for (int i = 0; paths[i]; i++){
				free(paths[i]);
			}
			free(paths);
			return (full_path);
		}
	}

	for (int i = 0; paths[i]; i++){
		free(paths[i]);
	}
	free(paths);

	return (NULL);
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
				print_error(args[0], ERR_NO_FILE);
				//perror("execve");
				exit(1);
			}
		}
	 	else
		{
			char *path = find_in_path(args[0], envp);
			if (!path)
			{
				print_error(args[0], ERR_CMD_NOT_FOUND);
				//fprintf(stderr, "minishell: %s: command not found\n", args[0]);		// ???
				exit(127);
			}
			execve(path, args, envp);
			free(path);
		}
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
