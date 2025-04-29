/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:12:04 by julien            #+#    #+#             */
/*   Updated: 2025/04/30 00:18:52 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_or_done(t_simulation *sim, t_philo *philo)
{
	long long	current_time;
	long long	last_meal;

	pthread_mutex_lock(&(philo->meal_lock));
	current_time = get_time();
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&(philo->meal_lock));
	if ((current_time - last_meal) >= (sim->time_to_die))
	{
		end_mutex(sim);
		print_action(sim, philo->philo_id, "died");
		return (1);
	}
	pthread_mutex_lock(&(sim->sim_end_mutex));
	if (sim->meals_to_eat > 0 && sim->total_meals_eaten >= sim->nb_philo)
	{
		pthread_mutex_unlock(&(sim->sim_end_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(sim->sim_end_mutex));
	return (0);
}

static int	check_philosopher_status(t_simulation *sim, t_philo *philo,
	long long *last, int *done)
{
	int	not_done;

	pthread_mutex_lock(&(philo->meal_lock));
	*last = philo->last_meal_time;
	*done = philo->has_finished;
	not_done = (sim->meals_to_eat > 0 && !(*done));
	pthread_mutex_unlock(&(philo->meal_lock));
	if (!(*done) && get_time() - *last >= sim->time_to_die)
	{
		print_action(sim, philo->philo_id, "died");
		end_mutex(sim);
		return (1);
	}
	return (not_done);
}

static void	check_all_philosophers(t_simulation *sim, t_philo *philo,
	t_philo *end, int *all_done)
{
	t_philo		*cur;
	long long	last;
	int			done;

	cur = philo;
	*all_done = 1;
	while (cur < end && *all_done)
	{
		if (check_philosopher_status(sim, cur, &last, &done))
			*all_done = 0;
		if (!check_sim_end(sim))
			cur++;
		else
			break ;
	}
}

void	monitoring(t_simulation *sim, t_philo *philo)
{
	t_philo		*end;
	int			all_done;

	end = philo + sim->nb_philo;
	while (!check_sim_end(sim))
	{
		check_all_philosophers(sim, philo, end, &all_done);
		if (sim->meals_to_eat > 0 && all_done)
		{
			end_mutex(sim);
			return ;
		}
		usleep(100);
	}
}
