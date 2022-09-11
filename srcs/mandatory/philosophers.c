/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:43:24 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/11 00:29:24 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	*thread_func(void *vars)
{
	
}

pthread_t	*create_threads(t_vars *vars)
{
	size_t		i;
	pthread_t	*threads;

	threads = malloc(sizeof(threads) * vars->num_philos);
	i = 0;
	while (i < vars->num_philos)
	{
		pthread_create(&threads[i], NULL, &thread_func, vars);
		i++;
	}
}



int	main(void)
{
	print_state(TAKEN_A_FORK);
	print_state(EATING);
	print_state(SLEEPING);
	print_state(THINKING);
	print_state(DIED);
	return (0);
}
