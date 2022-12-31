/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:16:29 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 10:41:49 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers_bonus.h"

static void	check_argument(int argc, char **argv, t_vars *vars)
{
	if (argc == 5)
		vars->option_set = false;
	else if (argc == 6)
		vars->option_set = true;
	else
		exit(EXIT_FAILURE);
	vars->num_philos = atoi_positive(argv[1]);
	vars->time_to_die = atoi_positive(argv[2]);
	vars->time_to_eat = atoi_positive(argv[3]);
	vars->time_to_sleep = atoi_positive(argv[4]);
	if (vars->option_set == true)
		vars->num_must_eat = atoi_positive(argv[5]);
	if (vars->num_philos == ERROR || vars->time_to_die == ERROR
		|| vars->time_to_eat == ERROR || vars->time_to_sleep == ERROR
		|| (vars->option_set == true && vars->num_must_eat == ERROR))
		exit(EXIT_FAILURE);
}

static void	init_semaphore(t_vars *vars)
{
	vars->forks = sem_open("a", O_CREAT, 0644, 1);
	if (vars->forks == SEM_FAILED)
		exit(EXIT_FAILURE);
}

static void	init_philos(t_vars *vars)
{
	ssize_t	i;

	vars->initial_time = get_timestamp() + 1000;
	vars->philos = malloc(sizeof(t_philos) * vars->num_philos);
	if (!vars->philos)
	{
		free(vars->forks);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < vars->num_philos)
	{
		vars->philos[i].id = i + 1;
		vars->philos[i].forks = vars->forks;
		vars->philos[i].status = INIT;
		vars->philos[i].num_ate = 0;
		vars->philos[i].time_to_eat = vars->time_to_eat;
		vars->philos[i].time_to_sleep = vars->time_to_sleep;
		vars->philos[i].initial_time = vars->initial_time;
		vars->philos[i].vars = vars;
		i++;
	}
}

int	init_setup(int argc, char **argv, t_vars *vars)
{
	check_argument(argc, argv, vars);
	init_semaphore(vars);
	init_philos(vars);
	return (0);
}
