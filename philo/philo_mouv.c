/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mouv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:47:57 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/16 17:30:54 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_sleep(t_philo *philo)
{
	philo->state = SLEEPING;
	print_action(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
}

void	philo_eat(t_philo *philo)
{
	philo->state = EATING;
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
	pthread_mutex_lock(&philo->meal_lock);
	print_action(philo, "is eating");
	pthread_mutex_unlock(&philo->meal_lock);
	philo->last_meal_time = get_current_time_ms();
	philo->meals_eaten++;
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	philo_think(t_philo *philo)
{
	philo->state = THINKING;
	print_action(philo, "is thinking");
	usleep(1000);
}
