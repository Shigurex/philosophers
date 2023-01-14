/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 10:46:51 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/12 13:51:26 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers_bonus.h"

static void	eat_meal(t_philos *philo)
{
	ssize_t	eat_start;

	sem_wait(philo->forks);
	print_state(TAKEN_A_FORK, get_timestamp() - philo->initial_time, philo->id);
	sem_wait(philo->forks);
	print_state(TAKEN_A_FORK, get_timestamp() - philo->initial_time, philo->id);
	eat_start = get_timestamp();
	philo->last_meal = eat_start;
	print_state(EATING, eat_start - philo->initial_time, philo->id);
	wait_certain_time(eat_start + philo->time_to_eat);
	philo->num_ate++;
	sem_post(philo->forks);
	sem_post(philo->forks);
}

static void	sleep_philos(t_philos *philos)
{
	ssize_t	sleep_start;

	sleep_start = get_timestamp();
	print_state(SLEEPING, sleep_start - philos->initial_time, philos->id);
	wait_certain_time(sleep_start + philos->time_to_sleep);
}

static void	think_philos(t_philos *philos)
{
	print_state(THINKING, get_timestamp() - philos->initial_time, philos->id);
}

void	act_philo(void *p)
{
	t_philos	*philos;

	philos = (t_philos *)p;
	wait_certain_time(philos->initial_time);
	if (philos->id % 2 == 0)
		usleep(philos->time_to_eat * MILISECOND / 2);
	while (true)
	{
		eat_meal(philos);
		sleep_philos(philos);
		think_philos(philos);
	}
}

// void	act_monitor(t_vars *vars, t_philos *philo)
// {
// 	;
// }

void	philo_and_monitor(t_philos *philo)
{
	t_vars	*vars;

	vars = philo->vars;
	(void)vars;
	printf("%s, %d\n", __FILE__, __LINE__);
	sem_wait(philo->forks);
	printf("%s, %d\n", __FILE__, __LINE__);
	sem_wait(philo->forks);
	printf("%s, %d\n", __FILE__, __LINE__);
	//act_philo(philo);
}
