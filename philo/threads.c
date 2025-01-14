/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:40:46 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/14 18:30:13 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_simulation(t_simulation *sim)
{
	int			i;
	pthread_t	monitor_thread;

	sim->start_time = get_current_time_ms();
	i = 0;
	while (i < sim->philo_count)
	{
		if (pthread_create(&(sim->philo[i].thread), NULL, philo_routine,
				(void *)&(sim->philo[i])) != 0)
		{
			error_msg("Failed to create thread for philo", sim);
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine,
			(void *)sim) != 0)
	{
		error_msg("Failed to create monitor thread", sim);
		return (1);
	}
	i = 0;
	while (i < sim->philo_count)
	{
		if (pthread_join(sim->philo[i].thread, NULL) != 0)
		{
			error_msg("Failed to join thread for philo", sim);
			return (1);
		}
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		error_msg("Failed to join monitor thread", sim);
		return (1);
	}
	return (0);
}

/*int init_threads(t_simulation *sim)
{
    int i;

    i = 0;
    while 
    
}
*/