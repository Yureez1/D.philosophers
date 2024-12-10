/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:32:43 by jbanchon          #+#    #+#             */
/*   Updated: 2024/12/10 16:57:46 by jbanchon         ###   ########.fr       */
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
	is_initialized(&sim);
	if (start_simulation(&sim) != 0)
		return (1);
	cleanup_simulation(&sim);
	free(sim.params);
	return (0);
}

#include <stdio.h>
#include <pthread.h>

int is_initialized(t_simulation *sim)
{
    // Vérifier si la simulation est correctement initialisée
    if (!sim) {
        printf("Simulation is not initialized.\n");
        return 0;
    }

    if (!sim->params) {
        printf("Simulation parameters are not initialized.\n");
        return 0;
    }

    if (!sim->philo) {
        printf("Philosophers array is not initialized.\n");
        return 0;
    }

    if (!sim->forks) {
        printf("Forks array is not initialized.\n");
        return 0;
    }

    if (!sim->stop_lock) {
        printf("Stop lock is not initialized.\n");
        return 0;
    }

    // Vérifier si les philosophes sont correctement initialisés
    for (int i = 0; i < sim->params->philo_count; i++) {
        t_philo *philo = &sim->philo[i];

        if (!philo->right_fork || !philo->left_fork) {
            printf("Philosopher %d forks are not initialized.\n", philo->philo_id);
            return 0;
        }

        // Vérifier si les mutex sont initialisés (vérification indirecte)
        if (pthread_mutex_trylock(&philo->meal_lock) != 0) {
            printf("Philosopher %d meal lock is not initialized.\n", philo->philo_id);
            return 0;
        }

        if (pthread_mutex_trylock(&philo->dead_lock) != 0) {
            printf("Philosopher %d dead lock is not initialized.\n", philo->philo_id);
            return 0;
        }

        if (pthread_mutex_trylock(&philo->print_lock) != 0) {
            printf("Philosopher %d print lock is not initialized.\n", philo->philo_id);
            return 0;
        }

        // Réinitialisation des mutex après vérification
        pthread_mutex_unlock(&philo->meal_lock);
        pthread_mutex_unlock(&philo->dead_lock);
        pthread_mutex_unlock(&philo->print_lock);

        // Vérification des temps de repas et de vie
        if (philo->last_meal_time < 0) {
            printf("Philosopher %d has invalid last meal time.\n", philo->philo_id);
            return 0;
        }

        if (philo->meals_eaten < 0) {
            printf("Philosopher %d has invalid meals eaten count.\n", philo->philo_id);
            return 0;
        }
    }

    // Vérifier les paramètres de simulation
    if (sim->params->philo_count <= 0) {
        printf("Invalid number of philosophers.\n");
        return 0;
    }

    if (sim->params->time_to_die <= 0 || sim->params->time_to_eat <= 0 || sim->params->time_to_sleep <= 0) {
        printf("Invalid simulation times (time to die, eat or sleep).\n");
        return 0;
    }

    if (sim->params->meals_count <= 0) {
        printf("Invalid meals count.\n");
        return 0;
    }

    return 1;  // Tout est correctement initialisé
}
