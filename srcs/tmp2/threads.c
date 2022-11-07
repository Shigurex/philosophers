/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 01:31:02 by yahokari          #+#    #+#             */
/*   Updated: 2022/11/04 19:43:32 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	create_threads(t_vars *vars)
{
	ssize_t	i;

	i = 0;
	while (i < vars->num_philos)
	{
		pthread_create(&vars->threads[i], NULL, &act_philos, &vars->philos[i]);
		i++;
	}
	//pthread_create(&vars->observer, NULL, &observe_philos, &vars);
}

void	delete_threads(t_vars *vars)
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

int	exec_action(t_vars *vars)
{
	ssize_t	timestamp;

	timestamp = get_timestamp();
	vars->initial_time = timestamp;
	create_threads(vars);
	pthread_join(vars->threads[0], NULL);
	//delete_threads(vars);
	return (0);
}
