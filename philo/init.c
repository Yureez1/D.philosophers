/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:50 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/28 10:25:29 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->params->meals_count = 0;
	sim->params->philo_count = 0;
	sim->params->time_to_die = 0;
	sim->params->time_to_eat = 0;
	sim->params->time_to_sleep = 0;
	if (pthread_mutex_init(&sim->print_lock, NULL) != 0)
		error_msg("Iniliazation failed for print_lock\n");
	while (i < sim->params->philo_count)
	{
		sim->philo[i].philo_id = i;
		sim->philo[i].meals_eaten = 0;
		sim->philo[i].last_meal_time = 0;
		if (pthread_mutex_init(&sim->philo[i].meal_lock, NULL) != 0)
			error_msg("Inilization for meal_lock failed\n");
		if (i == 0)
			sim->philo[i].left_fork = &sim->forks[sim->params->philo_count - 1];
		else
			sim->philo[i].left_fork = &sim->forks[i - 1];
		sim->philo[i].right_fork = &sim->forks[i];
		i++;
	}
	return (0);
}

int init_simulation(t_simulation *sim, t_params *params)
{

}
