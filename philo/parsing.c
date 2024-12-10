/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:18:07 by jbanchon          #+#    #+#             */
/*   Updated: 2024/12/10 13:39:34 by jbanchon         ###   ########.fr       */
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
	handle_optional_arg(argc, sim, argv);
	return (0);
}

void	check_argc(int argc, t_simulation *sim)
{
	if (argc < 5 || argc > 6)
		error_msg("Usage: Nb of philo, Time to die, Time to eat, "
					"Time to sleep [Meals count]",
					sim);
}

void	init_params(t_simulation *sim, char **argv)
{
	sim->params->philo_count = ft_atoi(argv[1]);
	sim->params->time_to_die = ft_atoi(argv[2]);
	sim->params->time_to_eat = ft_atoi(argv[3]);
	sim->params->time_to_sleep = ft_atoi(argv[4]);
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

void	handle_optional_arg(int argc, t_simulation *sim, char **argv)
{
	if (argc == 6)
	{
		printf("argv[5]: %s\n", argv[5]);
		if(!is_valid_int(argv[5]))
			error_msg("Meals count must be a valid integer.\n", sim);
		sim->params->meals_count = ft_atoi(argv[5]);
	}
	else
	{
		printf("No argv[5] provided, setting meals_count to -1\n");
		sim->params->meals_count = -1;
	}
	if (sim->params->meals_count < -1)
		error_msg("Meals count must be a positive integer or -1\n", sim);
}
