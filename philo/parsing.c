/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:18:07 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/25 20:16:35 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_integer(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str))
			return (0);
		i++;
	}
	return (1);
}

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

t_params	parse_input(t_simulation *sim, int argc, char **argv)
{
	t_params	params;

	sim->params = (t_params *)malloc(sizeof(t_params));
	if (!sim->params)
	{
		error_msg("Failed to allocate memory for params.", sim);
		exit(1);
	}
	params.philo_count = parse_args(argv[1]);
	params.time_to_die = parse_args(argv[2]);
	params.time_to_eat = parse_args(argv[3]);
	params.time_to_sleep = parse_args(argv[4]);
	if (argc == 6)
		params.meals_count = parse_args(argv[5]);
	else
		params.meals_count = -1;
	if (params.philo_count <= 0 || params.time_to_die <= 0
		|| params.time_to_eat <= 0 || params.time_to_sleep <= 0)
	{
		error_msg("Invalid arguments.", sim);
		exit(1);
	}
	*(sim->params) = params;
	return (params);
}
