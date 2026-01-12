#include "minishell.h"


//test rama jorge
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

void	child_exec(char *cmd, char **args, char **envp)
{
	char	*path;

	if (has_slash(cmd))
	{
		if (execve(cmd, args, envp) == -1)
		{
			print_error(cmd, ERR_NO_FILE);
			exit(1);
		}
	}
	else
	{
		path = find_in_path(cmd, envp);
		if (!path)
		{
			print_error(cmd, ERR_CMD_NOT_FOUND);
			exit(127);
		}
		execve(path, args, envp);
		free(path);
	}
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
		// restore_termios() // Para restaurar valor inicial 'stty echoctl'
		child_exec(args[0], args, envp);	// proceso hijo
	}
	else
	{
		disable_echoctl();	// Volvemos a desactivar porque se activó en el hijo
		waitpid(pid, NULL, 0);				// proceso padre
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**args;

	if (ac > 3000)
		return (0);
	// save_termios(); // estado original
	init_signals();
	disable_echoctl();	// Para que no escriba '^C' (para el prompt)
	while (1)
	{
		line = readline(PROMPT);
		// line = readline("minishell$ ");
		if (!line)
			break ;
		if (g_signal == SIGINT)  // Ctrl-C
		{
		g_signal = 0;  // reset
		free(line);     // readline malloc
		continue;       // vuelve al inicio del bucle
		}
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
