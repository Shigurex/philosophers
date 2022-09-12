/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:16:19 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/12 12:54:41 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	*thread_func(void *p)
{
	t_philos	*philos;
	t_vars		*vars;

	philos = (t_philos *)p;
	vars = philos->vars;
	// if (philos->id % 2 == 0)
	// 	usleep(200);
	pthread_mutex_lock(philos->right_fork);
	pthread_mutex_lock(philos->left_fork);
	print_state(EATING, philos->id, get_time());
	usleep(1000 * vars->eat_time);
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
	print_state(SLEEPING, philos->id, get_time());
	usleep(1000 * vars->sleep_time);
	print_state(THINKING, philos->id, get_time());
	return (NULL);
}

// void	create_forks(t_vars *vars)
// {
// 	vars->forks = malloc(sizeof(enum e_fork_state) * vars->num_philos);
	
// }

void	create_threads(t_vars *vars)
{
	ssize_t		i;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * vars->philos_num);
	i = 0;
	while (i < vars->philos_num)
	{
		pthread_create(&threads[i], NULL, &thread_func, vars);
		i++;
	}
	i = 0;
	while (i < vars->philos_num)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
