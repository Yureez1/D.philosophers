/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:10:28 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/16 17:41:35 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		philo_think(philo);
	while (1)
	{
		if (philo->meals_count == philo->meals_eaten)
		{
			philo->sim->simulation_end_flag = 1;
			break ;
		}
		if (philo->state == DEAD || philo->sim->simulation_end_flag)
		{
			philo_is_dead(philo);
			break ;
		}
        philo_eat(philo);
        philo_think(philo);
        philo_sleep(philo);
	}
	return (NULL);
}

void	philo_is_dead(t_philo *philo)
{
	print_action(philo, "has died");
	pthread_mutex_lock(&philo->dead_lock);
	philo->state = DEAD;
	pthread_mutex_unlock(&philo->dead_lock);
}

void	has_sim_stopped(t_philo *philo)
{
	int	i;
	int	all_dead;
	int	all_meals_eaten;

	i = 0;
	all_dead = 1;
	all_meals_eaten = 1;
	while (i < philo->nb_philos)
	{
		if (philo[i].state != DEAD)
		{
			all_dead = 0;
			break ;
		}
		if (philo->meals_count != -1
			&& philo[i].meals_eaten < philo[i].meals_count)
		{
			all_meals_eaten = 0;
			break ;
		}
		i++;
	}
	if (all_dead || all_meals_eaten)
		philo->sim->simulation_end_flag = 1;
	return ;
}
