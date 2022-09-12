/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 19:48:32 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/12 12:01:28 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	print_state(enum e_state state, ssize_t timestamp, ssize_t id)
{
	if (state == TAKEN_A_FORK)
		printf(TAKEN_A_FORK_MESSAGE, timestamp, id);
	else if (state == EATING)
		printf(EATING_MESSAGE, timestamp, id);
	else if (state == SLEEPING)
		printf(SLEEPING_MESSAGE, timestamp, id);
	else if (state == THINKING)
		printf(THINKING_MESSAGE, timestamp, id);
	else if (state == DIED)
		printf(DIED_MESSAGE, timestamp, id);
}
