/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:12:04 by julien            #+#    #+#             */
/*   Updated: 2025/04/26 16:55:35 by jbanchon         ###   ########.fr       */
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
	t_philo		*end;
	t_philo		*cur;
	long long	last;
	int			done;

	end = philo + sim->nb_philo;
	while (!check_sim_end(sim))
	{
		cur = philo;
		while (cur < end)
		{
			pthread_mutex_lock(&(cur->meal_lock));
			last = cur->last_meal_time;
			done = cur->has_finished;
			pthread_mutex_unlock(&(cur->meal_lock));
			if (!done && get_time() - last >= sim->time_to_die)
			{
				print_action(sim, cur->philo_id, "died");
				pthread_mutex_lock(&(sim->sim_end_mutex));
				sim->sim_end = 1;
				pthread_mutex_unlock(&(sim->sim_end_mutex));
				return ;
			}
			cur++;
		}
		usleep(100);
	}
}
