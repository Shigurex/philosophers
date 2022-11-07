/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:16:12 by yahokari          #+#    #+#             */
/*   Updated: 2022/11/07 17:59:02 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

static void	eat_meal(t_vars *vars, t_philos *philos)
{
	pthread_mutex_lock(philos->right_fork);
	print_state(vars, TAKEN_A_FORK, get_timestamp(), philos->id);
	pthread_mutex_lock(philos->left_fork);
	print_state(vars, TAKEN_A_FORK, get_timestamp(), philos->id);
	philos->last_action = get_timestamp();
	pthread_mutex_lock(vars->check);
	philos->last_meal = philos->last_action;
	pthread_mutex_unlock(vars->check);
	print_state(vars, EATING, philos->last_action, philos->id);
	wait_certain_time(philos->last_action + philos->time_to_eat);
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_lock(vars->check);
	philos->num_ate++;
	philos->last_meal = philos->last_action;
	pthread_mutex_unlock(vars->check);
}

static void	sleep_philos(t_vars *vars, t_philos *philos)
{
	philos->last_action = get_timestamp();
	print_state(vars, SLEEPING, philos->last_action, philos->id);
	wait_certain_time(philos->last_action + philos->time_to_sleep);
}

static void	think_philos(t_vars *vars, t_philos *philos)
{
	print_state(vars, THINKING, get_timestamp(), philos->id);
}

void	*act_philos(void *p)
{
	t_philos	*philos;
	t_vars		*vars;

	philos = (t_philos *)p;
	vars = philos->vars;
	pthread_mutex_lock(vars->check);
	philos->status = ACTIVE;
	philos->last_meal = get_timestamp();
	if (philos->id == 1)
		vars->initial_time = get_timestamp();
	pthread_mutex_unlock(vars->check);
	if (philos->id % 2 == 0)
		usleep(philos->time_to_eat * MILISECOND / 2);
	while (true)
	{
		eat_meal(vars, philos);
		sleep_philos(vars, philos);
		think_philos(vars, philos);
	}
	return (NULL);
}
