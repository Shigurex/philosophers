/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:19:58 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/15 16:12:45 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers_bonus.h"

static void	check_death(t_philos *philo, t_vars *vars, int id)
{
	ssize_t	time_of_death;
	ssize_t	timestamp;
	ssize_t	i;

	timestamp = get_timestamp();
	pthread_mutex_lock(&philo->check);
	time_of_death = philo->last_meal + vars->time_to_die;
	pthread_mutex_unlock(&philo->check);
	if (timestamp >= time_of_death)
	{
		print_state(vars->print, DIED, timestamp - vars->initial_time, id);
		i = 0;
		while (i < vars->num_philos)
		{
			sem_post(vars->check_end);
			i++;
		}
	}
}

static void	check_eaten(t_philos *philo, t_vars *vars)
{
	static bool	is_sem_post_sent;

	if (vars->option_set == false)
		return ;
	pthread_mutex_lock(&philo->check);
	if (philo->num_ate >= vars->num_must_eat && is_sem_post_sent == false)
	{
		sem_post(vars->check_end);
		is_sem_post_sent = true;
	}
	pthread_mutex_unlock(&philo->check);
}

void	act_monitor(t_philos *philo, t_vars *vars)
{
	int	id;

	pthread_mutex_lock(&philo->check);
	id = philo->id;
	pthread_mutex_unlock(&philo->check);
	while (true)
	{
		check_death(philo, vars, id);
		check_eaten(philo, vars);
		usleep(MILISECOND);
	}
}
