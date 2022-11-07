/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:48:03 by yahokari          #+#    #+#             */
/*   Updated: 2022/11/07 17:22:51 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	init_setup(argc, argv, &vars);
	exec_action(&vars);
	return (0);
}
