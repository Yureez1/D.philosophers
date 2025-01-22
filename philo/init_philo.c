/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:20 by julien            #+#    #+#             */
/*   Updated: 2025/01/17 14:21:20 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philo_timings(t_philo *philo, int i)
{
	philo[i].start_time = get_current_time_ms();
	philo[i].last_meal_time = philo[i].start_time;
	philo[i].time_to_die = philo->time_to_die;
	philo[i].time_to_eat = philo->time_to_eat;
	philo[i].time_to_sleep = philo->time_to_sleep;
}

static void	init_philo_mutexes(t_philo *philo, t_sim *sim, int i)
{
	philo[i].meal_lock = sim->meal_lock;
	philo[i].dead_lock = sim->dead_lock;
	philo[i].print_lock = sim->print_lock;
}

static void	init_philo_forks(t_philo *philo, pthread_mutex_t *forks, int i)
{
	philo[i].r_fork = &forks[i];
	philo[i].l_fork = &forks[(i + 1) % philo->nb_philos];
}

int	init_philo(t_philo *philo, t_sim *sim, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philo->nb_philos)
	{
		philo[i].id = i + 1;
		philo[i].nb_philos = philo->nb_philos;
		philo[i].meals_eaten = 0;
		philo[i].meals_count = philo->meals_count;
		init_philo_timings(philo, i);
		init_philo_mutexes(philo, sim, i);
		init_philo_forks(philo, forks, i);
		philo[i].state = SLEEPING;
		philo[i].sim = sim;
		i++;
	}
	return (0);
}
