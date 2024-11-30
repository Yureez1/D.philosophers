/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mouv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:47:57 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/30 13:38:37 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "Has taken the left fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "Has taken the right fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken the left fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "Has taken the right fork");
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (philo->sim->params->meals_count != -1
		&& philo->meals_eaten >= philo->sim->params->meals_count)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return ;
	}
	philo->last_meal_time = get_current_time_ms();
	philo->meals_eaten++;
	print_action(philo, "is eating");
	usleep(philo->sim->params->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->meal_lock);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	print_action(philo, "Has released the left fork");
	pthread_mutex_unlock(philo->right_fork);
	print_action(philo, "Has released the right fork");
}

void	go_to_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->sim->params->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	print_action(philo, "is thinking");
}
