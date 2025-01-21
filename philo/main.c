/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:32:43 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/21 23:13:00 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_sim	*sim;

	if (argc < 5 || argc > 6)
		return (error_msg("Wrong number of arguments", NULL));
	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
		return (error_msg("Failed to allocate memory for simulation", NULL));
	philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
	{
		free(sim);
		return (error_msg("Failed to allocate memory for philosophers", NULL));
	}
	sim->philo = philo;
	philo->sim = sim;
	if (init_args(philo, argv) || init_mutexes(sim) || init_fork(sim))
	{
		destroy(philo);
		return (1);
	}
	init_philo(philo, sim, sim->forks);
	start_simulation(philo);
	destroy(philo);
	return (0);
}
