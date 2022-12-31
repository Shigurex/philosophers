/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:48:03 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 10:41:34 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	init_setup(argc, argv, &vars);
	printf("%s, %d\n", __FILE__, __LINE__);
	exec_action(&vars);
	return (0);
}