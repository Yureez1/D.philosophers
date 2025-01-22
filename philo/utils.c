/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:44 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/22 16:31:40 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (!str)
	{
		error_msg("NULL argument", NULL);
		exit(1);
	}
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str)
	{
		error_msg("Invalid empty number", NULL);
		exit(1);
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if ((sign == 1 && result > INT_MAX) || 
			(sign == -1 && -result < INT_MIN))
		{
			error_msg("Number too large", NULL);
			exit(1);
		}
		str++;
	}
	if (*str)
	{
		error_msg("Invalid characters in number", NULL);
		exit(1);
	}
	return ((int)(sign * result));
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
