/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:47 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/21 16:00:36 by jbanchon         ###   ########.fr       */
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

typedef struct s_sim	t_sim;

typedef enum e_philo_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}						t_philo_state;

typedef struct s_philo
{
	int					id;
	int					nb_philos;
	int					meals_eaten;
	int					meals_count;

	size_t				time_to_eat;
	size_t				time_to_die;
	size_t				time_to_sleep;
	size_t				start_time;
	size_t				last_meal_time;

	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		dead_lock;
	pthread_t			thread;

	t_philo_state		state;
	t_sim				*sim;
}						t_philo;

typedef struct s_sim
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		dead_lock;
	int					simulation_end_flag;
	t_philo				*philo;
}						t_sim;

/*===========ERROR===========*/

int						error_msg(const char *msg, t_philo *philo);
void					destroy(t_philo *philo);
void					destroy_mutexes(t_sim *sim);
void					destroy_forks(t_sim *sim);

/*===========INIT===========*/

int						init_philo(t_philo *philo, t_sim *sim,
							pthread_mutex_t *forks);
int						init_mutexes(t_sim *sim);
int						init_args(t_philo *philo, char **argv);
int						init_fork(t_sim *sim);

/*===========MONITOR===========*/

int						check_death(t_philo *philo, int i);
void					check_meals(t_philo *philo, int i, int *all_finished);
int						check_simulation_complete(t_philo *philo,
							int all_finished);
void					*monitor_routine(void *arg);

/*===========SIMULATION===========*/

void					start_simulation(t_philo *philo);

/*===========PHILO_ACTIONS===========*/

void					philo_eat(t_philo *philo);
void					philo_sleep(t_philo *philo);
void					philo_think(t_philo *philo);

/*===========PHILO_ROUTINE===========*/

void					*philosopher_routine(void *arg);
void					philo_is_dead(t_philo *philo);
void					has_sim_stopped(t_philo *philo);

/*===========UTILS===========*/

void					print_action(t_philo *philo, const char *action);
void					precise_sleep(size_t duration);
size_t					get_current_time_ms(void);
int						ft_atoi(const char *str);
int						is_valid_int(char *str);

#endif