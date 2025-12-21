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
