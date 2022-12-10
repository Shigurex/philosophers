/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:24:33 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/10 19:46:11 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

static bool	check_death(t_vars *vars, ssize_t i)
{
	ssize_t		time_of_death;
	ssize_t		timestamp;

	timestamp = get_timestamp();
	//pthread_mutex_lock(&vars->monitor_check[i]);
	time_of_death = vars->last_meal[i] + vars->time_to_die;
	//pthread_mutex_unlock(&vars->monitor_check[i]);
	if (timestamp >= time_of_death)
	{
		print_state(&vars->print, DIED, timestamp, i + 1);
		return (true);
	}
	return (false);
}

static bool	is_action_finished(t_vars *vars)
{
	ssize_t		i;
	bool		all_ate_flag;

	i = 0;
	all_ate_flag = true;
	while (i < vars->num_philos)
	{
		pthread_mutex_lock(&vars->monitor_check[i]);
		if (check_death(vars, i))
			return (true);
		if (vars->option_set == false
			|| vars->num_ate[i] < vars->num_must_eat)
			all_ate_flag = false;
		pthread_mutex_unlock(&vars->monitor_check[i]);
		i++;
	}
	return (all_ate_flag);
}

void	*monitor_philos(void *p)
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
