/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:20:30 by julien            #+#    #+#             */
/*   Updated: 2025/04/23 16:13:54 by julien           ###   ########.fr       */
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

	if (!sim)
		return ;
	end_mutex(sim);
	i = 0;
	if (sim->forks)
	{
		while (i < sim->nb_philo)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
		free(sim->forks);
		sim->forks = NULL;
	}
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->time_lock);
	pthread_mutex_destroy(&sim->sim_end_mutex);
}
