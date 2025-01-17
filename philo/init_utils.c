/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:21:20 by julien            #+#    #+#             */
/*   Updated: 2025/01/17 14:21:20 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	init_mutexes(t_sim *sim)
{
	pthread_mutex_init(&(sim->dead_lock), NULL);
	pthread_mutex_init(&(sim->meal_lock), NULL);
	pthread_mutex_init(&(sim->print_lock), NULL);
	return (0);
}

void	init_fork(t_sim *sim)
{
	int	i;

	i = 0;
	sim->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* sim->philo->nb_philos);
	while (i < sim->philo->nb_philos)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
}
