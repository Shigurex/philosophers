/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 19:40:58 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/11 21:12:49 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include	<pthread.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<limits.h>
# include	<sys/time.h>

# define TAKEN_A_FORK_MESSAGE "%d %d has taken a fork\n"
# define EATING_MESSAGE "%d %d is eating\n"
# define SLEEPING_MESSAGE "%d %d is sleeping\n"
# define THINKING_MESSAGE "%d %d is thinking\n"
# define DIED_MESSAGE "%d %d died\n"

# define TRUE 1
# define FALSE 0
# define ERROR -1

enum e_fork_state {
	USED,
	UNUSED
};

enum e_state {
	TAKEN_A_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_philos {
	ssize_t				id;
	enum e_fork_state	*right_fork;
	enum e_fork_state	*left_fork;
}	t_philos;

typedef struct s_vars {
	ssize_t				philos_num;
	ssize_t				die_time;
	ssize_t				eat_time;
	ssize_t				sleep_time;
	int					option_arg;
	ssize_t				eat_num;
	enum e_fork_state	*forks;
	t_philos			*philos;
}	t_vars;

int		init_setup(int argc, char **argv, t_vars *vars);
ssize_t	get_time(void);
void	print_state(enum e_state state);

#endif
