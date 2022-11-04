/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:54:32 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/27 09:13:57 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	eat_meal(t_vars *vars, t_philos *philos)
{
	pthread_mutex_lock(philos->right_fork);
	philos->last_action = get_timestamp();
	print_state(vars, TAKEN_A_FORK, philos->last_action, philos->id);
	pthread_mutex_lock(philos->left_fork);
	philos->last_action = get_timestamp();
	print_state(vars, TAKEN_A_FORK, philos->last_action, philos->id);
	philos->last_action = get_timestamp();
	philos->status = EATING;
	print_state(vars, EATING, philos->last_action, philos->id);
	wait_certain_time(philos->last_action + vars->time_to_eat);
	philos->last_meal = get_timestamp();
	philos->num_ate++;
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
}

void	*act_philos(void *p)
{
	t_philos	*philos;
	t_vars		*vars;

	philos = (t_philos *)p;
	vars = philos->vars;
	philos->last_meal = get_timestamp();
	if (philos->id % 2 == 0)
		usleep(vars->time_to_eat * MILISECOND / 2);
	while (TRUE)
	{
		eat_meal(vars, philos);
		philos->last_action = get_timestamp();
		philos->status = SLEEPING;
		print_state(vars, SLEEPING, philos->last_action, philos->id);
		wait_certain_time(philos->last_action + vars->time_to_sleep);
		philos->last_action = get_timestamp();
		philos->status = THINKING;
		print_state(vars, THINKING, philos->last_action, philos->id);
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
	while (TRUE)
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
				print_state(vars, DIED, timestamp, philos->id);
				pthread_mutex_lock(&vars->print);
				return (NULL);
			}
			i++;
		}
		i = 0;
		while (vars->option_set == TRUE && i < vars->num_philos)
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

int	create_threads(t_vars *vars)
{
	ssize_t		i;
	ssize_t		timestamp;

	i = 0;
	timestamp = get_timestamp();
	while (i < vars->num_philos)
	{
		vars->philos[i].last_meal = timestamp;
		pthread_create(&vars->threads[i], NULL, &act_philos, &vars->philos[i]);
		i++;
	}
	pthread_create(&vars->observer, NULL, &observe_philos, vars);
	pthread_join(vars->observer, NULL);
	i = 0;
	while (i < vars->num_philos)
	{
		pthread_detach(vars->threads[i]);
		i++;
	}
	return (0);
}
