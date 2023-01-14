/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:05:23 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/14 20:47:19 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers_bonus.h"

void	philo_and_monitor(t_philos *philo)
{
	t_vars		*vars;
	pthread_t	thread;

	vars = philo->vars;
	pthread_mutex_init(&philo->check, NULL);
	pthread_create(&thread, NULL, &act_philo, philo);
	act_monitor(philo, vars);
	pthread_detach(thread);
}

void	create_process(t_vars *vars)
{
	ssize_t		i;
	t_philos	*philo;

	i = 0;
	while (i < vars->num_philos)
	{
		philo = &vars->philos[i];
		philo->pid = fork();
		if (philo->pid < 0)
			exit_with_message(FORK_ERROR);
		else if (philo->pid == CHILD)
			philo_and_monitor(philo);
		i++;
	}
}

void	wait_for_sem_signal(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->num_philos)
	{
		sem_wait(vars->check_end);
		i++;
	}
}

void	delete_process(t_vars *vars)
{
	t_philos	*philo;
	ssize_t		i;

	i = 0;
	while (i < vars->num_philos)
	{
		philo = &vars->philos[i];
		kill(philo->pid, SIGKILL);
		i++;
	}
}

void	sem_delete(t_vars *vars)
{
	sem_close(vars->forks);
	sem_unlink(FORKS);
	sem_close(vars->print);
	sem_unlink(PRINT);
	sem_close(vars->check_end);
	sem_unlink(CHECK_END);
}

void	exec_action(t_vars *vars)
{
	create_process(vars);
	wait_for_sem_signal(vars);
	delete_process(vars);
	sem_delete(vars);
	free(vars->philos);
}
