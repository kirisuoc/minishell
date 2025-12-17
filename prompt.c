/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 09:30:58 by ecousill          #+#    #+#             */
/*   Updated: 2025/12/17 09:37:01 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*prompt(void)
{
	char	*cwd;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("minishell$ "));
	prompt = ft_strjoin(cwd, "$ ");
	free(cwd);
	return (prompt);
}
