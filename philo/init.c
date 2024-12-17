/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:50 by jbanchon          #+#    #+#             */
/*   Updated: 2024/12/17 15:42:18 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_simulation *sim)
{
	if (allocate_simulation_ressources(sim) != 0)
		return (1);
	if (init_forks(sim) != 0)
		return (1);
	if (init_philosophers(sim) != 0)
		return (1);
	return (0);
}

int	allocate_simulation_ressources(t_simulation *sim)
{
	if (!(sim->philo = malloc(sizeof(t_philo) * sim->params->philo_count)))
		return (error_msg("Memory allocation for philosophers failed\n", sim));
	if (!(sim->forks = malloc(sizeof(pthread_mutex_t)
				* sim->params->philo_count)))
		return (error_msg("Memory allocation for forks failed\n", sim));
	if (!(sim->stop_lock = malloc(sizeof(pthread_mutex_t))))
		return (error_msg("Memory allocation for stop lock failed\n", sim));
	return (0);
}

int	init_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(sim->stop_lock, NULL) != 0)
		return (error_msg("Failed to initialize stop lock", sim));
	while (i < sim->params->philo_count)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			while(--i >= 0)
				pthread_mutex_destroy(&sim->forks[i]);
			pthread_mutex_destroy(sim->stop_lock);
			return (error_msg("Initialization failed for forks", sim));
		}
		i++;
	}
	return (0);
}

int	init_philosophers(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->simulation_stopped = 0;
	while (i < sim->params->philo_count)
	{
		sim->philo[i].philo_id = i;
		sim->philo[i].meals_eaten = 0;
		sim->philo[i].last_meal_time = sim->start_time;
		if (init_mutex(&sim->philo[i].meal_lock,
				"Initialization for meal_lock failed\n", sim) != 0)
			return (1);
		sim->philo[i].left_fork = &sim->forks[(i + sim->params->philo_count - 1)
			% sim->params->philo_count];
		sim->philo[i].right_fork = &sim->forks[i];
		sim->philo[i].sim = sim;
		i++;
	}
	return (0);
}

int	init_mutex(pthread_mutex_t *mutex, char *error_message, t_simulation *sim)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		return (error_msg(error_message, sim));
	return (0);
}
