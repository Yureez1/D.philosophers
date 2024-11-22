/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:03:47 by jbanchon          #+#    #+#             */
/*   Updated: 2024/11/22 16:08:28 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHER_H

typedef struct *s_philo
{
	struct s_data *data;
	pthread_mutex_t lock;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
}
t_philo;

typedef struct *s_data
{
	u_int64_t death_time;
	u_int64_t eat_time;
	u_int64_t sleep_time;
	u_int64_t start_time;
	pthread_mutex_t *fork;
}
t_data;

#endif