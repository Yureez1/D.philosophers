/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:47 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/14 18:29:23 by jbanchon         ###   ########.fr       */
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

# define PHILO_MAX 200
typedef struct s_philo	t_philo;

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}						t_state;

typedef struct s_simulation
{
	int					simulation_stopped;
	pthread_mutex_t		*stop_lock;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	int dead;
	size_t				start_time;
	int					philo_count;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					meals_count;
}						t_simulation;

// Philo struct
typedef struct s_philo
{
	int					philo_id;
	int					meals_eaten;
	int					eating;
	size_t				last_meal_time;
	int					*dead;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_t			thread;
	t_simulation		*sim;
}						t_philo;

/************
***PARSING***
*************/

int						parse_args(int argc, char **argv, t_simulation *sim);
void					check_argc(int argc, t_simulation *sim);
void					init_(t_simulation *sim, char **argv);
void					validate_args(t_simulation *sim, char **argv);
int						is_initialized(t_simulation *sim);
void					precise_usleep(size_t duration);

/**********
***UTILS***
***********/

int						is_valid_int(char *str);
time_t					get_current_time_ms(void);
int						is_digit(const char c);
int						ft_atoi(const char *str);
void					print_action(t_philo *philo, const char *action);

/*********
***INIT***
**********/

int						init_philo(t_simulation *sim);
int						init_philosophers(t_simulation *sim);
int						allocate_simulation_ressources(t_simulation *sim);
int						init_forks(t_simulation *sim);
int						check_simulation_stopped(t_simulation *sim);

/**********
**ROUTINE**
***********/

void					take_forks(t_philo *philo);
void					eat(t_philo *philo);
void					release_forks(t_philo *philo);
void					go_to_sleep(t_philo *philo);
void					think(t_philo *philo);
void					*philo_routine(void *arg);
int						is_dead(t_simulation *sim);
void					*monitor_routine(void *arg);
int						start_simulation(t_simulation *sim);
void					one_philo(t_philo *philo);

/********
**LOOP***
*********/

int						all_philo_ate(t_simulation *sim);
/**********
***ERROR***
***********/

int						error_msg(char *message, t_simulation *sim);
void					cleanup_simulation(t_simulation *sim);

#endif