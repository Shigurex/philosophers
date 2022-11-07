/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:37:48 by yahokari          #+#    #+#             */
/*   Updated: 2022/11/07 15:36:30 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

static bool	is_action_finished(t_vars *vars)
{
	size_t		i;
	t_philos	*philos;
	ssize_t		timestamp;
	bool		all_ate_flag;

	i = 0;
	all_ate_flag = true;
	while (i < vars->num_philos)
	{
		pthread_mutex_lock(vars->check);
		philos = &vars->philos[i];
		timestamp = get_timestamp();
		if (philos->status != INIT
			&& timestamp >= philos->last_meal + vars->time_to_die)
		{
			print_state(vars, DIED, timestamp, philos->id);
			pthread_mutex_unlock(vars->check);
			return (true);
		}
		if (vars->option_set == false
			|| philos->num_ate < vars->num_must_eat)
			all_ate_flag = false;
		pthread_mutex_unlock(vars->check);
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
	printf("%zd\n", vars->philos[0].num_ate);
	return (NULL);
}
