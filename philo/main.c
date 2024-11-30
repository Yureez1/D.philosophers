/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:32:43 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/30 13:09:46 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	sim.params = malloc(sizeof(t_params));
	if (!sim.params)
		error_msg("Error: Memory allocation for params failed\n", &sim);
	if (parse_args(argc, argv, &sim) != 0)
		return (1);
	if (init_philo(&sim) != 0)
		return (1);
	if (start_simulation(&sim) != 0)
		return (1);
	cleanup_simulation(&sim);
	free(sim.params);
	return (0);
}
