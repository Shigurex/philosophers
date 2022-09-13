/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:49:53 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/13 20:57:12 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	*thread_func(void *p)
{
	t_philos	*philos;
	t_vars		*vars;

	philos = (t_philos *)p;
	vars = philos->vars;
	if (philos->id % 2 == 0)
		usleep(1000 * 10);
	while (TRUE)
	{
		pthread_mutex_lock(philos->right_fork);
		pthread_mutex_lock(philos->left_fork);
		print_state(vars, EATING, get_time(), philos->id);
		usleep(1000 * vars->time_to_eat);
		pthread_mutex_unlock(philos->right_fork);
		pthread_mutex_unlock(philos->left_fork);
		philos->num_ate++;
		if (philos->num_ate == vars->num_must_eat)
			break ;
		print_state(vars, SLEEPING, get_time(), philos->id);
		usleep(1000 * vars->time_to_sleep);
		print_state(vars, THINKING, get_time(), philos->id);
	}
	return (NULL);
}
