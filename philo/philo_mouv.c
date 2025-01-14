/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mouv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:47:57 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/14 18:20:01 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	take_forks(t_philo *philo)
// {
// 	if (philo->philo_id % 2 == 0)
// 	{
// 		pthread_mutex_lock(philo->left_fork);
// 		print_action(philo, "has taken a fork");
// 		pthread_mutex_lock(philo->right_fork);
// 		print_action(philo, "has taken a fork");
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(philo->right_fork);
// 		print_action(philo, "has taken a fork");
// 		pthread_mutex_lock(philo->left_fork);
// 		print_action(philo, "has taken a fork");
// 	}
// }

void	eat(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->meal_lock);
	philo->eating = 1;
	philo->last_meal_time = get_current_time_ms();
	philo->meals_eaten++;
	print_action(philo, "is eating");
	pthread_mutex_unlock(&philo->meal_lock);
	precise_usleep(philo->sim->time_to_eat);
	pthread_mutex_lock(&philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	go_to_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	precise_usleep(philo->sim->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

void	precise_usleep(size_t duration_ms)
{
	size_t start_time;
	
	start_time = get_current_time_ms();
	while((get_current_time_ms() - start_time) < duration_ms)
		usleep(500);
}
