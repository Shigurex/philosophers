/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:26:51 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/14 22:56:50 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

static int	check_argument(int argc, char **argv, t_vars *vars)
{
	if (argc == 5)
		vars->option_set = FALSE;
	else if (argc == 6)
		vars->option_set = TRUE;
	else
		return (1);
	vars->num_philos = atoi_positive(argv[1]);
	vars->time_to_die = atoi_positive(argv[2]);
	vars->time_to_eat = atoi_positive(argv[3]);
	vars->time_to_sleep = atoi_positive(argv[4]);
	if (vars->option_set == TRUE)
		vars->num_must_eat = atoi_positive(argv[5]);
	if (vars->num_philos == ERROR || vars->time_to_die == ERROR
		|| vars->time_to_eat == ERROR || vars->time_to_sleep == ERROR
		|| (vars->option_set == TRUE && vars->num_must_eat == ERROR))
		return (1);
	return (0);
}

static int	init_mutexes(t_vars *vars)
{
	ssize_t	i;

	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->num_philos);
	if (!vars->forks)
		return (1);
	i = 0;
	while (i < vars->num_philos)
	{
		pthread_mutex_init(&(vars->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(vars->print), NULL);
	return (0);
}

static int	init_philos(t_vars *vars)
{
	ssize_t	i;

	vars->philos = malloc(sizeof(t_philos) * vars->num_philos);
	if (!vars->philos)
	{
		free(vars->forks);
		return (1);
	}
	i = 0;
	while (i < vars->num_philos)
	{
		vars->philos[i].id = i + 1;
		vars->philos[i].right_fork = &vars->forks[i % vars->num_philos];
		vars->philos[i].left_fork = &vars->forks[(i + 1) % vars->num_philos];
		vars->philos[i].num_ate = 0;
		vars->philos[i].vars = vars;
		i++;
	}
	return (0);
}

static int	init_threads(t_vars *vars)
{
	vars->threads = malloc(sizeof(pthread_t) * vars->num_philos);
	if (!vars->threads)
	{
		free(vars->forks);
		free(vars->philos);
		return (1);
	}
	vars->observer = malloc(sizeof(pthread_t));
	if (!vars->observer)
	{
		free(vars->forks);
		free(vars->philos);
		free(vars->threads);
		return (1);
	}
	return (0);
}

int	init_setup(int argc, char **argv, t_vars *vars)
{
	if (check_argument(argc, argv, vars))
		return (1);
	if (init_mutexes(vars))
		return (1);
	if (init_philos(vars))
		return (1);
	if (init_threads(vars))
		return (1);
	return (0);
}
