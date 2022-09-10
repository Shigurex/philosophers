/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 19:40:58 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/10 20:01:55 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define TAKEN_A_FORK_MESSAGE "%d %d has taken a fork\n"
# define EATING_MESSAGE "%d %d is eating\n"
# define SLEEPING_MESSAGE "%d %d is sleeping\n"
# define THINKING_MESSAGE "%d %d is thinking\n"
# define DIED_MESSAGE "%d %d died\n"

typedef struct s_vars {
	size_t	num_philos;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	size_t	num_eat;
}	t_vars;

enum e_state {
	TAKEN_A_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

void	print_state(enum e_state state);

#endif
