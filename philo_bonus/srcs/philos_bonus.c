/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 10:46:51 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 11:56:38 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers_bonus.h"

// void	act_philo(t_philos *philo)
// {
// 	;
// }

// void	act_monitor(t_vars *vars, t_philos *philo)
// {
// 	;
// }

void	philo_and_monitor(t_philos *philo)
{
	t_vars	*vars;

	vars = philo->vars;
	printf("%s, %d\n", __FILE__, __LINE__);
}
