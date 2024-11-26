/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:10:28 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/26 15:04:09 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->params->sim->print_lock);
	printf("Philo %d is eating\n", philo->philo_id);
	pthread_mutex_unlock(&philo->params->sim->print_lock);
	philo->meals_eaten++;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep_and_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->sim->print_lock);
	printf("Philo %d is sleeping\n", philo->philo_id);
	pthread_mutex_unlock(&philo->params->sim->print_lock);
	usleep(philo->params->time_to_sleep * 1000);
	pthread_mutex_lock(&philo->params->sim->print_lock);
	printf("Philo %d is thinking\n", philo->philo_id);
	pthread_mutex_unlock(&philo->params->sim->print_lock);
}

/*void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->params->sim->print_lock);
	printf("Philo %d started\n", philo->philo_id);
	pthread_mutex_unlock(&philo->params->sim->print_lock);
	while (1)
	{
		philo_eat(philo);
		philo_sleep_and_think(philo);
		if (philo->meals_eaten >= philo->params->meals_count)
			break ;
	}
	return (NULL);
}*/
void	*philo_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	
	printf("Philo %d started\n", philo->philo_id);
	if (!philo->left_fork || !philo->right_fork)
	{
		printf("Error: Forks not initialized for Philo %d\n", philo->philo_id);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->params->sim->print_lock);
		printf("Philo %d is thinking\n", philo->philo_id);
		pthread_mutex_unlock(&philo->params->sim->print_lock);
		
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		
		pthread_mutex_lock(&philo->params->sim->print_lock);
		printf("Philo %d is eating\n", philo->philo_id);
		pthread_mutex_unlock(&philo->params->sim->print_lock);
		philo->meals_eaten++;
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		philo_sleep_and_think(philo);
		usleep(philo->params->time_to_sleep * 1000);
		if (philo->meals_eaten >= philo->params->meals_count)
			break ;
	}
	return (NULL);
}
