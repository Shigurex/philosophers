/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:54:54 by yahokari          #+#    #+#             */
/*   Updated: 2022/11/07 18:05:36 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

static void	create_threads(t_vars *vars)
{
	ssize_t	i;

	i = 0;
	pthread_mutex_lock(vars->check);
	while (i < vars->num_philos)
	{
		pthread_create(&vars->threads[i], NULL, &act_philos, &vars->philos[i]);
		i++;
	}
	pthread_mutex_unlock(vars->check);
	pthread_create(&vars->observer, NULL, &observe_philos, vars);
}

static void	delete_threads(t_vars *vars)
{
	ssize_t	i;

	pthread_join(vars->observer, NULL);
	i = 0;
	while (i < vars->num_philos)
	{
		pthread_detach(vars->threads[i]);
		i++;
	}
}

static void	destroy_mutex(t_vars *vars)
{
	ssize_t	i;

	i = 0;
	while (i < vars->num_philos)
	{
		pthread_mutex_destroy(&vars->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&vars->print);
	pthread_mutex_destroy(vars->check);
}

void	exec_action(t_vars *vars)
{
	ssize_t	timestamp;

	vars->initial_time = get_timestamp();
	create_threads(vars);
	delete_threads(vars);
	destroy_mutex(vars);
}
