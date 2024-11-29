/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:11:01 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/29 15:49:13 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_msg(char *message, t_simulation *sim)
{
	printf("%s\n", message);
	if (sim)
		cleanup_simulation(sim);
	return (1);
}

void	cleanup_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->params->philo_count)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->philo->print_lock);
	free(sim->forks);
	free(sim->philo);
	free(sim->params);
}
