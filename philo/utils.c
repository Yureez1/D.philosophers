/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:20:34 by julien            #+#    #+#             */
/*   Updated: 2025/04/29 23:09:10 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcnmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (res > 9223372036854775807 && sign == -1)
		return (-1);
	else if (res > 9223372036854775807)
		return (0);
	return (res * sign);
}

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	print_action(t_simulation *sim, int philo_id, char *action)
{
	long long	current_time;
	int			sim_ended;

	pthread_mutex_lock(&(sim->sim_end_mutex));
	sim_ended = sim->sim_end;
	pthread_mutex_unlock(&(sim->sim_end_mutex));
	if (sim_ended && ft_strcnmp(action, "died", 4) != 0)
		return (0);
	pthread_mutex_lock(&(sim->print_lock));
	current_time = get_time();
	if (current_time < 0)
	{
		pthread_mutex_unlock(&(sim->print_lock));
		return (-1);
	}
	pthread_mutex_lock(&(sim->sim_end_mutex));
	sim_ended = sim->sim_end;
	pthread_mutex_unlock(&(sim->sim_end_mutex));
	if (!sim_ended || ft_strcnmp(action, "died", 4) == 0)
		printf("%lld %d %s\n", current_time - sim->sim_start_time, philo_id,
			action);
	pthread_mutex_unlock(&(sim->print_lock));
	return (0);
}

void	ft_usleep(long long ms)
{
	long long	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(ms / 10);
}
