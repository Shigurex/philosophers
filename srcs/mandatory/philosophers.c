/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:43:24 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/10 20:04:14 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

int	main(void)
{
	print_state(TAKEN_A_FORK);
	print_state(EATING);
	print_state(SLEEPING);
	print_state(THINKING);
	print_state(DIED);
	return (0);
}
