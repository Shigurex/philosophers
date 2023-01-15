/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 10:46:51 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/15 17:22:40 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers_bonus.h"

static void	eat_meal(t_philos *philo)
{
	ssize_t	eat_start;

	sem_wait(philo->forks);
	print_state(philo->print, TAKEN_A_FORK, \
		get_timestamp() - philo->initial_time, philo->id);
	sem_wait(philo->forks);
	print_state(philo->print, TAKEN_A_FORK, \
		get_timestamp() - philo->initial_time, philo->id);
	eat_start = get_timestamp();
	sem_wait(philo->check);
	philo->last_meal = eat_start;
	sem_post(philo->check);
	print_state(philo->print, EATING, \
		eat_start - philo->initial_time, philo->id);
	wait_certain_time(eat_start + philo->time_to_eat);
	sem_wait(philo->check);
	philo->num_ate++;
	sem_post(philo->check);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

static void	sleep_philo(t_philos *philo)
{
	ssize_t	sleep_start;

	sleep_start = get_timestamp();
	print_state(philo->print, SLEEPING, \
		sleep_start - philo->initial_time, philo->id);
	wait_certain_time(sleep_start + philo->time_to_sleep);
}

static void	think_philo(t_philos *philo)
{
	print_state(philo->print, THINKING, \
		get_timestamp() - philo->initial_time, philo->id);
}

void	*act_philo(void *p)
{
	t_philos	*philo;

	philo = (t_philos *)p;
	wait_certain_time(philo->initial_time);
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat * MILISECOND / 2);
	while (true)
	{
		eat_meal(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	return (NULL);
}
