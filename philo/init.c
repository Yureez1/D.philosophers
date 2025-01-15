/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:50 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/15 18:21:57 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init(t_philo *philo)
{
	if (!init_mutexes(philo))
		error_msg("Failed to initialize mutexes", philo);
	if (!init_philo(philo))
		error_msg("Failed to initialize philos", philo);
}

void	init_args(t_philo *philo, char **argv)
{
	philo->nb_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		philo->meals_count = ft_atoi(argv[5]);
	else
		philo->meals_count = -1;
	if (philo->nb_philos <= 0 || philo->time_to_die <= 0
		|| philo->time_to_eat <= 0 || philo->time_to_sleep <= 0)
		error_msg("Invalid args", philo);
}

void	init_mutexes(t_philo *philo)
{
	int	i;

	i = 0;
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philos);
	if (!philo->forks)
		error("Failed to allocate memory for forks mutexes", philo);
	while (i < philo->nb_philos)
	{
		if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
			error_msg("Failed to initialize fork mutex", philo);
		i++;
	}
	philo->print_lock = malloc(sizeof(pthread_mutex_t));
	philo->meal_lock = malloc(sizeof(pthread_mutex_t));
	philo->dead_lock = malloc(sizeof(pthread_mutex_t));
	if (!philo->print_lock || !philo->meal_lock || !philo->dead_lock)
		error_msg("Failed to allocate memory for additionnal mutexes", philo);
	if (pthread_mutex_init(philo->print_lock, NULL) != 0
		|| pthread_mutex_init(philo->dead_lock, NULL) != 0
		|| pthread_mutex_init(philo->meal_lock, NULL) != 0)
		error_msg("Failed to initialize additionnal mutex", philo);
}

void	init_philo(t_philo *philo)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * nb_philos);
	if (!philos)
		error_msg("Failed to allocate memory for philosophers", philo);
	i = 0;
	while (i < nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].nb_philos = nb_philos;
		philos[i].meals_eaten = 0;
		philos[i].meals_count = meals_count;
		philos[i].time_to_die = time_to_die;
		philos[i].time_to_eat = time_to_eat;
		philos[i].time_to_sleep = time_to_sleep;
		philos[i].start_time = get_current_time_ms();
		philos[i].last_meal_time = philos[i].start_time;
		philos[i].forks = sim->forks;
		philos[i].meal_lock = sim->meal_lock;
		philos[i].dead_lock = sim->dead_lock;
		philos[i].meal_lock = sim->meal_lock;
		i++;
	}
	return (philos);
}
