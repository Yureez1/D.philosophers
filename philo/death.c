/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:20 by julien            #+#    #+#             */
/*   Updated: 2025/01/21 22:42:40 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *philo, int i)
{
	size_t	current_time;

	current_time = get_current_time_ms();
	pthread_mutex_lock(&philo[i].dead_lock);
	if (philo->meals_count == -1 || philo[i].meals_eaten < philo->meals_count)
	{
		if (current_time - philo[i].last_meal_time > philo[i].time_to_die)
		{
			print_action(&philo[i], "has died");
			pthread_mutex_lock(&philo->sim->dead_lock);
			philo->sim->simulation_end_flag = 1;
			pthread_mutex_unlock(&philo->sim->dead_lock);
			pthread_mutex_unlock(&philo[i].dead_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo[i].dead_lock);
	return (0);
}

void	check_meals(t_philo *philo, int i, int *all_finished)
{
	pthread_mutex_lock(&philo[i].meal_lock);
	if (philo->meals_count != -1)
	{
		if (philo[i].meals_eaten < philo->meals_count)
		{
			pthread_mutex_lock(&philo->sim->dead_lock);
			*all_finished = 0;
			pthread_mutex_unlock(&philo->sim->dead_lock);
		}
	}
	pthread_mutex_unlock(&philo[i].meal_lock);
}

int	check_simulation_complete(t_philo *philo, int all_finished)
{
	if (philo->meals_count != -1 && all_finished)
	{
		pthread_mutex_lock(&philo->sim->dead_lock);
		if (!philo->sim->simulation_end_flag)
		{
			philo->sim->simulation_end_flag = 1;
		}
		pthread_mutex_unlock(&philo->sim->dead_lock);
		return (1);
	}
	return (0);
}
