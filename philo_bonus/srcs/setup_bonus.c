/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:16:29 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/15 17:05:42 by yahokari         ###   ########.fr       */
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
		exit_with_message(ARGUMENT_ERROR);
	vars->num_philos = atoi_positive(argv[1]);
	vars->time_to_die = atoi_positive(argv[2]);
	vars->time_to_eat = atoi_positive(argv[3]);
	vars->time_to_sleep = atoi_positive(argv[4]);
	if (vars->option_set == true)
		vars->num_must_eat = atoi_positive(argv[5]);
	if (vars->num_philos == ERROR || vars->time_to_die == ERROR
		|| vars->time_to_eat == ERROR || vars->time_to_sleep == ERROR
		|| (vars->option_set == true && vars->num_must_eat == ERROR))
		exit_with_message(ARGUMENT_ERROR);
}

static void	init_semaphore(t_vars *vars)
{
	sem_unlink(FORKS);
	vars->forks = sem_open(FORKS, O_CREAT, 0644, vars->num_philos);
	if (vars->forks == SEM_FAILED)
		exit_with_message(SEMAPHORE_ERROR);
	sem_unlink(PRINT);
	vars->print = sem_open(PRINT, O_CREAT, 0644, 1);
	if (vars->print == SEM_FAILED)
		exit_with_message(SEMAPHORE_ERROR);
	sem_unlink(CHECK_END);
	vars->check_end = sem_open(CHECK_END, O_CREAT, 0644, 0);
	if (vars->check_end == SEM_FAILED)
		exit_with_message(SEMAPHORE_ERROR);
}

void	init_sem_check(t_philos *philo)
{
	char	*name;

	name = (ft_itoa(philo->id));
	if (!name)
		exit_with_message(MALLOC_ERROR);
	sem_unlink(name);
	philo->check = sem_open(name, O_CREAT, 0644, 1);
	free(name);
	if (philo->check == SEM_FAILED)
		exit_with_message(SEMAPHORE_ERROR);
}

static void	init_philos(t_vars *vars)
{
	ssize_t	i;

	vars->initial_time = get_timestamp() + 1000;
	vars->philos = malloc(sizeof(t_philos) * vars->num_philos);
	if (!vars->philos)
		exit_with_message(MALLOC_ERROR);
	i = 0;
	while (i < vars->num_philos)
	{
		vars->philos[i].id = i + 1;
		sem_unlink(CHECK_END);
		init_sem_check(&vars->philos[i]);
		vars->philos[i].forks = vars->forks;
		vars->philos[i].print = vars->print;
		vars->philos[i].last_meal = vars->initial_time;
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
