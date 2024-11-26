/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:50 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/26 14:57:41 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*void	init_params(t_simulation *sim)
{
	int	i;

	sim->params = (t_params *)malloc(sizeof(t_params));
	if (!sim->params)
		error_msg("Error: Memory allocation for params failed", sim);
	printf("%d\n",sim->params->philo_count);
	if(sim->params->philo_count <= 0)
	{
		error_msg("Error: Invalid philo count.", sim);
		printf("%d\n",sim->params->philo_count);
	}
}*/
void	init_philo(t_simulation *sim)
{
	int i;
	
	sim->philo = (t_philo *)malloc(sim->params->philo_count * sizeof(t_philo));
	if (!sim->philo)
		error_msg("Error: Memory allocation for philo failed.", sim);
	i = 0;
	while (i < sim->params->philo_count)
	{
		sim->philo[i].philo_id = i;
		sim->philo[i].meals_eaten = 0;
		sim->philo[i].last_meal_time = 0;
		sim->philo[i].params = sim->params;
		sim->philo[i].left_fork = &sim->forks[i];
		sim->philo[i].right_fork = &sim->forks[(i + 1) % sim->params->philo_count];
		printf("Philo %d: left fork = %p, right fork = %p\n", i, sim->philo[i].left_fork, sim->philo[i].right_fork);
		i++;
	}
}

void	init_forks(t_simulation *sim)
{
	int	i;

	sim->forks = (pthread_mutex_t *)malloc(sim->params->philo_count
			* sizeof(pthread_mutex_t));
	if (!sim->forks)
		error_msg("Error: Memory allocation for forks failed.", sim);
	i = 0;
	while (i < sim->params->philo_count)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			error_msg("Error: Mutex initilialization for forks failed", sim);
			exit(EXIT_FAILURE);
		}
		printf("Fork %d initialized.\n", i);
		i++;
	}
	if (pthread_mutex_init(&sim->print_lock, NULL) != 0)
	{
		error_msg("Error: Mutex initilization for print lock failed", sim);
		exit(EXIT_FAILURE);
	}
	printf("Print lock initialized.\n");
}

void	init_simulation(t_simulation *sim)
{
	init_forks(sim);
	init_philo(sim);
}
