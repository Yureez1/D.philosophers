/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:46:37 by jbanchon          #+#    #+#             */
/*   Updated: 2025/05/16 11:38:06 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <memory.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_sim
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				sim_end_flg;
	int				completed_meals;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	sim_end_mutex;

}					t_sim;

typedef struct s_philo
{
	t_sim			*sim;
	pthread_t		thread;
	int				philo_id;
	int				left;
	int				right;
	long long		last_meal_time;
	int				meals_count;
}					t_philo;

/*=====[INIT]=====*/

int					init_mutexes(t_sim *sim);
int					init_params(t_sim *sim, int argc, char **argv);
int					init_philos(t_philo **philo, t_sim *sim);
int					create_threads(t_philo *philo, t_sim *sim);

/*=====[PHILO_ROUTINE]=====*/

void				monitoring(t_sim *sim, t_philo *philo);
int					print_stat(t_sim *sim, int philo_id, char *msg);
void				*philo_routine(void *argv);
int					philo_eat(t_sim *sim, t_philo *philo);

/*=====[PHILO_UTILS]=====*/

int					check_sim_end(t_sim *sim);
void				ft_usleep(int ms);
void				lock_and_unlock_mutexes(t_sim *sim);
void				destroy_mutexes(t_sim *sim);

/*=====[UTILS]=====*/

int					ft_strncmp(char *s1, char *s2, int n);
int					ft_atoi(char *str);
long long			get_time(void);
void				waiting(long long time, t_sim *sim);
void				philo_think(t_sim *sim);

#endif