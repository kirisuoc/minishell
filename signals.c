#include "minishell.h"

volatile sig_atomic_t g_signal = 0;

void	init_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);

}

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;

	// readline: limpiar linea actual y mostrar prompt de nuevo
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
