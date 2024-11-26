/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:18:07 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/26 14:40:34 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_args(const char *argv)
{
	int	value;

	if (!is_integer(argv))
		return (-1);
	value = ft_atoi(argv);
	if (value <= 0)
		return (-1);
	return (value);
}

void	parse_input(t_simulation *sim, int argc, char **argv)
{
	sim->params = (t_params *)malloc(sizeof(t_params));
	if (!sim->params)
	{
		error_msg("Failed to allocate memory for params.", sim);
		exit(EXIT_FAILURE);
	}
	init_args(sim, argc, argv);
}

void	init_args(t_simulation *sim, int argc, char **argv)
{
	sim->params->philo_count = parse_args(argv[1]);
	sim->params->time_to_die = parse_args(argv[2]);
	sim->params->time_to_eat = parse_args(argv[3]);
	sim->params->time_to_sleep = parse_args(argv[4]);
	if (argc == 6)
		sim->params->meals_count = parse_args(argv[5]);
	else
		sim->params->meals_count = -1;
	if (sim->params->philo_count <= 0 || sim->params->time_to_die <= 0
		|| sim->params->time_to_eat <= 0 || sim->params->time_to_sleep <= 0)
	{
		error_msg("Invalid arguments", sim);
		exit(EXIT_FAILURE);
	}
	if (sim->params->philo_count <= 0)
		error_msg("Error: Invalid philo count", sim);
}
