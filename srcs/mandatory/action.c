/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:18:40 by yahokari          #+#    #+#             */
/*   Updated: 2022/11/04 18:33:17 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	*act_philos(void *p)
{
	t_philos	*philos;
	t_vars		*vars;

	philos = (t_philos *)p;
	vars = philos->vars;
	record_action(vars, philos, INIT);
	if (philos->id % 2 == 0)
		usleep(vars->time_to_eat * MILISECOND / 2);
	while (true)
	{
		pthread_mutex_lock(philos->right_fork);
		record_action(vars, philos, TAKEN_A_FORK);
		pthread_mutex_lock(philos->left_fork);
		record_action(vars, philos, TAKEN_A_FORK);
		record_action(vars, philos, EATING);
		wait_certain_time(philos->last_action + vars->time_to_eat);
		pthread_mutex_unlock(philos->right_fork);
		pthread_mutex_unlock(philos->left_fork);
		record_action(vars, philos, SLEEPING);
		wait_certain_time(philos->last_action + vars->time_to_sleep);
		record_action(vars, philos, THINKING);
	}
	return (NULL);
}

void	*observe_philos(void *p)
{
	t_vars		*vars;
	t_philos	*philos;
	ssize_t		i;
	ssize_t		timestamp;
	ssize_t		death_time;

	vars = (t_vars *)p;
	while (true)
	{
		i = 0;
		while (i < vars->num_philos)
		{
			philos = &vars->philos[i];
			if (philos->status == EATING)
			{
				i++;
				continue ;
			}
			death_time = philos->last_meal + vars->time_to_die;
			timestamp = get_timestamp();
			if (timestamp >= death_time)
			{
				record_action(vars, philos, DIED);
				pthread_mutex_lock(&vars->print);
				return (NULL);
			}
			i++;
		}
		i = 0;
		while (vars->option_set == true && i < vars->num_philos)
		{
			philos = &vars->philos[i];
			if (philos->num_ate < vars->num_must_eat)
				break ;
			i++;
			if (i == vars->num_philos)
			{
				pthread_mutex_lock(&vars->print);
				return (NULL);
			}
		}
	}
	return (NULL);
}
