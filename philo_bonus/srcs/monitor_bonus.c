/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:19:58 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/15 16:46:34 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers_bonus.h"

static void	check_death(t_philos *philo, t_vars *vars, int id)
{
	ssize_t	time_of_death;
	ssize_t	timestamp;
	ssize_t	i;

	timestamp = get_timestamp();
	sem_wait(philo->check);
	time_of_death = philo->last_meal + vars->time_to_die;
	sem_post(philo->check);
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
	sem_wait(philo->check);
	if (philo->num_ate >= vars->num_must_eat && is_sem_post_sent == false)
	{
		sem_post(vars->check_end);
		is_sem_post_sent = true;
	}
	sem_post(philo->check);
}

static void	act_monitor(t_philos *philo, t_vars *vars)
{
	int	id;

	id = philo->id;
	while (true)
	{
		check_death(philo, vars, id);
		check_eaten(philo, vars);
		usleep(MILISECOND);
	}
}

void	philo_and_monitor(t_philos *philo)
{
	t_vars		*vars;
	pthread_t	thread;

	vars = philo->vars;
	pthread_create(&thread, NULL, &act_philo, philo);
	act_monitor(philo, vars);
	pthread_detach(thread);
}
