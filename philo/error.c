/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:11:01 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/16 14:26:05 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_msg(const char *msg, t_philo *philo)
{
	printf("Error: %s\n", msg);
	destroy(philo);
	exit(0);
}

void	destroy(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philos)
	{
		if (&(philo->nb_philos) != NULL)
			pthread_mutex_destroy(&philo->sim->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->print_lock);
	pthread_mutex_destroy(&philo->meal_lock);
	pthread_mutex_destroy(&philo->dead_lock);
	free(philo->sim->forks);
	free(philo);
	return ;
}
