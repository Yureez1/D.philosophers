/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:13:49 by julien            #+#    #+#             */
/*   Updated: 2025/04/23 16:12:15 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_simulation
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	int				sim_end;
	int				total_meals_eaten;
	long long		sim_start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	sim_end_mutex;
}					t_simulation;

typedef struct s_philo
{
	t_simulation	*simulation;
	pthread_t		philo_thread;
	int				philo_id;
	int				left_fork;
	int				right_fork;
	long long		last_meal_time;
	int				meals_completed;
}					t_philo;

/*======INITIALIZATION======*/

int					init_philo(t_philo **philo, t_simulation *sim);
int					init_args(t_simulation *sim, int argc, char **argv);
int					init_mutex(t_simulation *sim);
void				end_mutex(t_simulation *sim);

/*======THREADS=======*/

int					create_philo_threads(t_philo *philo, t_simulation *sim);
void				*philo_routine(void *arg);
void				monitoring(t_simulation *sim, t_philo *philo);
int					check_sim_end(t_simulation *sim);

/*======ACTIONS======*/

int					philo_eat(t_simulation *sim, t_philo *philo);
void				philo_think(t_simulation *sim);
int					print_action(t_simulation *sim, int philo_id, char *action);

/*======UTILS======*/

void				philo_wait(long long usec, t_simulation *sim);
void				handle_eating(t_philo *philo, t_simulation *sim);
void				ft_usleep(long long ms);
long long			get_time(void);
int					ft_atoi(char *str);

/*======ERRORS======*/

void				error_msg(char *msg, t_simulation *sim);
void				destroy(t_simulation *sim);

#endif