/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:39:04 by jbanchon          #+#    #+#             */
/*   Updated: 2025/05/13 22:42:15 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(&(sim->forks[philo->left]));
	print_stat(sim, philo->philo_id, "has taken a fork");
	if (sim->nb_philo != 1)
	{
		pthread_mutex_lock(&(sim->forks[philo->right]));
		print_stat(sim, philo->philo_id, "has taken a fork");
		print_stat(sim, philo->philo_id, "is eating");
		pthread_mutex_lock(&(sim->time_mutex));
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&(sim->time_mutex));
		philo->meals_count++;
		waiting((long long)sim->time_to_eat, sim);
		pthread_mutex_unlock(&(sim->forks[philo->right]));
	}
	pthread_mutex_unlock(&(sim->forks[philo->left]));
	return (0);
}

static void	life_status(t_sim *sim, t_philo *philo)
{
	if (sim->nb_philo - 1 == philo->philo_id && philo->meals_count == 0)
		usleep(1);
	philo_eat(sim, philo);
	if (sim->nb_philo == 1)
		waiting((long long)sim->time_to_sleep, sim);
}

void	*philo_routine(void *argv)
{
	t_sim	*sim;
	t_philo	*philo;

	philo = (t_philo *)argv;
	sim = philo->sim;
	if (philo->philo_id % 2 == 0)
		philo_think(sim);
	while (!check_sim_end(sim))
	{
		life_status(sim, philo);
		if (sim->nb_eat == philo->meals_count)
		{
			sim->completed_meals++;
			break ;
		}
		print_stat(sim, philo->philo_id, "is sleeping");
		waiting((long long)sim->time_to_sleep, sim);
		print_stat(sim, philo->philo_id, "is thinking");
	}
	return (0);
}

int	print_stat(t_sim *sim, int philo_id, char *msg)
{
	long long	cur_time;

	pthread_mutex_lock(&(sim->print_mutex));
	cur_time = get_time();
	if (cur_time < 0)
		return (-1);
	if (!check_sim_end(sim))
		printf("%lld %d %s\n", cur_time - sim->start_time, philo_id, msg);
	if (ft_strncmp(msg, "died", 4) == 0)
		return (0);
	pthread_mutex_unlock(&(sim->print_mutex));
	return (0);
}

void	monitoring(t_sim *sim, t_philo *philo)
{
	int			i;
	long long	cur_time;

	while (!check_sim_end(sim))
	{
		if ((sim->nb_eat != 0) && (sim->nb_philo == sim->completed_meals))
			lock_and_unlock_mutexes(sim);
		i = 0;
		while (i < sim->nb_philo)
		{
			cur_time = get_time();
			if ((cur_time - philo[i].last_meal_time) >= (sim->time_to_die))
			{
				print_stat(sim, i, "died");
				lock_and_unlock_mutexes(sim);
				pthread_mutex_unlock(&(sim->print_mutex));
			}
			i++;
		}
	}
}
