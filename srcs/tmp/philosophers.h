/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:07:10 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/12 23:07:26 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include	<pthread.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<limits.h>
# include	<sys/time.h>

# define TAKEN_A_FORK_MESSAGE "%zu %zu has taken a fork\n"
# define EATING_MESSAGE "%zu %zu is eating\n"
# define SLEEPING_MESSAGE "%zu %zu is sleeping\n"
# define THINKING_MESSAGE "%zu %zu is thinking\n"
# define DIED_MESSAGE "%zu %zu died\n"

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define USED 1
# define UNUSED 0

enum e_state {
	TAKEN_A_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_philos {
	ssize_t			id;
	enum e_state	state;
	ssize_t			action_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_vars	*vars;
}	t_philos;

typedef struct s_vars {
	ssize_t			philos_num;
	ssize_t			die_time;
	ssize_t			eat_time;
	ssize_t			sleep_time;
	int				option_arg;
	ssize_t			eat_num;
	pthread_mutex_t	*forks;
	t_philos		*philos;
}	t_vars;

int			init_setup(int argc, char **argv, t_vars *vars);
ssize_t		get_time(void);
ssize_t		get_time_diff(ssize_t old_time, ssize_t new_time);
void		create_threads(t_vars *vars);
void		print_state(enum e_state state, ssize_t timestamp, ssize_t id);

#endif
