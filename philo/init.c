/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:46:09 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/30 12:28:29 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_sim *sim)
{
	int	i;

	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&sim->time_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&sim->sim_end_mutex, NULL) != 0)
		return (1);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nb_philo);
	if (!sim->forks)
		return (1);
	i = 0;
	while (i < sim->nb_philo)
	{
		if (pthread_mutex_init(&sim->forks[i]), NULL) != 0)
            return (1);
		i++;
	}
	return (0);
}
int	init_params(t_sim *sim, int argc, char **argv)
{
	sim->nb_philo = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (sim->nb_philo <= 0 || sim->nb_philo > 200 || sim->time_to_die <= 0
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0)
		return (1);
	if (argc == 6)
	{
		sim->nb_eat = ft_atoi(argv[5]);
		if (sim->nb_eat <= 0)
			return (1);
		if (sim->nb_philo == 1)
			sim->nb_eat = 0;
	}
	if (init_mutexes(sim) != 0)
	{
		free(sim->forks);
		return (1);
	}
	return (0);
}
int	init_philos(t_philo *philo, t_sim *sim)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * sim->nb_philo);
	if (!philo)
		return (1);
	while (i < sim->nb_philo)
	{
		(*philo)[i].sim = sim;
		(*philo)[i].philo_id = i + 1;
		(*philo)[i].left = i;
		if (i == sim->nb_philo - 1)
			(*philo)[i].right = 0;
		else
			(*philo)[i].right = i + 1;
		(*philo)[i].last_meal_time = get_time();
		(*philo)[i].meals_count = 0;
		i++;
	}
	return (0);
}

int	create_threads(t_philo *philo, t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nb_philo)
	{
		philo[i].last_meal_time = get_time();
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return (1);
		i++;
	}
	monitoring_threads(sim, philo);
	i = 0;
	while (i < sim->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}
