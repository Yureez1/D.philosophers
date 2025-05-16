/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:06:14 by julien            #+#    #+#             */
/*   Updated: 2025/05/16 11:41:51 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_sim *sim)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(sim->print_mutex));
	pthread_mutex_destroy(&(sim->time_mutex));
	pthread_mutex_destroy(&(sim->sim_end_mutex));
	while (i < sim->nb_philo)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	free(sim->forks);
}

int	main(int argc, char **argv)
{
	t_sim	sim;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
		return (printf("Error: Invalid number of arguments\n"));
	memset(&sim, 0, sizeof(t_sim));
	if (init_params(&sim, argc, argv) == 1)
		return (printf("Error: Invalid arguments\n"));
	if (init_philos(&philo, &sim) == 1)
	{
		printf("Error: Invalid philosophers\n");
		destroy_mutexes(&sim);
		return (1);
	}
	if (create_threads(philo, &sim) == 1)
	{
		printf("Error: Invalid threads\n");
		destroy_mutexes(&sim);
		free(philo);
		return (1);
	}
	destroy_mutexes(&sim);
	free(philo);
	return (0);
}
