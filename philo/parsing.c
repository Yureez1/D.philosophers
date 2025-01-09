/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:18:07 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/09 14:34:13 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_args(int argc, char **argv, t_simulation *sim)
{
	sim->params = malloc(sizeof(t_params));
	if (!sim->params)
		error_msg("Memory allocation failed for simulation parameters\n", sim);
	check_argc(argc, sim);
	init_params(sim, argv);
	validate_args(sim, argv);
	return (0);
}

void	check_argc(int argc, t_simulation *sim)
{
	if (argc < 5 || argc > 6)
		error_msg("Usage: Nb of philo, Time to die, Time to eat, "
					"Time to sleep [Meals count]",
					sim);
}

void	validate_args(t_simulation *sim, char **argv)
{
	if (!is_valid_int(argv[1]) || !is_valid_int(argv[2])
		|| !is_valid_int(argv[3]) || !is_valid_int(argv[4]))
		error_msg("Arguments must be valid positive integers\n", sim);
	if (sim->params->philo_count <= 0 || sim->params->philo_count > 200
		|| sim->params->time_to_die <= 0 || sim->params->time_to_eat <= 0
		|| sim->params->time_to_sleep <= 0)
		error_msg("All values must be positive integers greater than 0\n", sim);
}
