/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:30 by julien            #+#    #+#             */
/*   Updated: 2025/04/29 14:46:14 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;
	t_philo			*philo;

	if (argc < 5 || argc > 6)
		return (printf("Invalid number of args\n"), 1);
	memset(&sim, 0, sizeof(t_simulation));
	if (init_all(&sim, &philo, argc, argv))
	{
		printf("Failed to initialize simulation\n");
		return (1);
	}
	if (create_philo_threads(philo, &sim))
	{
		printf("Failed to create philosopher threads\n");
		destroy(&sim);
		free(philo);
		return (1);
	}
	for (int i = 0; i < sim.nb_philo; i++)
	{
		printf("Philosopher %d ate %d times\n", philo[i].philo_id,
			philo[i].meals_completed);
	}
	destroy(&sim);
	free(philo);
	return (0);
}
