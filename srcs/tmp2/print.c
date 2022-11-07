/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 19:48:32 by yahokari          #+#    #+#             */
/*   Updated: 2022/11/04 19:46:17 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	print_state(t_vars *vars, t_state state, ssize_t timestamp, ssize_t id)
{
	ssize_t	time_passed;

	pthread_mutex_lock(&vars->print);
	time_passed = timestamp - vars->initial_time;
	if (state == TAKEN_A_FORK)
		printf(TAKEN_A_FORK_MESSAGE, time_passed, id);
	else if (state == EATING)
		printf(EATING_MESSAGE, time_passed, id);
	else if (state == SLEEPING)
		printf(SLEEPING_MESSAGE, time_passed, id);
	else if (state == THINKING)
		printf(THINKING_MESSAGE, time_passed, id);
	else if (state == DIED)
		printf(DIED_MESSAGE, time_passed, id);
	pthread_mutex_unlock(&vars->print);
}

void	record_action(t_vars *vars, t_philos *philos, t_state state)
{
	ssize_t	timestamp;
	ssize_t	id;

	id = philos->id;
	timestamp = get_timestamp();
	if (state == EATING)
		philos->num_ate++;
	if (state == INIT || state == EATING || state == SLEEPING)
		philos->last_meal = timestamp;
	if (state == INIT || state == EATING
		|| state == SLEEPING || state == THINKING || state == DIED)
		philos->last_action = timestamp;
	print_state(vars, state, timestamp, id);
}
