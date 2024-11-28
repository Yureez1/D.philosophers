/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:18:07 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/28 11:07:10 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_valid_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_params *params)
{
	if (argc < 5 || argc > 6)
		error_msg("Usage: Nb of philo, Time to die, Time to eat, "
					"Time to sleep [Meals count]");
	if (!is_valid_int(argv[1]) || !is_valid_int(argv[2])
		|| is_valid_int(argv[3]) || !is_valid_int(argv[4]))
		error_msg("Arguments must be valid positive integers.\n");
	params->philo_count = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (params->philo_count <= 0 || params->philo_count > 200
		|| params->time_to_die < 0 || params->time_to_eat < 0
		|| params->time_to_sleep < 0)
		error_msg("All values must be positive integers greater than 0\n");
	if (argc == 6)
	{
		if (!is_valid_int(argv[5]))
			error_msg("Meals count must be a valid integer.\n");
		params->meals_count = ft_atoi(argv[5]);
	}
	else
		params->meals_count = -1;
	if (params->meals_count < -1)
		error_msg("Meals count must be a positive integer or -1\n");
	return (0);
}
