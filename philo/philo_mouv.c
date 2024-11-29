/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mouv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:47:57 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/29 15:31:15 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "Has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "Has taken a fork");
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_current_time_ms();
	philo->meals_eaten++;
	print_action(philo, "is eating");
	usleep(philo->sim->params->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->meal_lock);
}

void release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	print_action(philo, "Has released a fork");
	pthread_mutex_unlock(philo->right_fork);
	print_action(philo, "Has released a fork");
}

void go_to_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->sim->params->time_to_sleep * 1000);
}

void think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

