/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 19:06:05 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/12 13:54:36 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

static ssize_t	atoi_positive(const char *str)
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

static int	check_argument(int argc, char **argv, t_vars *vars)
{
	if (argc < 5 || 6 < argc)
		return (FALSE);
	vars->philos_num = atoi_positive(argv[1]);
	vars->die_time = atoi_positive(argv[2]);
	vars->eat_time = atoi_positive(argv[3]);
	vars->sleep_time = atoi_positive(argv[4]);
	if (argc == 6)
	{
		vars->option_arg = TRUE;
		vars->eat_num = atoi_positive(argv[5]);
	}
	if (vars->philos_num == ERROR || vars->die_time == ERROR
		|| vars->eat_time == ERROR || vars->sleep_time == ERROR
		|| (vars->option_arg == TRUE && vars->eat_num == ERROR))
		return (1);
	return (0);
}

static int	init_forks(t_vars *vars)
{
	ssize_t	i;

	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->philos_num);
	if (!vars->forks)
		return (1);
	i = 0;
	while (i < vars->philos_num)
	{
		pthread_mutex_init(&(vars->forks[i]), NULL);
		i++;
	}
	return (0);
}

static int	init_philos(t_vars *vars)
{
	ssize_t	i;

	vars->philos = malloc(sizeof(t_philos) * vars->philos_num);
	if (!vars->philos)
		return (1);
	i = 0;
	while (i < vars->philos_num)
	{
		vars->philos[i].id = i + 1;
		vars->philos[i].right_fork = &vars->forks[i % vars->philos_num];
		vars->philos[i].left_fork = &vars->forks[(i + 1) % vars->philos_num];
		vars->philos[i].vars = vars;
		i++;
	}
	return (0);
}

int	init_setup(int argc, char **argv, t_vars *vars)
{
	if (check_argument(argc, argv, vars))
		return (1);
	if (init_forks(vars))
		return (1);
	if (init_philos(vars))
		return (1);
	return (0);
}
