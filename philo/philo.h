/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:46:37 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/30 11:52:00 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

#endif