/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libunit.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/11 18:17:23 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/11 18:17:23 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "libunit.h"

// https://en.cppreference.com/w/c/program/sig_atomic_t TODO NEEDS volatile too ???
sig_atomic_t g_child_pid;
sig_atomic_t g_timeout_triggered;

/*
** void	timer_sig_handler(__attribute__((unused)) int signo,
** __attribute__((unused)) siginfo_t *info,
** __attribute__((unused)) void *context)
*/

void	timer_sig_handler(int signo, siginfo_t *info, void *context)
{
	(void)signo;
	(void)info;
	(void)context;
	g_timeout_triggered = 1;
	kill(g_child_pid, SIGKILL);
}

void	set_timer_sig_handler(void)
{
	struct sigaction sig;
	struct itimerval timer;

	sig = (struct sigaction) {
		.sa_sigaction = timer_sig_handler,
		.sa_flags = SA_SIGINFO | SA_RESTART
	};
	sigemptyset(&sig.sa_mask);
	ft_err_exit(sigaction(SIGALRM, &sig, NULL) != 0, "Failed to set sigaction!\n");
	timer.it_interval = (struct timeval) {.tv_sec = 0, .tv_usec = 0};
	timer.it_value = (struct timeval) {.tv_sec = 1, .tv_usec = 0};
	ft_err_exit(setitimer(ITIMER_REAL, &timer, NULL) != 0, "Failed to set timer!\n");
}

void	remove_timer_sig_handler(void)
{
	struct sigaction sig;
	struct itimerval timer;

	sig = (struct sigaction){
		.sa_handler = SIG_DFL,
	};
	sigemptyset(&sig.sa_mask);
	ft_err_exit(sigaction(SIGALRM, &sig, NULL) != 0, "Failed to set sigaction!\n");
	timer.it_interval = (struct timeval) {.tv_sec = 0, .tv_usec = 0};
	timer.it_value = (struct timeval) {.tv_sec = 0, .tv_usec = 0};
	ft_err_exit(setitimer(ITIMER_REAL, &timer, NULL) != 0, "Failed to set timer!\n");
}

void	run_test(
				void (*func)(void),
				const char *name,
				const char *file,
				size_t line
				)
{
	pid_t	pid;
	int		status;

	pid = fork();
	ft_err_exit(pid == -1, "Fork failed!\n");
	if (pid == 0)
	{
		func();
		exit(0);
	}
	else
	{
		g_child_pid = pid;
		set_timer_sig_handler();
		ft_err_exit(wait(&status) == -1, "Failed to wait()!\n");
		// TODO Race condition here????
		remove_timer_sig_handler();
	}
	if (g_timeout_triggered)
	{
		g_timeout_triggered = 0;
		printf("%s@(%s:%lu): Timeout\n", name, file, line);
	}
	else if (!WIFEXITED(status) && WIFSIGNALED(status))
	{
		printf("%s@(%s:%lu): %s\n", name, file, line, sys_siglist[WTERMSIG(status)]);
	}
}
