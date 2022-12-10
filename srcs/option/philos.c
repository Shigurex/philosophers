/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:16:12 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/10 18:35:08 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

static void	eat_meal(t_vars *vars, t_philos *philos)
{
	ssize_t	eat_start;

	pthread_mutex_lock(philos->right_fork);
	//print_state(vars, TAKEN_A_FORK, get_timestamp(), philos->id);
	pthread_mutex_lock(philos->left_fork);
	//print_state(vars, TAKEN_A_FORK, get_timestamp(), philos->id);
	eat_start = get_timestamp();
	pthread_mutex_lock(&vars->check);
	philos->last_meal = eat_start;
	philos->status = EATING;
	print_state(vars, EATING, eat_start, philos->id);
	pthread_mutex_unlock(&vars->check);
	wait_certain_time(eat_start + philos->time_to_eat);
	pthread_mutex_lock(&vars->check);
	philos->num_ate++;
	pthread_mutex_unlock(&vars->check);
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
}

static void	sleep_philos(t_vars *vars, t_philos *philos)
{
	ssize_t	sleep_start;

	sleep_start = get_timestamp();
	pthread_mutex_lock(&vars->check);
	philos->status = SLEEPING;
	print_state(vars, SLEEPING, sleep_start, philos->id);
	pthread_mutex_unlock(&vars->check);
	wait_certain_time(sleep_start + philos->time_to_sleep);
}

static void	think_philos(t_vars *vars, t_philos *philos)
{
	pthread_mutex_lock(&vars->check);
	philos->status = THINKING;
	print_state(vars, THINKING, get_timestamp(), philos->id);
	pthread_mutex_unlock(&vars->check);
}

void	*act_philos(void *p)
{
	t_philos	*philos;
	t_vars		*vars;

	philos = (t_philos *)p;
	vars = (t_vars *)philos->vars;
	pthread_mutex_lock(&vars->check);
	pthread_mutex_unlock(&vars->check);
	if (philos->id % 2 == 0)
		usleep(philos->time_to_eat * MILISECOND / 2);
	while (true)
	{
		eat_meal(vars, philos);
		sleep_philos(vars, philos);
		think_philos(vars, philos);
	}
}
