/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:31:17 by jbanchon          #+#    #+#             */
/*   Updated: 2025/05/13 22:43:02 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_sim_end(t_sim *sim)
{
	pthread_mutex_lock(&(sim->sim_end_mutex));
	if (sim->sim_end_flg == 1)
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

void	lock_and_unlock_mutexes(t_sim *sim)
{
	pthread_mutex_lock(&(sim->sim_end_mutex));
	sim->sim_end_flg = 1;
	pthread_mutex_unlock(&(sim->sim_end_mutex));
}

void	ft_usleep(int ms)
{
	long int	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(ms / 10);
}
