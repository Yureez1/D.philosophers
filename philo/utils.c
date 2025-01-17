/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:44 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/17 14:19:19 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	if (str == NULL)
		return (0);
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

size_t	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_action(t_philo *philo, const char *action)
{
	size_t	relative_time;

	pthread_mutex_lock(&philo->sim->print_lock);
	relative_time = get_current_time_ms() - philo->start_time;
	printf("%zu %d %s\n", relative_time, philo->id, action);
	pthread_mutex_unlock(&philo->sim->print_lock);
}

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

void	precise_sleep(size_t sleep_time)
{
	size_t	start;
	size_t	elapsed;
	size_t	remaining;

	start = get_current_time_ms();
	while (1)
	{
		elapsed = get_current_time_ms() - start;
		if (elapsed >= sleep_time)
			break ;
		remaining = sleep_time - elapsed;
		if (remaining > 50)
			usleep(remaining * 900);
		else
			usleep(100);
	}
}
