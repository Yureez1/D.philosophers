/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:47 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/15 18:18:36 by jbanchon         ###   ########.fr       */
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

typedef enum e_philo_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}					t_philo_state;

typedef struct s_philo
{
	int				id;
	int				nb_philos;
	int				meals_eaten;
	int				meals_count;

	size_t			time_to_eat;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			start_time;
	size_t			last_meal_time;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	pthread_t		*thread;

	t_philo_state	*state;
}					t_philo;

typedef struct s_sim
{
	pthread_mutex_t	*forks;
	int				simulation_end_flag;
}					t_sim;

/*===========ERROR===========*/

int					error_msg(const char *msg, t_philo *philo);
void				destroy(t_philo *philo, t_sim *sim);

/*===========INIT===========*/

void				init_philo(t_philo *philo);
void				init_mutexes(t_philo *philo);
void				init_args(t_philo *philo, char **argv);

/*===========PHILO_MOUV===========*/

void				philo_sleep(t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_think(t_philo *philo);

/*===========PHILO_ROUTINE===========*/

void				*philosopher_routine(void *arg);
void				philo_is_dead(t_philo *philo);
void				has_sim_stopped(t_philo *philo);

/*===========THREADS===========*/

void				start_simulation(t_philo *philo);

/*===========UTILS===========*/

int					ft_atoi(const char *str);
time_t				get_current_time_ms(void);
void				print_action(t_philo *philo, const char *action);
int					is_valid_int(char *str);


#endif