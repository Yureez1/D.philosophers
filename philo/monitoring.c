/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:12:04 by julien            #+#    #+#             */
/*   Updated: 2025/01/27 11:17:59 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring(t_simulation *sim, t_philo *philo)
{
	int			i;
	long long	current_time;

	while (!check_sim_end(sim))
	{
		if ((sim->meals_to_eat != 0)
			&& (sim->nb_philo == sim->total_meals_eaten))
			end_mutex(sim);
		i = 0;
		while (i < sim->nb_philo)
		{
			current_time = get_time();
			if ((current_time - philo[i].last_meal_time) >= (sim->time_to_die))
			{

				print_action(sim, i, "died");
				end_mutex(sim);
				pthread_mutex_lock(&(sim->print_lock));
			}
			i++;
		}
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
