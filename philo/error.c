/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:20:30 by julien            #+#    #+#             */
/*   Updated: 2025/01/26 16:33:39 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg(char *msg, t_simulation *sim)
{
	printf("%s", msg);
	if (sim)
		destroy(sim);
	exit(1);
}

void	destroy(t_simulation *sim)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->time_lock);
	pthread_mutex_destroy(&sim->sim_end_mutex);
	while (i < sim->nb_philo)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	free(sim->forks);
}
