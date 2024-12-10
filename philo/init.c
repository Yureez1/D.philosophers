/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:50 by jbanchon          #+#    #+#             */
/*   Updated: 2024/12/10 17:30:45 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_simulation *sim)
{
	if (allocate_simulation_ressources(sim) != 0)
		return (1);
	if (init_forks(sim) != 0)
		return (1);
	if (init_philosophers(sim) != 0)
		return (1);
	return (0);
}

int	allocate_simulation_ressources(t_simulation *sim)
{
	/*int i;

	i = 0;
	if (!(sim->philo = malloc(sizeof(t_philo) * sim->params->philo_count)))
		return (error_msg("Memory allocation for philosophers failed\n", sim));
	if (!(sim->forks = malloc(sizeof(pthread_mutex_t) * sim->params->philo_count)))
		return (error_msg("Memory allocation for forks failed\n", sim));
	while (i < sim->params->philo_count)
	{
		if (!(sim->philo[i].left_fork = malloc(sizeof(pthread_mutex_t))))
			return(error_msg("Memory allocation for left fork failed\n", sim));
		if(!(sim->philo[i].right_fork = malloc(sizeof(pthread_mutex_t))))
			return(error_msg("Memory allocation for right fork failed\n", sim));
		i++;
	}
	return (0);*/
	int i;

    i = 0;
    if (!(sim->philo = malloc(sizeof(t_philo) * sim->params->philo_count)))
        return (error_msg("Memory allocation for philosophers failed\n", sim));
    if (!(sim->forks = malloc(sizeof(pthread_mutex_t) * sim->params->philo_count)))
        return (error_msg("Memory allocation for forks failed\n", sim));

    // Initialiser les fourches en allocant des mutex
    while (i < sim->params->philo_count)
    {
        if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
            return (error_msg("Initialization failed for forks", sim));
        i++;
    }
    return (0);
}

int	init_forks(t_simulation *sim)
{
	/*int	i;

	i = 0;
	while (i < sim->params->philo_count)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			return (error_msg("Initialization failed for forks", sim));
		if (pthread_mutex_init(sim->philo[i].left_fork, NULL) != 0)
			return (error_msg("Initialization failed for left forks", sim));
		if (pthread_mutex_init(sim->philo[i].right_fork, NULL) != 0)
			return (error_msg("Initialization failed for right forks", sim));
		i++;
	}
	return (0);*/
	
	    int i;

    i = 0;
    while (i < sim->params->philo_count)
    {
        // Les fourches sont déjà allouées dans `sim->forks` dans `allocate_simulation_ressources`.
        // Nous devons juste les lier correctement aux philosophes.
        sim->philo[i].left_fork = &sim->forks[(i + sim->params->philo_count - 1) % sim->params->philo_count];
        sim->philo[i].right_fork = &sim->forks[i];

        // Initialisation des mutex pour les fourches de chaque philosophe
        if (pthread_mutex_init(sim->philo[i].left_fork, NULL) != 0)
            return (error_msg("Initialization failed for left fork", sim));
        if (pthread_mutex_init(sim->philo[i].right_fork, NULL) != 0)
            return (error_msg("Initialization failed for right fork", sim));

        i++;
    }
    return (0);
}

int	init_philosophers(t_simulation *sim)
{
	/*int	i;

	i = 0;
	while (i < sim->params->philo_count)
	{
		sim->philo[i].philo_id = i;
		sim->philo[i].meals_eaten = 0;
		sim->philo[i].last_meal_time = 0;
		if (init_mutex(&sim->philo[i].meal_lock,
				"Initialization for meal_lock failed\n", sim) != 0)
			return (1);
		sim->philo[i].left_fork = &sim->forks[(i + sim->params->philo_count - 1)
			% sim->params->philo_count];
		sim->philo[i].right_fork = &sim->forks[i];
		sim->philo[i].sim = sim;
		i++;
	}
	return (0);*/
	    int i;

    i = 0;
    while (i < sim->params->philo_count)
    {
        sim->philo[i].philo_id = i;
        sim->philo[i].meals_eaten = 0;
        sim->philo[i].last_meal_time = 0;
        if (init_mutex(&sim->philo[i].meal_lock, "Initialization for meal_lock failed\n", sim) != 0)
            return (1);
        
        // On assigne les fourches correctement ici, sans nécessiter d'allocation supplémentaire.
        sim->philo[i].sim = sim;
        i++;
    }
    return (0);
}

int	init_mutex(pthread_mutex_t *mutex, char *error_message,
		t_simulation *sim)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		return (error_msg(error_message, sim));
	return (0);
}
