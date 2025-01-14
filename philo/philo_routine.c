/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:10:28 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/14 18:18:35 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_simulation *sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	while (1)
	{
		pthread_mutex_lock(&philo->dead_lock);
		if (*(sim->philo->dead) == 1)
		{
			pthread_mutex_unlock(&philo->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->dead_lock);
		eat(philo);
		go_to_sleep(philo);
		think(philo);
	}
	return (NULL);
}

int	philo_is_dead(t_philo *philo)
{
	int	dead_status;

	pthread_mutex_lock(&philo->dead_lock);
	dead_status = *philo->dead;
	pthread_mutex_unlock(&philo->dead_lock);
	return (dead_status);
}

int	is_dead(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->philo_count)
	{
		pthread_mutex_lock(&sim->philo[i].meal_lock);
		if (get_current_time_ms()
			- sim->philo[i].last_meal_time > sim->time_to_die)
		{
			print_action(&sim->philo[i], "has died");
			pthread_mutex_lock(&sim->philo[i].meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&sim->philo[i].meal_lock);
		i++;
	}
	return (0);
}

// void	*monitor_routine(void *arg)
// {
// 	t_simulation	*sim;

// 	sim = (t_simulation *)arg;
// 	while (!check_simulation_stopped(sim))
// 	//while (1)
// 	{
// 		if (is_dead(sim))
// 		{
// 			// pthread_mutex_lock(sim->stop_lock);
// 			sim->simulation_stopped = 1;
// 			// pthread_mutex_unlock(sim->stop_lock);
// 			break ;
// 		}
// 		if (all_philo_ate(sim))
// 		{
// 			// pthread_mutex_lock(sim->stop_lock);
// 			sim->simulation_stopped = 1;
// 			// pthread_mutex_unlock(sim->stop_lock);
// 			break ;
// 		}
// 		usleep(1000);
// 	}
// 	return (NULL);
// }

void *monitor_routine(void *arg)
{
	t_simulation *sim;

	sim = (t_simulation *)arg;
	while(1)
	{
		pthread_mutex_lock(&sim->philo->dead_lock);
		if (*(sim->philo[0].dead) == 1)
		{
			pthread_mutex_unlock(&sim->philo->dead_lock);
			break;
		}
		pthread_mutex_unlock(&sim->philo->dead_lock);
		if(is_dead(sim))
		{
			pthread_mutex_lock(&sim->philo->dead_lock);
			*(sim->philo[0].dead) = 1;
			pthread_mutex_unlock(&sim->philo->dead_lock);
			break;
		}
		if(all_philo_ate(sim))
		{
			pthread_mutex_lock(&sim->philo->dead_lock);
			*(sim->philo[0].dead) = 1;
			pthread_mutex_unlock(&sim->philo->dead_lock);
			break;
		}
		usleep(1000);
	}
	return(NULL);
}

int	all_philo_ate(t_simulation *sim)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	if (sim->meals_count == -1)
		return (0);
	while (i < sim->philo_count)
	{
		pthread_mutex_lock(&sim->philo[i].meal_lock);
		if (sim->philo[i].meals_eaten > sim->meals_count)
			total++;
		pthread_mutex_unlock(&sim->philo[i].meal_lock);
		i++;
	}
	if (total == sim->philo_count)
	{
		pthread_mutex_lock(&sim->philo[0].dead_lock);
		*(sim->philo[0].dead) = 1;
		pthread_mutex_unlock(&sim->philo[0].dead_lock);
		return(1);
	}
	return (0);
}

int	check_simulation_stopped(t_simulation *sim)
{
	int	stopped;

	pthread_mutex_lock(&sim->stop_lock);
	stopped = sim->simulation_stopped;
	pthread_mutex_unlock(&sim->stop_lock);
	return (stopped);
}
