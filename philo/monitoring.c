/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:12:04 by julien            #+#    #+#             */
/*   Updated: 2025/04/23 16:14:24 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring(t_simulation *sim, t_philo *philo)
{
	int			i;
	long long	current_time;
	long long	last_meal;

	while (!check_sim_end(sim))
	{
		i = 0;
		while (i < sim->nb_philo && !check_sim_end(sim))
		{
			pthread_mutex_lock(&(sim->time_lock));
			current_time = get_time();
			last_meal = philo[i].last_meal_time;
			pthread_mutex_unlock(&(sim->time_lock));
			if ((current_time - last_meal) >= (sim->time_to_die))
			{
				end_mutex(sim);
				print_action(sim, philo[i].philo_id, "died");
				break ;
			}
			i++;
		}
		usleep(1000);
	}
}

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

void	ft_usleep(long long ms)
{
	long long	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(ms / 10);
}
