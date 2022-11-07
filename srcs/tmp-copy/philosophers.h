/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:07:10 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/16 14:48:41 by yahokari         ###   ########.fr       */
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

# define MILISECOND 1000

typedef enum e_state {
	TAKEN_A_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	NONE
}	t_state;

typedef struct s_philos {
	ssize_t			id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_state			status;
	ssize_t			last_meal;
	ssize_t			last_action;
	ssize_t			num_ate;
	struct s_vars	*vars;
}	t_philos;

typedef struct s_vars {
	t_philos		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_t		*threads;
	pthread_t		observer;
	ssize_t			num_philos;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	int				option_set;
	ssize_t			num_must_eat;
}	t_vars;

// <-- action.c -->
int		create_threads(t_vars *vars);

// <-- setup.c -->
int		init_setup(int argc, char **argv, t_vars *vars);

// <-- state.c -->
void	print_state(t_vars *vars, t_state state, ssize_t timestamp, ssize_t id);

// <-- utils.c -->
ssize_t	atoi_positive(const char *str);
ssize_t	get_timestamp(void);
void	wait_certain_time(ssize_t time_end);

//typedef struct s_philos {
//	ssize_t			id;
//	enum e_state	state;
//	ssize_t			action_time;
//	pthread_mutex_t	*right_fork;
//	pthread_mutex_t	*left_fork;
//	struct s_vars	*vars;
//}	t_philos;

//typedef struct s_vars {
//	ssize_t			philos_num;
//	ssize_t			die_time;
//	ssize_t			eat_time;
//	ssize_t			sleep_time;
//	int				option_arg;
//	ssize_t			eat_num;
//	pthread_mutex_t	*forks;
//	t_philos		*philos;
//}	t_vars;

#endif