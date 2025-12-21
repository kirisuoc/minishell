/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:56:12 by ecousill          #+#    #+#             */
/*   Updated: 2025/12/21 18:34:49 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// IMPLEMENTAR ft_split_whitespace en lugar de strtok
/* char	**parse(char *line)
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
	return (args);
} */

char	**parse(char *line)
{
	char	**args;
	char	*token;
	int		i;

	i = 0;
	args = ft_split_whitespace(line);
	return (args);
}

char	*find_in_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	char	*temp;
	int		i;

	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		i++;
	}
	free_array(paths);
	return (NULL);
}

void	exec_command(char **args, char **envp)
{
	pid_t	pid;
	char	*path;

	pid = fork();
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
				exit(1);
			}
		}
		else
		{
			path = find_in_path(args[0], envp);
			if (!path)
			{
				print_error(args[0], ERR_CMD_NOT_FOUND);
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
	char	*line;
	char	**args;

	if (ac > 3000)
		return (0);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		args = parse(line);
		if (args[0])
			exec_command(args, envp);
		free_array(args);
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

/*
En mac:
	cc main.c -g \
	-I/opt/homebrew/opt/readline/include \
	-L/opt/homebrew/opt/readline/lib \
	-lreadline \
	-o minishell

	clear_history() en Linux
*/
