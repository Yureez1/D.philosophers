/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:20 by julien            #+#    #+#             */
/*   Updated: 2025/01/22 15:39:17 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*static int	check_meals_complete(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (philo->meals_count != -1 && philo->meals_eaten >= philo->meals_count)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}*/

static int	check_simulation_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->dead_lock);
	if (philo->sim->simulation_end_flag)
	{
		pthread_mutex_unlock(&philo->sim->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->dead_lock);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_sleep(philo->time_to_eat * 0.2);
	while (1)
	{
		if (check_simulation_end(philo))
			return (NULL);
		philo_eat(philo);
		if (check_simulation_end(philo))
			return (NULL);
		philo_sleep(philo);
		if (check_simulation_end(philo))
			return (NULL);
		philo_think(philo);
		if (check_simulation_end(philo))
			return (NULL);
	}
	return (NULL);
}
