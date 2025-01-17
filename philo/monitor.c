/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:20 by julien            #+#    #+#             */
/*   Updated: 2025/01/17 14:21:20 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_monitor_end(t_philo *philo)
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

static int	monitor_philosophers(t_philo *philo, int *all_finished)
{
	int	i;

	i = 0;
	while (i < philo->nb_philos)
	{
		if (check_death(philo, i))
			return (1);
		check_meals(philo, i, all_finished);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	int		all_finished;

	philo = (t_philo *)arg;
	precise_sleep(5);
	while (1)
	{
		if (check_monitor_end(philo))
			return (NULL);
		all_finished = 1;
		if (monitor_philosophers(philo, &all_finished))
			return (NULL);
		if (check_simulation_complete(philo, all_finished))
			return (NULL);
		precise_sleep(1);
	}
	return (NULL);
}
