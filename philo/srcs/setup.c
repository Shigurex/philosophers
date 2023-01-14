/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:36:58 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/14 15:58:24 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

int	check_argument(t_vars *vars, int argc, char **argv)
{
	if (argc == 5)
		vars->option_set = false;
	else if (argc == 6)
		vars->option_set = true;
	else
		return (1);
	vars->num_philos = atoi_positive(argv[1]);
	vars->time_to_die = atoi_positive(argv[2]);
	vars->time_to_eat = atoi_positive(argv[3]);
	vars->time_to_sleep = atoi_positive(argv[4]);
	if (vars->option_set == true)
		vars->num_must_eat = atoi_positive(argv[5]);
	if (vars->num_philos == ERROR || vars->time_to_die == ERROR
		|| vars->time_to_eat == ERROR || vars->time_to_sleep == ERROR
		|| (vars->option_set == true && vars->num_must_eat == ERROR))
		return (1);
	return (0);
}

int	init_mutexes(t_vars *vars)
{
	ssize_t	i;

	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->num_philos);
	vars->monitor_check = malloc(sizeof(pthread_mutex_t) * vars->num_philos);
	if (!vars->forks || !vars->monitor_check)
	{
		free(vars->forks);
		free(vars->monitor_check);
		return (1);
	}
	i = 0;
	while (i < vars->num_philos)
	{
		pthread_mutex_init(&vars->forks[i], NULL);
		pthread_mutex_init(&vars->monitor_check[i], NULL);
		i++;
	}
	pthread_mutex_init(&vars->print, NULL);
	return (0);
}

static void	init_philos_structure(t_vars *vars, ssize_t i)
{
	vars->philos[i].id = i + 1;
	vars->philos[i].right_fork = &vars->forks[i];
	vars->philos[i].left_fork = &vars->forks[(i + 1) % vars->num_philos];
	vars->last_meal[i] = vars->initial_time;
	vars->philos[i].last_meal = &vars->last_meal[i];
	vars->num_ate[i] = 0;
	vars->philos[i].num_ate = &vars->num_ate[i];
	vars->philos[i].time_to_eat = vars->time_to_eat;
	vars->philos[i].time_to_sleep = vars->time_to_sleep;
	vars->philos[i].initial_time = vars->initial_time;
	vars->philos[i].print = &vars->print;
	vars->philos[i].monitor_check = &vars->monitor_check[i];
}

int	init_philos(t_vars *vars)
{
	ssize_t	i;

	vars->initial_time = get_timestamp() + 1000;
	vars->philos = malloc(sizeof(t_philos) * vars->num_philos);
	vars->last_meal = malloc(sizeof(ssize_t) * vars->num_philos);
	vars->num_ate = malloc(sizeof(ssize_t) * vars->num_philos);
	if (!vars->philos || !vars->last_meal || !vars->num_ate)
	{
		free(vars->forks);
		free(vars->monitor_check);
		free(vars->philos);
		free(vars->last_meal);
		free(vars->num_ate);
		return (1);
	}
	i = 0;
	while (i < vars->num_philos)
	{
		init_philos_structure(vars, i);
		i++;
	}
	return (0);
}

int	init_threads(t_vars *vars)
{
	vars->threads = malloc(sizeof(pthread_t) * vars->num_philos);
	if (!vars->threads)
	{
		free(vars->forks);
		free(vars->monitor_check);
		free(vars->philos);
		free(vars->last_meal);
		free(vars->num_ate);
		return (1);
	}
	return (0);
}
