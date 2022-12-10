/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:06:11 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/10 18:47:14 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

static void	create_threads(t_vars *vars)
{
	ssize_t	i;

	i = 0;
	while (i < vars->num_philos)
	{
		pthread_create(&vars->threads[i], NULL, &act_philos, &vars->philos[i]);
		i++;
	}
	pthread_create(&vars->monitor, NULL, &monitor_philos, vars);
}

static void	delete_threads(t_vars *vars)
{
	ssize_t	i;

	pthread_join(vars->monitor, NULL);
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
}

void	exec_action(t_vars *vars)
{
	create_threads(vars);
	delete_threads(vars);
	destroy_mutex(vars);
}
