/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:15:20 by julien            #+#    #+#             */
/*   Updated: 2025/04/30 00:15:20 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_sim_end(t_simulation *sim)
{
	pthread_mutex_lock(&(sim->sim_end_mutex));
	if (sim->sim_end == 1)
	{
		pthread_mutex_unlock(&(sim->sim_end_mutex));
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&(sim->sim_end_mutex));
		return (0);
	}
}

void	end_mutex(t_simulation *sim)
{
	pthread_mutex_lock(&(sim->sim_end_mutex));
	sim->sim_end = 1;
	pthread_mutex_unlock(&(sim->sim_end_mutex));
}

void	philo_wait(long long usec, t_simulation *sim)
{
	long long	start_time;
	long long	current_time;

	start_time = get_time();
	while (!check_sim_end(sim))
	{
		current_time = get_time();
		if ((current_time - start_time) >= usec)
			break ;
		usleep(100);
	}
}
