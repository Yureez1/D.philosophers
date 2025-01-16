/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:40:46 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/16 11:08:33 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_simulation(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, philosopher_routine,
				&philo[i]) != 0)
			error_msg("Failed to create philosopher thread", philo);
		i++;
	}
	i = 0;
	while (i < philo->nb_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			error_msg("Failed to join philosopher thread", philo);
		i++;
	}
}
