/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:50:39 by yahokari          #+#    #+#             */
/*   Updated: 2022/11/07 18:18:37 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (init_setup(argc, argv, &vars))
		return (1);
	exec_action(&vars);
	return (0);
}
