/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:32:43 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/20 14:40:26 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_sim	*sim;

	(void)argc;
	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
		return (1);
	philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
	{
		free(sim);
		return (1);
	}
	printf("%d\n", ft_atoi("42"));          // Doit retourner 42
	printf("%d\n", ft_atoi("-42"));         // Doit retourner -42
	printf("%d\n", ft_atoi("0"));           // Doit retourner 0
	printf("%d\n", ft_atoi("abc"));         // Doit gérer ce cas
	printf("%d\n", ft_atoi("2147483647"));  // Limite supérieure d'un int
	printf("%d\n", ft_atoi("-2147483648")); // Limite inférieure d'un int
	sim->philo = philo;
	init_args(philo, argv);
	init_mutexes(sim);
	init_fork(sim);
	init_philo(philo, sim, sim->forks);
	start_simulation(philo);
	destroy(philo);
	return (0);
}
