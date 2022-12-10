/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:09:04 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/10 18:48:52 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

static void	eat_meal(t_philos *philos)
{
	ssize_t	eat_start;

	pthread_mutex_lock(philos->right_fork);
	print_state(&philos->print, TAKEN_A_FORK, get_timestamp(), philos->id);
	pthread_mutex_lock(philos->left_fork);
	print_state(&philos->print, TAKEN_A_FORK, get_timestamp(), philos->id);
	eat_start = get_timestamp();
	philos->last_meal = eat_start;
	philos->status = EATING;
	print_state(&philos->print, EATING, eat_start, philos->id);
	wait_certain_time(eat_start + philos->time_to_eat);
	philos->num_ate++;
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
}

static void	sleep_philos(t_philos *philos)
{
	ssize_t	sleep_start;

	sleep_start = get_timestamp();
	philos->status = SLEEPING;
	print_state(&philos->print, SLEEPING, sleep_start, philos->id);
	wait_certain_time(sleep_start + philos->time_to_sleep);
}

static void	think_philos(t_philos *philos)
{
	philos->status = THINKING;
	print_state(&philos->print, THINKING, get_timestamp(), philos->id);
}

void	*act_philos(void *p)
{
	t_philos	*philos;

	philos = (t_philos *)p;
	wait_certain_time(philos->initial_time);
	if (philos->id % 2 == 0)
		usleep(philos->time_to_eat * MILISECOND / 2);
	while (true)
	{
		eat_meal(philos);
		sleep_philos(philos);
		think_philos(philos);
	}
}
