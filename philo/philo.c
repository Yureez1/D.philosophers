/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:41:22 by julien            #+#    #+#             */
/*   Updated: 2025/04/29 13:56:11 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_simulation *sim, t_philo *philo)
{
	pthread_mutex_lock(&(sim->forks[philo->left_fork]));
	print_action(sim, philo->philo_id, "has taken a fork");
	if (sim->nb_philo == 1)
	{
		philo_wait(sim->time_to_die, sim);
		pthread_mutex_unlock(&(sim->forks[philo->left_fork]));
		return (1);
	}
	pthread_mutex_lock(&(sim->forks[philo->right_fork]));
	print_action(sim, philo->philo_id, "has taken a fork");
	print_action(sim, philo->philo_id, "is eating");
	pthread_mutex_lock(&(philo->meal_lock));
	philo->last_meal_time = get_time();
	philo->meals_completed++;
	pthread_mutex_unlock(&(philo->meal_lock));
	philo_wait(sim->time_to_eat, sim);
	pthread_mutex_unlock(&(sim->forks[philo->right_fork]));
	pthread_mutex_unlock(&(sim->forks[philo->left_fork]));
	return (0);
}

void	philo_think_and_sleep(t_simulation *sim, t_philo *philo)
{
	long long	think_time;

	if (check_sim_end(sim))
		return ;
	print_action(sim, philo->philo_id, "is sleeping");
	philo_wait(sim->time_to_sleep, sim);
	print_action(sim, philo->philo_id, "is thinking");
	think_time = sim->time_to_eat / 2;
	if (think_time < 1)
		think_time = 1;
	else if (think_time > 100)
		think_time = 100;
	philo_wait(think_time, sim);
}

static void	philo_eat_routine(t_simulation *sim, t_philo *philo)
{
	int	is_first_meal;

	if (check_sim_end(sim))
		return ;
	is_first_meal = (philo->meals_completed == 0);
	if (sim->nb_philo > 1 && philo->philo_id == sim->nb_philo - 1
		&& is_first_meal)
		usleep(500);
	pthread_mutex_lock(&philo->meal_lock);
	pthread_mutex_unlock(&philo->meal_lock);
	if (!check_sim_end(sim))
		philo_eat(sim, philo);
	if (sim->nb_philo == 1)
		philo_wait(sim->time_to_die, sim);
}

static int	philo_actions(t_simulation *sim, t_philo *philo)
{
	pthread_mutex_lock(&(philo->meal_lock));
	if (philo->has_finished)
	{
		pthread_mutex_unlock(&(philo->meal_lock));
		return (1);
	}
	pthread_mutex_unlock(&(philo->meal_lock));
	philo_eat_routine(sim, philo);
	pthread_mutex_lock(&(philo->meal_lock));
	if (!philo->has_finished && sim->meals_to_eat > 0
		&& philo->meals_completed >= sim->meals_to_eat)
	{
		philo->has_finished = 1;
		pthread_mutex_lock(&(sim->sim_end_mutex));
		sim->total_meals_eaten++;
		if (sim->total_meals_eaten >= sim->nb_philo)
			sim->sim_end = 1;
		pthread_mutex_unlock(&(sim->sim_end_mutex));
	}
	pthread_mutex_unlock(&(philo->meal_lock));
	philo_think_and_sleep(sim, philo);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_simulation	*sim;
	t_philo			*philo;

	philo = (t_philo *)arg;
	sim = philo->simulation;
	if (sim->nb_philo > 1 && philo->philo_id % 2 == 0)
		philo_think_and_sleep(sim, philo);
	while (!check_sim_end(sim))
	{
		if (philo_actions(sim, philo))
			break ;
	}
	return (0);
}
