/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:20 by julien            #+#    #+#             */
/*   Updated: 2025/01/17 14:21:20 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_simulation_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->dead_lock);
	if (philo->sim->simulation_end_flag)
	{
		pthread_mutex_unlock(&philo->sim->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->dead_lock);
	return (0);
}

static void	take_forks(t_philo *philo)
{
	if (check_simulation_end(philo))
		return;
	if (philo->nb_philos == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		if (!check_simulation_end(philo))
			print_action(philo, "has taken a fork");
		precise_sleep(philo->time_to_die);
		pthread_mutex_unlock(philo->l_fork);
		return;
	}
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		if (!check_simulation_end(philo))
			print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		if (!check_simulation_end(philo))
			print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		if (!check_simulation_end(philo))
			print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		if (!check_simulation_end(philo))
			print_action(philo, "has taken a fork");
	}
}

static void	start_eating(t_philo *philo)
{
	size_t	start_time;

	if (check_simulation_end(philo))
		return;
	pthread_mutex_lock(&philo->dead_lock);
	start_time = get_current_time_ms();
	philo->last_meal_time = start_time;
	pthread_mutex_unlock(&philo->dead_lock);

	pthread_mutex_lock(&philo->meal_lock);
	philo->state = EATING;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);

	if (!check_simulation_end(philo))
		print_action(philo, "is eating");
}

void	philo_eat(t_philo *philo)
{
	if (check_simulation_end(philo))
		return;
	take_forks(philo);
	if (philo->nb_philos == 1)
		return;
	start_eating(philo);
	if (!check_simulation_end(philo))
		precise_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	philo_sleep(t_philo *philo)
{
	if (check_simulation_end(philo))
		return;
	pthread_mutex_lock(&philo->meal_lock);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->meal_lock);
	if (!check_simulation_end(philo))
		print_action(philo, "is sleeping");
	if (!check_simulation_end(philo))
		precise_sleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	if (check_simulation_end(philo))
		return;
	pthread_mutex_lock(&philo->meal_lock);
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->meal_lock);
	if (!check_simulation_end(philo))
		print_action(philo, "is thinking");
}
