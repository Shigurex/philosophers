/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:32:50 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/10 18:16:21 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (init_setup(&vars, argc, argv))
		return (1);
	exec_action(&vars);
	return (0);
}
