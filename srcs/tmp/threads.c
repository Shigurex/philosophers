/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:07:39 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/12 23:07:51 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	eat_dish(t_philos *philos)
{
	
}

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
		print_state(EATING, get_time(), philos->id);
		usleep(1000 * vars->eat_time);
		pthread_mutex_unlock(philos->right_fork);
		pthread_mutex_unlock(philos->left_fork);
		print_state(SLEEPING, get_time(), philos->id);
		usleep(1000 * vars->sleep_time);
		print_state(THINKING, get_time(), philos->id);
	}
	return (NULL);
}

void	create_threads(t_vars *vars)
{
	ssize_t		i;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * vars->philos_num);
	i = 0;
	while (i < vars->philos_num)
	{
		pthread_create(&threads[i], NULL, &thread_func, &vars->philos[i]);
		i++;
	}
	i = 0;
	while (i < vars->philos_num)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
