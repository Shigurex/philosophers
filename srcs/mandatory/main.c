/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:32:50 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/19 16:18:11 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

static int	init_setup(t_vars *vars, int argc, char **argv)
{
	if (check_argument(vars, argc, argv))
		return (1);
	if (init_mutexes(vars))
		return (1);
	if (init_philos(vars))
		return (1);
	if (init_threads(vars))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (init_setup(&vars, argc, argv))
		return (1);
	exec_action(&vars);
	return (0);
}
