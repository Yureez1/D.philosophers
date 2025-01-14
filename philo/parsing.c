/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:18:07 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/14 18:08:55 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_args(int argc, char **argv, t_simulation *sim)
{
	check_argc(argc, sim);
	init_ (sim, argv);
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
	if (sim->philo_count <= 0 || sim->philo_count > 200
		|| sim->time_to_die <= 0 || sim->time_to_eat <= 0
		|| sim->time_to_sleep <= 0)
		error_msg("All values must be positive integers greater than 0\n", sim);
}

void	init_ (t_simulation *sim, char **argv)
{
	sim->philo_count = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		sim->meals_count = ft_atoi(argv[5]);
	else
		sim->meals_count = -1;
}
