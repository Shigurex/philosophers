/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:16:19 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/12 00:58:06 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	eat_dish(t_philos *philos)
{
	
}

void	*thread_func(void *p)
{
	t_philos	*philos;

	philos = (t_philos *)p;
	// if (philos->id % 2 == 0)
	while (TRUE)
	{
		
		// if (philos->right_fork == UNUSED)
		// 	philos->right_fork = USED;
		// if (philos->left_fork == UNUSED)
		// 	philos->left_fork = USED;
	}
}

// void	create_forks(t_vars *vars)
// {
// 	vars->forks = malloc(sizeof(enum e_fork_state) * vars->num_philos);
	
// }

pthread_t	*create_threads(t_vars *vars)
{
	size_t		i;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * vars->philos_num);
	i = 0;
	while (i < vars->philos_num)
	{
		pthread_create(&threads[i], NULL, &thread_func, vars);
		i++;
	}
}
