/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:50 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/14 18:30:01 by jbanchon         ###   ########.fr       */
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
	/*if (!(sim->  = malloc(sizeof(t_ ))))
		return (error_msg("Memory allocation for t_  failed\n", sim));*/
	if (!(sim->philo = malloc(sizeof(t_philo) * sim->philo_count)))
		return (error_msg("Memory allocation for philosophers failed\n", sim));
	if (!(sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philo_count)))
		return (error_msg("Memory allocation for forks failed\n", sim));
	sim->stop_lock = malloc(sizeof(pthread_mutex_t));
	if (!sim->stop_lock || pthread_mutex_init(sim->stop_lock, NULL) != 0)
	{
		free(sim->stop_lock);
		return (-1);
	}
	return (0);
}

int	init_philosophers(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->simulation_stopped = 0;
	sim->start_time = get_current_time_ms();
	while (i < sim->philo_count)
	{
		sim->philo[i].philo_id = i + 1;
		sim->philo[i].meals_eaten = 0;
		sim->philo[i].last_meal_time = sim->start_time;
		sim->philo[i].left_fork = &sim->forks[(i + sim->philo_count - 1)
			% sim->philo_count];
		sim->philo[i].right_fork = &sim->forks[i];
		sim->philo[i].sim = sim;
		// sim->philo[i].dead = malloc(sizeof(int));
		// *(sim->philo[i].dead) = 0;
		sim->philo[i].dead = &sim->dead;
		pthread_mutex_init(&sim->philo->print_lock, NULL);
		pthread_mutex_init(&sim->philo->dead_lock, NULL);
		pthread_mutex_init(&sim->philo->meal_lock, NULL);
		i++;
	}
	return (0);
}

int	init_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->philo_count)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
	return (0);
}
