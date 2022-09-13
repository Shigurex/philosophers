/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:43:24 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/13 20:20:24 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (init_setup(argc, argv, &vars))
		return (1);
	// create_threads(&vars);
	return (0);
}
