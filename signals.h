#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t g_signal;

void	init_signals(void);
void	handle_sigint(int sig);

#endif
