/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:32:43 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/21 16:54:17 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_sim	*sim;

	(void)argc;
	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
		return (1);
	philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
	{
		free(sim);
		return (1);
	}
	sim->philo = philo;
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
