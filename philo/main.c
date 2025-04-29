/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:30 by julien            #+#    #+#             */
/*   Updated: 2025/04/29 23:19:31 by julien           ###   ########.fr       */
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
	destroy(&sim);
	free(philo);
	return (0);
}
