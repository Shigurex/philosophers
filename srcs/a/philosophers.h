/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:41:14 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/10 19:47:28 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include	<pthread.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<limits.h>
# include	<stdbool.h>
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
	INIT
}	t_state;

typedef struct s_philos {
	ssize_t			id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_state			status;
	ssize_t			*last_meal;
	ssize_t			*num_ate;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			initial_time;
	pthread_mutex_t	print;
	pthread_mutex_t	*monitor_check;
}	t_philos;

typedef struct s_vars {
	t_philos		*philos;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	pthread_t		monitor;
	ssize_t			num_philos;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	bool			option_set;
	ssize_t			num_must_eat;
	ssize_t			initial_time;
	pthread_mutex_t	print;
	pthread_mutex_t	*monitor_check;
	ssize_t			*last_meal;
	ssize_t			*num_ate;
}	t_vars;

/* setup.c */
int		init_setup(t_vars *vars, int argc, char **argv);

/* execute.c */
void	exec_action(t_vars *vars);

/* philos.c */
void	*act_philos(void *p);

/* monitor.c */
void	*monitor_philos(void *p);

/* util.c */
void	print_state(pthread_mutex_t *print, t_state state, ssize_t timestamp, ssize_t id);
ssize_t	get_timestamp(void);
void	wait_certain_time(ssize_t time_end);
ssize_t	atoi_positive(const char *str);

#endif
