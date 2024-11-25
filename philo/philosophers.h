/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:47 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/25 19:48:25 by jbanchon         ###   ########.fr       */
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

# define ERROR_NUM_PHILO "There must be no more than 200 philosophers."
# define ERROR_ARGS "<Number of philo> <Time of philo must fast to die> <Time of philo takes to eat> <Time of philo takes to sleep> Optionnal : <Times the philos must eat in order to terminate the program>."

// Simulation params
typedef struct s_params
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_count;
}					t_params;

// Philo struct
typedef struct s_philo
{
	int				philo_id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_params		*params;
}					t_philo;

typedef struct s_simulation
{
	t_params		*params;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	long			start_time;
}					t_simulation;

/************
***PARSING***
*************/

t_params			parse_input(t_simulation *sim, int argc, char **argv);
int					parse_args(const char *argv);
int					is_integer(const char *str);

/**********
***UTILS***
***********/

int					ft_atoi(const char *str);
int					ft_isdigit(const char *str);
long				get_current_time(void);

/**********
***PHILO***
***********/

void				start_sim(t_simulation *sim);
void				*philo_routine(void *arg);
void				init_simulation(t_simulation *sim);

/**********
***ERROR***
***********/

int					error_msg(char *message, t_simulation *sim);
void				cleanup_simulation(t_simulation *sim);

#endif