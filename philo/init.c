/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:50 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/16 17:19:57 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*void	init(t_philo *philo, t_sim *sim)
{
	if (!init_mutexes(philo, sim))
		error_msg("Failed to initialize mutexes", philo);
	if (!init_philo(philo, sim, philo->forks))
		error_msg("Failed to initialize philos", philo);
}*/
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

int	init_philo(t_philo *philo, t_sim *sim, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philo->nb_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].meals_count = philo->meals_count;
		philo[i].start_time = get_current_time_ms();
		philo[i].last_meal_time = philo[i].start_time;
		philo[i].r_fork = &forks[i];
		philo[i].l_fork = &forks[(i + 1) % philo->nb_philos];
		philo[i].meal_lock = sim->meal_lock;
		philo[i].dead_lock = sim->dead_lock;
		philo[i].print_lock = sim->print_lock;
		philo[i].time_to_die = philo->time_to_die;
		philo[i].time_to_eat = philo->time_to_eat;
		philo[i].time_to_sleep = philo->time_to_sleep;
		philo[i].state = SLEEPING;
		philo[i].sim = sim;
		i++;
	}
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
