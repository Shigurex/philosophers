/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:11:30 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/12 15:39:23 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

ssize_t	get_time(void)
{
	struct timeval	current_time;
	ssize_t			time_msec;

	if (gettimeofday(&current_time, NULL))
		return (ERROR);
	time_msec = current_time.tv_sec * 1000;
	time_msec += current_time.tv_usec / 1000;
	return (time_msec);
}

ssize_t	get_time_diff(ssize_t old_time, ssize_t new_time)
{
	if (old_time > new_time)
		return (ERROR);
	return (new_time - old_time);
}
