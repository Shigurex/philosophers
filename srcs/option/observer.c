/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:37:48 by yahokari          #+#    #+#             */
/*   Updated: 2022/11/07 21:24:47 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

static bool	check_death(t_vars *vars, t_philos *philos)
{
	ssize_t		time_of_death;
	ssize_t		timestamp;

	timestamp = get_timestamp();
	if (philos->status == INIT)
		time_of_death = vars->initial_time + vars->time_to_die;
	else
		time_of_death = philos->last_meal + vars->time_to_die;
	if (timestamp >= time_of_death)
	{
		print_state(vars, DIED, timestamp, philos->id);
		return (true);
	}
	return (false);
}

static bool	is_action_finished(t_vars *vars)
{
	ssize_t		i;
	t_philos	*philos;
	bool		all_ate_flag;

	i = 0;
	all_ate_flag = true;
	while (i < vars->num_philos)
	{
		philos = &vars->philos[i];
		pthread_mutex_lock(&vars->check);
		if (check_death(vars, philos))
			return (true);
		if (vars->option_set == false
			|| philos->num_ate < vars->num_must_eat)
			all_ate_flag = false;
		pthread_mutex_unlock(&vars->check);
		i++;
	}
	return (all_ate_flag);
}

void	*observe_philos(void *p)
{
	t_vars		*vars;

	vars = (t_vars *)p;
	while (true)
	{
		if (is_action_finished(vars))
			break ;
	}
	pthread_mutex_lock(&vars->print);
	return (NULL);
}
