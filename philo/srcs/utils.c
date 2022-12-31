/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:11:30 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/19 16:26:46 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	print_state(pthread_mutex_t *print, t_state state, \
	ssize_t timestamp, ssize_t id)
{
	pthread_mutex_lock(print);
	if (state == TAKEN_A_FORK)
		printf(TAKEN_A_FORK_MESSAGE, timestamp, id);
	else if (state == EATING)
		printf(EATING_MESSAGE, timestamp, id);
	else if (state == SLEEPING)
		printf(SLEEPING_MESSAGE, timestamp, id);
	else if (state == THINKING)
		printf(THINKING_MESSAGE, timestamp, id);
	else if (state == DIED)
		printf(DIED_MESSAGE, timestamp, id);
	pthread_mutex_unlock(print);
}

ssize_t	get_timestamp(void)
{
	struct timeval	current_time;
	ssize_t			time_msec;

	if (gettimeofday(&current_time, NULL))
		return (ERROR);
	time_msec = current_time.tv_sec * 1000;
	time_msec += current_time.tv_usec / 1000;
	return (time_msec);
}

void	wait_certain_time(ssize_t time_end)
{
	while (get_timestamp() < time_end)
		usleep(100);
}

ssize_t	atoi_positive(const char *str)
{
	size_t	i;
	ssize_t	value;

	i = 0;
	value = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (ERROR);
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
		{
			value = 10 * value + (str[i] - '0');
			if (value > (ssize_t)INT_MAX)
				return (ERROR);
			i++;
		}
		else
			return (ERROR);
	}
	if (value == 0)
		return (ERROR);
	return (value);
}
