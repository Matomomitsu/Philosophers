/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:50:56 by mtomomit          #+#    #+#             */
/*   Updated: 2023/02/03 21:52:06 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_eat(t_philo *philo)
{
	taking_forks(philo);
	if (print_action(philo, ft_mstime() - philo->data->start_time, \
		"is eating"))
	{
		philo->last_meal = ft_mstime();
		ft_msleep(philo->data->input->time_to_eat);
		philo->eat_times++;
	}
	pthread_mutex_unlock(&(philo->l_fork->fork));
	pthread_mutex_unlock(&(philo->r_fork->fork));
}
