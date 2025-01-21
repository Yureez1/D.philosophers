/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:20 by julien            #+#    #+#             */
/*   Updated: 2025/01/21 22:42:56 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_msg(const char *msg, t_philo *philo)
{
	printf("Error: %s\n", msg);
	if (philo)
		destroy(philo);
	return (1);
}

void	destroy_forks(t_sim *sim)
{
	int	i;

	if (sim && sim->forks)
	{
		i = 0;
		while (i < sim->philo->nb_philos)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
		free(sim->forks);
		sim->forks = NULL;
	}
}

void	destroy_mutexes(t_sim *sim)
{
	if (sim)
	{
		pthread_mutex_destroy(&sim->print_lock);
		pthread_mutex_destroy(&sim->meal_lock);
		pthread_mutex_destroy(&sim->dead_lock);
	}
}

void	destroy(t_philo *philo)
{
	t_sim	*sim;

	if (!philo)
		return;
	sim = philo->sim;
	if (sim)
	{
		destroy_forks(sim);
		destroy_mutexes(sim);
		free(sim);
	}
	free(philo);
}
