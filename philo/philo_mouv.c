/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mouv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:47:57 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/15 18:17:06 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_sleep(t_philo *philo)
{
	philo->state = SLEEPING;
	print_action("is sleeping", philo->id);
}

void	philo_eat(t_philo *philo)
{
	philo->state = EATING;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->id]);
		pthread_mutex_lock(&philo->forks[philo->id + 1] % philo->nb_philos);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->id + 1] % philo->nb_philos);
		pthread_mutex_lock(&philo->forks[philo->id]);
	}
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = get_current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_lock(philo->print_lock);
	print_action("is eating", philo->id);
	pthread_mutex_unlock(philo->print_lock);
	usleep(philo->time_to_eat * 1000)
	pthread_mutex_unlock(&philo->forks[philo->id];
	pthread_mutex_unlock(&philo->forks[(philo->id + 1) % philo->nb_philos]);
}

void	philo_think(t_philo *philo)
{
	philo->state = THINKING;
	print_action("is thinking", philo->id);
}
