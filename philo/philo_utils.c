/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 23:21:20 by julien            #+#    #+#             */
/*   Updated: 2025/04/30 00:09:03 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_left_fork(t_simulation *sim, t_philo *philo)
{
	if (check_sim_end(sim))
		return (1);
	pthread_mutex_lock(&(sim->forks[philo->left_fork]));
	if (check_sim_end(sim))
	{
		pthread_mutex_unlock(&(sim->forks[philo->left_fork]));
		return (1);
	}
	print_action(sim, philo->philo_id, "has taken a fork");
	if (sim->nb_philo == 1)
	{
		philo_wait(sim->time_to_die, sim);
		pthread_mutex_unlock(&(sim->forks[philo->left_fork]));
		return (1);
	}
	return (0);
}

int	take_right_fork(t_simulation *sim, t_philo *philo)
{
	pthread_mutex_lock(&(sim->forks[philo->right_fork]));
	if (check_sim_end(sim))
	{
		pthread_mutex_unlock(&(sim->forks[philo->right_fork]));
		pthread_mutex_unlock(&(sim->forks[philo->left_fork]));
		return (1);
	}
	print_action(sim, philo->philo_id, "has taken a fork");
	return (0);
}

void	eat_and_release_forks(t_simulation *sim, t_philo *philo)
{
	print_action(sim, philo->philo_id, "is eating");
	pthread_mutex_lock(&(philo->meal_lock));
	philo->last_meal_time = get_time();
	philo->meals_completed++;
	pthread_mutex_unlock(&(philo->meal_lock));
	philo_wait(sim->time_to_eat, sim);
	pthread_mutex_unlock(&(sim->forks[philo->right_fork]));
	pthread_mutex_unlock(&(sim->forks[philo->left_fork]));
}

int	philo_eat(t_simulation *sim, t_philo *philo)
{
	if (take_left_fork(sim, philo))
		return (1);
	if (take_right_fork(sim, philo))
		return (1);
	eat_and_release_forks(sim, philo);
	return (0);
}
