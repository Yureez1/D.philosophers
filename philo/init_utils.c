/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:20 by julien            #+#    #+#             */
/*   Updated: 2025/01/22 16:34:03 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_args(t_philo *philo, char **argv)
{
	philo->nb_philos = ft_atoi(argv[1]);
	if (philo->nb_philos <= 0 || philo->nb_philos > 200)
	{
		error_msg("Invalid number of philosophers (1-200)", philo);
		return (1);
	}
	philo->time_to_die = ft_atoi(argv[2]);
	if (philo->time_to_die <= 0)
	{
		error_msg("Time to die must be positive", philo);
		return (1);
	}
	philo->time_to_eat = ft_atoi(argv[3]);
	if (philo->time_to_eat <= 0)
	{
		error_msg("Time to eat must be positive", philo);
		return (1);
	}
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (philo->time_to_sleep <= 0)
	{
		error_msg("Time to sleep must be positive", philo);
		return (1);
	}
	if (argv[5] != NULL)
	{
		philo->meals_count = ft_atoi(argv[5]);
		if (philo->meals_count != -1 && philo->meals_count <= 0)
		{
			error_msg("Number of meals must be positive or -1", philo);
			return (1);
		}
	}
	else
		philo->meals_count = -1;
	return (0);
}

int	init_mutexes(t_sim *sim)
{
	if (pthread_mutex_init(&(sim->dead_lock), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(sim->meal_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&(sim->dead_lock));
		return (1);
	}
	if (pthread_mutex_init(&(sim->print_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&(sim->dead_lock));
		pthread_mutex_destroy(&(sim->meal_lock));
		return (1);
	}
	return (0);
}

int	init_fork(t_sim *sim)
{
	int	i;

	i = 0;
	sim->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* sim->philo->nb_philos);
	if (!sim->forks)
	{
		error_msg("Failed to allocate memory", sim->philo);
		pthread_mutex_destroy(&(sim->dead_lock));
		pthread_mutex_destroy(&(sim->meal_lock));
		pthread_mutex_destroy(&(sim->print_lock));
		return (1);
	}
	while (i < sim->philo->nb_philos)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&sim->forks[i]);
			free(sim->forks);
			pthread_mutex_destroy(&(sim->dead_lock));
			pthread_mutex_destroy(&(sim->meal_lock));
			pthread_mutex_destroy(&(sim->print_lock));
			return (1);
		}
		i++;
	}
	return (0);
}
