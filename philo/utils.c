/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:20:08 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/30 12:45:46 by jbanchon         ###   ########.fr       */
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
	struct time_val	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	waiting(long long time, t_sim *sim)
{
	long long	start_time;
	long long	cur;

	start_time = get_time();
	while (!check_sim_end(sim))
	{
		cur = get_time();
		if ((cur - start_time) >= time)
			break ;
		usleep(100);
	}
}

void	philo_think(t_sim *sim)
{
	struct timeval get_time;
	struct timeval time_stat;
	int time_diff;

	gettimeofday(&get_time, NULL);
	while (1)
	{
		gettimeofday(&time_stat, NULL);
		time_diff = (time_stat.tv_usec - get_time.tv_usec) + (time_stat.tv_sec
				- get_time.tv_sec) * 1000000;
		if (time_diff > sim->time_to_eat * 900)
			break ;
		ft_usleep(sim->time_to_eat);
	}
}