/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:48:44 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/14 19:42:33 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include	<semaphore.h>
# include	<pthread.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<limits.h>
# include	<stdbool.h>
# include	<signal.h>
# include	<sys/time.h>

# define ARGUMENT_ERROR "invalid argument\n"
# define MALLOC_ERROR "memory allocation failed\n"
# define SEMAPHORE_ERROR "semaphore failed\n"
# define FORK_ERROR "fork failed\n"

# define TAKEN_A_FORK_MESSAGE "%zu %zu has taken a fork\n"
# define EATING_MESSAGE "%zu %zu is eating\n"
# define SLEEPING_MESSAGE "%zu %zu is sleeping\n"
# define THINKING_MESSAGE "%zu %zu is thinking\n"
# define DIED_MESSAGE "%zu %zu died\n"

# define CHILD 0

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define USED 1
# define UNUSED 0

# define MILISECOND 1000

# define FORKS "forks"
# define PRINT "print"
# define CHECK_END "check_end"

typedef enum e_state {
	TAKEN_A_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	INIT,
	ACTIVE
}	t_state;

typedef struct s_philos {
	pid_t			pid;
	ssize_t			id;
	pthread_mutex_t	check;
	sem_t			*forks;
	sem_t			*print;
	ssize_t			last_meal;
	ssize_t			num_ate;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			initial_time;
	struct s_vars	*vars;
}	t_philos;

typedef struct s_vars {
	t_philos	*philos;
	sem_t		*forks;
	sem_t		*check_end;
	sem_t		*print;
	ssize_t		num_philos;
	ssize_t		time_to_die;
	ssize_t		time_to_eat;
	ssize_t		time_to_sleep;
	bool		option_set;
	ssize_t		num_must_eat;
	ssize_t		initial_time;
}	t_vars;

/* <-- setup_bonus.c --> */
int		init_setup(int argc, char **argv, t_vars *vars);

/* <-- execute_bonus.c --> */
void	exec_action(t_vars *vars);

/* <-- utils_bonus.c --> */
void	print_state(sem_t *print, t_state state, ssize_t timestamp, ssize_t id);
ssize_t	atoi_positive(const char *str);
ssize_t	get_timestamp(void);
void	wait_certain_time(ssize_t time_end);
void	exit_with_message(char *str);

void	*act_philo(void *p);

void	act_monitor(t_philos *philos, t_vars *vars);

void	philo_and_monitor(t_philos *philo);

#endif
