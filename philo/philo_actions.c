/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:20 by julien            #+#    #+#             */
/*   Updated: 2025/01/17 14:21:20 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "has taken a fork");
	}
}

static void	start_eating(t_philo *philo)
{
	size_t	start_time;

	start_time = get_current_time_ms();
	pthread_mutex_lock(&philo->dead_lock);
	philo->last_meal_time = start_time;
	pthread_mutex_unlock(&philo->dead_lock);
	pthread_mutex_lock(&philo->meal_lock);
	philo->state = EATING;
	print_action(philo, "is eating");
	pthread_mutex_unlock(&philo->meal_lock);
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	start_eating(philo);
	precise_sleep(philo->time_to_eat);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	philo_sleep(t_philo *philo)
{
	philo->state = SLEEPING;
	print_action(philo, "is sleeping");
	precise_sleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	philo->state = THINKING;
	print_action(philo, "is thinking");
}
