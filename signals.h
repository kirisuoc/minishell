#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <termios.h>


extern volatile sig_atomic_t g_signal;

void	init_signals(void);
void	handle_sigint(int sig);
void	disable_echoctl(void);

#endif
