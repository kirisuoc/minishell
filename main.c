/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:10:01 by ecousill          #+#    #+#             */
/*   Updated: 2025/12/16 20:19:35 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

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

int	main(/*int ac, char **av*/)
{
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
		for (int i = 0; args[i]; i++)
			printf("%s\n", args[i]);
		for (int i = 0; args[i]; i++)
			free(args[i]);
		free(args);
		free(line);
	}
	rl_clear_history();

/*	int	args = ac;

 	while (1)
	{
		printf("Este es el prompt.\n");
		if (args >= 2)
		{
			printf("%s\n", av[1]);
			args--;
		}
		else
			return 0;
	} */
	return (0);
}
