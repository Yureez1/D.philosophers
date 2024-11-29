/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:18:07 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/29 13:17:06 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_args(int argc, char **argv, t_simulation *sim)
{
	if (argc < 5 || argc > 6)
		error_msg("Usage: Nb of philo, Time to die, Time to eat, "
					"Time to sleep [Meals count]", sim);
	if (!is_valid_int(argv[1]) || !is_valid_int(argv[2])
		|| is_valid_int(argv[3]) || !is_valid_int(argv[4]))
		error_msg("Arguments must be valid positive integers.\n", sim);
	sim->params->philo_count = ft_atoi(argv[1]);
	sim->params->time_to_die = ft_atoi(argv[2]);
	sim->params->time_to_eat = ft_atoi(argv[3]);
	sim->params->time_to_sleep = ft_atoi(argv[4]);
	if (sim->params->philo_count <= 0 || sim->params->philo_count > 200
		|| sim->params->time_to_die < 0 || sim->params->time_to_eat < 0
		|| sim->params->time_to_sleep < 0)
		error_msg("All values must be positive integers greater than 0\n", sim);
	if (argc == 6)
	{
		if (!is_valid_int(argv[5]))
			error_msg("Meals count must be a valid integer.\n", sim);
		sim->params->meals_count = ft_atoi(argv[5]);
	}
	else
		sim->params->meals_count = -1;
	if (sim->params->meals_count < -1)
		error_msg("Meals count must be a positive integer or -1\n", sim);
	return (0);
}
