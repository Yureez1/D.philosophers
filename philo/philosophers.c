/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:50 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/25 20:20:35 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_simulation(t_simulation *sim)
{
	int	i;

	sim->params = (t_params *)malloc(sizeof(t_params));
	sim->philo = (t_philo *)malloc(sim->params->philo_count * sizeof(t_philo));
	if (!sim->params || sim->params->philo_count <= 0)
		error_msg("Error: Simulation parameters not initialized.", sim);
	i = 0;
	while (i < sim->params->philo_count)
	{
		sim->philo[i].philo_id = i;
		sim->philo[i].meals_eaten = 0;
		sim->philo[i].last_meal_time = 0;
		sim->philo[i].params = sim->params;
		i++;
	}
	sim->forks = (pthread_mutex_t *)malloc(sim->params->philo_count
			* sizeof(pthread_mutex_t));
	i = 0;
	while (i < sim->params->philo_count)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&sim->print_lock, NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Philo %d started\n", philo->philo_id);
	while (1)
	{
		printf("Philo %d is thinking\n", philo->philo_id);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		printf("Philo %d is eating\n", philo->philo_id);
		philo->meals_eaten++;
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		printf("Philo %d is sleeping\n", philo->philo_id);
		usleep(philo->params->time_to_sleep * 1000);
		if (philo->meals_eaten >= philo->params->meals_count)
			break ;
	}
	return (NULL);
}

void	start_sim(t_simulation *sim)
{
	pthread_t	*threads;
	int			i;

	threads = (pthread_t *)malloc(sim->params->philo_count * sizeof(pthread_t));
	i = 0;
	while (i < sim->params->philo_count)
	{
		sim->philo[i].left_fork = &sim->forks[i];
		sim->philo[i].right_fork = &sim->forks[(i + 1)
			% sim->params->philo_count];
		pthread_create(&threads[i], NULL, philo_routine,
			(void *)&sim->philo[i]);
		i++;
	}
	i = 0;
	while (i < sim->params->philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
}
