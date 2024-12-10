/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:47 by jbanchon          #+#    #+#             */
/*   Updated: 2024/12/10 16:52:22 by jbanchon         ###   ########.fr       */
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

typedef struct s_philo	t_philo;

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}						t_state;

// Simulation params
typedef struct s_params
{
	int					philo_count;
	t_philo				*philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_count;
	struct s_simulation	*sim;
}						t_params;

typedef struct s_simulation
{
	int					simulation_stopped;
	t_params			*params;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	long				start_time;
	pthread_mutex_t		*stop_lock;
}						t_simulation;

// Philo struct
typedef struct s_philo
{
	int					philo_id;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	long				last_meal_time;
	int					meals_eaten;
	pthread_mutex_t		print_lock;
	pthread_t			thread;
	struct s_simulation	*sim;
	t_params			*params;
	t_state				state;
}						t_philo;

/************
***PARSING***
*************/

int						parse_args(int argc, char **argv, t_simulation *sim);
void					check_argc(int argc, t_simulation *sim);
void					init_params(t_simulation *sim, char **argv);
void					validate_args(t_simulation *sim, char **argv);
void					handle_optional_arg(int argc, t_simulation *sim,
							char **argv);

int is_initialized(t_simulation *sim);
/**********
***UTILS***
***********/

int						is_valid_int(char *str);
int						get_current_time_ms(void);
int						is_digit(const char c);
int						ft_atoi(const char *str);
void					print_action(t_philo *philo, const char *action);

/*********
***INIT***
**********/

int						init_philo(t_simulation *sim);
int						init_forks(t_simulation *sim);
int						init_philosophers(t_simulation *sim);
int						init_mutex(pthread_mutex_t *mutex, char *error_message,
							t_simulation *sim);
int						allocate_simulation_ressources(t_simulation *sim);

/**********
**ROUTINE**
***********/

void					take_forks(t_philo *philo);
void					eat(t_philo *philo);
void					release_forks(t_philo *philo);
void					go_to_sleep(t_philo *philo);
void					think(t_philo *philo);
void					*philo_routine(void *arg);
int						is_dead(t_philo *philo);
void					*monitor_routine(void *arg);
int						start_simulation(t_simulation *sim);

/********
**LOOP***
*********/

int all_philo_ate(t_simulation *sim);
/**********
***ERROR***
***********/

int						error_msg(char *message, t_simulation *sim);
void					cleanup_simulation(t_simulation *sim);

#endif