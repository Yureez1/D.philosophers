/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:10:28 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/15 18:17:32 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		philo_is_dead(philo);
		if (philo->state == DEAD)
			break ;
		philo_eat(philo);
		philo_think(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	philo_is_dead(t_philo *philo)
{
	if (get_current_time_ms() - philo->last_meal_time >= philo->time_to_die)
	{
		philo->state = DEAD;
		print_action("has died", philo->id);
	}
}

void	has_sim_stopped(t_philo *philo)
{
	int	i;
	int	is_dead;

	i = 0;
	is_dead = 1;
	while (i < nb_philos)
	{
		if (philos[i].state != DEAD)
		{
			is_dead = 0;
			break ;
		}
	}
	if (is_dead)
	{
		return (1);
	}
	return (0);
}
