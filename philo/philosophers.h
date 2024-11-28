/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:47 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/28 09:58:25 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING
}						t_state;

// Simulation params
typedef struct s_params
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_count;
	struct s_simulation	*sim;
}						t_params;

// Philo struct
typedef struct s_philo
{
	int					philo_id;
	int					meals_eaten;
	long				last_meal_time;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	t_params			*params;
	t_state				state;
}						t_philo;

typedef struct s_simulation
{
	int					simulation_stopped;
	t_params			*params;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	long				start_time;
}						t_simulation;

/************
***PARSING***
*************/

void					parse_input(t_simulation *sim, int argc, char **argv);
int						parse_args(const char *argv);
int						is_integer(const char *str);
void					init_args(t_simulation *sim, int argc, char **argv);

/**********
***UTILS***
***********/

int						ft_atoi(const char *str);
int						is_digit(const char c);
long					get_current_time(void);

/*********
***INIT***
**********/

void					init_simulation(t_simulation *sim);
void					init_forks(t_simulation *sim);
void					init_philo(t_simulation *sim);
// void					init_params(t_simulation *sim);

/**********
**ROUTINE**
***********/

void					*philo_routine(void *arg);
void					philo_sleep_and_think(t_philo *philo);
void					philo_eat(t_philo *philo);

/**********
***ERROR***
***********/

int						error_msg(char *message, t_simulation *sim);
void					cleanup_simulation(t_simulation *sim);

#endif