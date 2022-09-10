/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 19:48:32 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/10 20:03:17 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	print_state(enum e_state state)
{
	if (state == TAKEN_A_FORK)
		printf(TAKEN_A_FORK_MESSAGE, 100, 1);
	else if (state == EATING)
		printf(EATING_MESSAGE, 100, 1);
	else if (state == SLEEPING)
		printf(SLEEPING_MESSAGE, 100, 1);
	else if (state == THINKING)
		printf(THINKING_MESSAGE, 100, 1);
	else if (state == DIED)
		printf(DIED_MESSAGE, 100, 1);
}
