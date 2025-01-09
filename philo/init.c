/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:50 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/09 15:43:54 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_simulation *sim)
{
	if (allocate_simulation_ressources(sim) != 0)
		return (1);
	if (init_forks(sim) != 0)
		return (1);
	if (init_philosophers(sim) != 0)
		return (1);
	return (0);
}

int	allocate_simulation_ressources(t_simulation *sim)
{
	if (!(sim->philo = malloc(sizeof(t_philo) * sim->params->philo_count)))
		return (error_msg("Memory allocation for philosophers failed\n", sim));
	if (!(sim->forks = malloc(sizeof(pthread_mutex_t)
				* sim->params->philo_count)))
		return (error_msg("Memory allocation for forks failed\n", sim));
	if (!(sim->stop_lock = malloc(sizeof(pthread_mutex_t))))
		return (error_msg("Memory allocation for stop lock failed\n", sim));
	return (0);
}

int	init_philosophers(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->simulation_stopped = 0;
	sim->start_time = get_current_time_ms();
	while (i < sim->params->philo_count)
	{
		sim->philo[i].philo_id = i + 1;
		sim->philo[i].meals_eaten = 0;
		sim->philo[i].last_meal_time = sim->start_time;
		sim->philo[i].left_fork = &sim->forks[(i + sim->params->philo_count - 1)
			% sim->params->philo_count];
		sim->philo[i].right_fork = &sim->forks[i];
		sim->philo[i].sim = sim;
		i++;
	}
	return (0);
}

int		init_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->params->philo_count)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
	return(0);
}

void	init_params(t_simulation *sim, char **argv)
{
	sim->params->philo_count = ft_atoi(argv[1]);
	sim->params->time_to_die = ft_atoi(argv[2]);
	sim->params->time_to_eat = ft_atoi(argv[3]);
	sim->params->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		sim->params->meals_count = ft_atoi(argv[5]);
	else
		sim->params->meals_count = -1;
}
