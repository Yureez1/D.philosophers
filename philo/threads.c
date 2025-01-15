/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:40:46 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/15 18:13:43 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_simulation(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, phisopher_routine,
				&philos[i]) != 0)
			error_msg("Failed to create philosopher thread", philos);
		i++;
	}
	i = 0;
	while (i < philo->nb_philos)
	{
		if (pthread_join(&philos[i].thread, NULL) != 0)
			error_msg("Failed to join philosopher thread", philos);
		i++;
	}
}
