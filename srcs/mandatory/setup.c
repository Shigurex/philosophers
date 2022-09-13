/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:26:51 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/12 23:42:59 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

int	init_setup(int argc, char **argv, t_vars *vars)
{
	if (check_argument(argc, argv, vars))
		return (1);
	if (init_forks(vars))
		return (1);
	if (init_philos(vars))
	{
		free(vars->forks);
		return (1);
	}
	return (0);
}
