/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:12:04 by julien            #+#    #+#             */
/*   Updated: 2025/04/24 13:46:42 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_or_done(t_simulation *sim, t_philo *philo)
{
	long long	current_time;
	long long	last_meal;

	pthread_mutex_lock(&(philo->meal_lock));
	current_time = get_time();
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&(philo->meal_lock));
	if ((current_time - last_meal) >= (sim->time_to_die))
	{
		end_mutex(sim);
		print_action(sim, philo->philo_id, "died");
		return (1);
	}
	pthread_mutex_lock(&(sim->sim_end_mutex));
	if (sim->meals_to_eat > 0 && sim->total_meals_eaten >= sim->nb_philo)
	{
		pthread_mutex_unlock(&(sim->sim_end_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(sim->sim_end_mutex));
	return (0);
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

void	monitoring(t_simulation *sim, t_philo *philo)
{
	int	i;

	while (!check_sim_end(sim))
	{
		i = 0;
		while (i < sim->nb_philo)
		{
			if (check_death_or_done(sim, &philo[i]))
				return ;
			i++;
		}
		usleep(100);
	}
}
