/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:44:04 by julien            #+#    #+#             */
/*   Updated: 2025/01/27 10:57:24 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo **philo, t_simulation *sim)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * sim->nb_philo);
	if (!(*philo))
		return (1);
	while (i < sim->nb_philo)
	{
		(*philo)[i].simulation = sim;
		(*philo)[i].philo_id = i + 1;
		(*philo)[i].left_fork = i;
		if (i == sim->nb_philo - 1)
			(*philo)[i].right_fork = 0;
		else
			(*philo)[i].right_fork = i + 1;
		(*philo)[i].last_meal_time = get_time();
		(*philo)[i].meals_completed = 0;
		i++;
	}
	return (0);
}

int	create_philo_threads(t_philo *philo, t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->nb_philo)
	{
		philo[i].last_meal_time = get_time();
		if (pthread_create(&philo[i].philo_thread, NULL, &philo_routine,
				&philo[i]))
			return (1);
		i++;
	}
	monitoring(sim, philo);
	i = 0;
	while (i < sim->nb_philo)
	{
		pthread_join(philo[i].philo_thread, NULL);
		i++;
	}
	return (0);
}

int	init_args(t_simulation *sim, int argc, char **argv)
{
	sim->nb_philo = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	sim->sim_start_time = get_time();
	if (sim->nb_philo <= 0 || sim->time_to_die <= 0 || sim->time_to_eat <= 0
		|| sim->time_to_sleep <= 0)
		return (1);
	if (argc == 6)
	{
		sim->meals_to_eat = ft_atoi(argv[5]);
		if (sim->meals_to_eat <= 0)
			return (1);
		if (sim->nb_philo == 1)
			sim->meals_to_eat = 0;
	}
	if (init_mutex(sim))
	{
		free(sim->forks);
		return (1);
	}
	return (0);
}

int	init_mutex(t_simulation *sim)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(sim->print_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(sim->time_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(sim->sim_end_mutex), NULL))
		return (1);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nb_philo);
	if (!sim->forks)
		return (1);
	while (i < sim->nb_philo)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}
