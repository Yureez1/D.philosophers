/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:11:01 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/30 13:12:57 by jbanchon         ###   ########.fr       */
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

	if (!sim || !sim->params)
		return ;
	i = 0;
	while (i < sim->params->philo_count && sim->forks)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	if (sim->philo)
		pthread_mutex_destroy(&sim->philo->print_lock);
	free(sim->forks);
	sim->forks = NULL;
	free(sim->philo);
	sim->philo = NULL;
	free(sim->params);
	sim->params = NULL;
}
