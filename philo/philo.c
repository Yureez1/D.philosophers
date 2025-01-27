/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:41:22 by julien            #+#    #+#             */
/*   Updated: 2025/01/27 11:17:24 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_simulation *sim, t_philo *philo)
{
	pthread_mutex_lock(&(sim->forks[philo->left_fork]));
	print_action(sim, philo->philo_id, "has taken a fork");
	if (sim->nb_philo != 1)
	{
		pthread_mutex_lock(&(sim->forks[philo->right_fork]));
		print_action(sim, philo->philo_id, "has taken a fork");
		print_action(sim, philo->philo_id, "is eating");
		pthread_mutex_lock(&(sim->time_lock));
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&(sim->time_lock));
		philo->meals_completed++;
		philo_wait((long long)sim->time_to_eat, sim);
		pthread_mutex_unlock(&(sim->forks[philo->right_fork]));
	}
	pthread_mutex_unlock(&(sim->forks[philo->left_fork]));
	return (0);
}

void	philo_think(t_simulation *sim)
{
	struct timeval	get_time;
	struct timeval	time_stat;
	int				time_take;

	gettimeofday(&get_time, NULL);
	while (1)
	{
		gettimeofday(&time_stat, NULL);
		time_take = time_stat.tv_usec - get_time.tv_usec + (time_stat.tv_sec
				- get_time.tv_sec) * 1000000;
		if (time_take > sim->time_to_eat * 900)
			break ;
		ft_usleep(sim->time_to_eat);
	}
}

static void	philo_is_dead(t_simulation *sim, t_philo *philo)
{
	if (sim->nb_philo - 1 == philo->philo_id && philo->meals_completed == 0)
		usleep(1);
	philo_eat(sim, philo);
	if (sim->nb_philo == 1)
		philo_wait((long long)sim->time_to_sleep, sim);
}

void	*philo_routine(void *arg)
{
	t_simulation	*sim;
	t_philo			*philo;

	philo = (t_philo *)arg;
	sim = philo->simulation;
	if (philo->philo_id % 2 == 0)
		philo_think(sim);
	while (!check_sim_end(sim))
	{
		philo_is_dead(sim, philo);
		if (sim->meals_to_eat == philo->meals_completed)
		{
			sim->total_meals_eaten++;
			break ;
		}
		print_action(sim, philo->philo_id, "is sleeping");
		philo_wait((long long)sim->time_to_sleep, sim);
		print_action(sim, philo->philo_id, "is thinking");
	}
	return (0);
}
