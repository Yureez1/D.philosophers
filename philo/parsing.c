/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:18:07 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/25 15:53:29 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_integer(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
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
		;
	return (-1);
	value = ft_atoi(argv);
	if (value <= 0)
		return (-1);
	return (value);
}

t_params	parse_input(int argc, char **argv)
{
	t_params	params;

	params.philo_count = parse_args(argv[1]);
	params.time_to_die = parse_args(argv[2]);
	params.time_to_eat = parse_args(argv[3]);
	params.time_to_sleep = parse_args(argv[4]);
	if (argc == 6)
		params.meals_count = parse_args(argv[5]);
	else
		params.meals_count = -1;
	if (params.philo_count == -1 || params.time_to_die == -1
		|| params.time_to_eat == -1 || params.time_to_sleep == -1 || (argv[6]
			&& params.meals_count == -1))
	{
		printf("Invalid arguments\n");
		exit(1);
	}
	return (params);
}
