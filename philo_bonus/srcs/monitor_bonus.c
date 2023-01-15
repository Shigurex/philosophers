/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:19:58 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/15 17:41:22 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers_bonus.h"

static void	check_death(t_vars *vars, int id)
{
	ssize_t	time_of_death;
	ssize_t	timestamp;
	ssize_t	i;

	timestamp = get_timestamp();
	sem_wait(vars->philos[id - 1].check);
	time_of_death = vars->philos[id - 1].last_meal + vars->time_to_die;
	sem_post(vars->philos[id - 1].check);
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

static void	check_eaten(t_vars *vars, ssize_t id)
{
	static bool	is_sem_post_sent;

	if (vars->option_set == false)
		return ;
	sem_wait(vars->philos[id - 1].check);
	if (vars->philos[id - 1].num_ate >= vars->num_must_eat \
		&& is_sem_post_sent == false)
	{
		sem_post(vars->check_end);
		is_sem_post_sent = true;
	}
	sem_post(vars->philos[id - 1].check);
}

static void	act_monitor(t_vars *vars, ssize_t id)
{
	while (true)
	{
		check_death(vars, id);
		check_eaten(vars, id);
		usleep(MILISECOND);
	}
}

void	philo_and_monitor(t_philos *philo)
{
	t_vars		*vars;
	pthread_t	thread;
	ssize_t		id;

	vars = philo->vars;
	id = philo->id;
	pthread_create(&thread, NULL, &act_philo, philo);
	act_monitor(vars, id);
	pthread_detach(thread);
}
