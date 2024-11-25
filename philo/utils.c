/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:44 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/25 15:43:44 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	while (*str >= 9 && str <= 13 || (*str == 32))
		*str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		*str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str + '0');
		*str++;
	}
	return (sign * result);
}

int	ft_isdigit(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
