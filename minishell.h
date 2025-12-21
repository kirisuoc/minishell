#ifndef MINISHELL_H
# define MINISHELL_H

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

void	free_array(char **array);
int		has_slash(char *cmd);
void	print_error(char *cmd, enum e_error_type type);
char	**parse(char *line);
char	*find_in_path(char *cmd, char **envp);
void	exec_command(char **args, char **envp);

#endif
