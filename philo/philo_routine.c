/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:10:28 by jbanchon          #+#    #+#             */
/*   Updated: 2024/12/10 16:38:36 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->sim->stop_lock);
		if (philo->sim->simulation_stopped)
		{
			pthread_mutex_unlock(philo->sim->stop_lock);
			break ;
		}
		pthread_mutex_unlock(philo->sim->stop_lock);
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		go_to_sleep(philo);
		think(philo);
	}
	return (NULL);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_current_time_ms()
		- philo->last_meal_time > philo->sim->params->time_to_die)
	{
		print_action(philo, "has died");
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;
	int				i;

	sim = (t_simulation *)arg;
	while (!sim->simulation_stopped)
	{
		i = 0;
		while (i < sim->params->philo_count)
		{
			if (is_dead(&sim->philo[i]))
			{
				sim->simulation_stopped = 1;
				break ;
			}
			i++;
		}
		if (all_philo_ate(sim))
		{
			sim->simulation_stopped = 1;
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

int	all_philo_ate(t_simulation *sim)
{
	int	i;

	i = 0;
	if (sim->params->meals_count == -1)
		return (0);
	while (i < sim->params->philo_count)
	{
		printf("Philo %d has eaten %d meals\n", i, sim->philo[i].meals_eaten);
		if (sim->philo[i].meals_eaten < sim->params->meals_count)
			return (0);
	}
	return (1);
}

int	start_simulation(t_simulation *sim)
{
	int			i;
	pthread_t	monitor_thread;

	sim->start_time = get_current_time_ms();
	i = 0;
	while (i < sim->params->philo_count)
	{
		if (pthread_create(&(sim->philo[i].thread), NULL, philo_routine,
				(void *)&(sim->philo[i])) != 0)
		{
			error_msg("Failed to create thread for philo", sim);
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine,
			(void *)sim) != 0)
	{
		error_msg("Failed to create monitor thread", sim);
		return (1);
	}
	i = 0;
	while (i < sim->params->philo_count)
	{
		if (pthread_join(sim->philo[i].thread, NULL) != 0)
		{
			error_msg("Failed to join thread for philo", sim);
			return (1);
		}
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		error_msg("Failed to join monitor thread", sim);
		return (1);
	}
	return (0);
}
