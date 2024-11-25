/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:32:43 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/25 19:52:32 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	t_simulation sim;
	
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s philo_count time_to_die time_to_eat time_to_sleep [meals_count]\n", argv[0]);
		return (1);
	}
	parse_input(&sim, argc, argv);
	init_simulation(&sim);
	start_sim(&sim);
	cleanup_simulation(&sim);
	return (0);
}
