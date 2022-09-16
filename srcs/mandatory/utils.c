/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:11:30 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/16 15:08:06 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

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
	ssize_t	timestamp;

	timestamp = get_timestamp();
	while (get_timestamp() < time_end)
	{
		timestamp = get_timestamp();
		usleep(100);
	}
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
	return (value);
}

//ssize_t	get_time_diff(ssize_t old_timestamp, ssize_t new_timestamp)
//{
//	if (old_timestamp > new_timestamp)
//		return (ERROR);
//	return (new_timestamp - old_timestamp);
//}
