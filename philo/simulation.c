/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:20 by julien            #+#    #+#             */
/*   Updated: 2025/01/21 16:15:34 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_simulation(t_philo *philo)
{
	int		i;
	size_t	start_time;

	i = 0;
	start_time = get_current_time_ms();
	while (i < philo->nb_philos)
	{
		philo[i].start_time = start_time;
		philo[i].last_meal_time = start_time;
		philo[i].sim->simulation_end_flag = 0;
		i++;
	}
}

static void	cleanup_threads(t_philo *philo, int last_created)
{
	int	i;

	i = 0;
	while (i < last_created)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

static int	create_threads(t_philo *philo, pthread_t *monitor)
{
	int	i;

	if (pthread_create(monitor, NULL, monitor_routine, philo) != 0)
	{
		error_msg("Failed to create monitor thread", philo);
		return (0);
	}
	i = 0;
	while (i < philo->nb_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, philosopher_routine,
				&philo[i]) != 0)
		{
			error_msg("Failed to create philosopher thread", philo);
			pthread_join(*monitor, NULL);
			cleanup_threads(philo, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	join_threads(t_philo *philo, pthread_t monitor)
{
	int	i;

	if (pthread_join(monitor, NULL) != 0)
		error_msg("Failed to join monitor thread", philo);
	i = 0;
	while (i < philo->nb_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			error_msg("Failed to join philosopher thread", philo);
		i++;
	}
}

void	start_simulation(t_philo *philo)
{
	pthread_t	monitor;

	init_simulation(philo);
	if (!create_threads(philo, &monitor))
		return;
	join_threads(philo, monitor);
}
