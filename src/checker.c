/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:11:17 by mtomomit          #+#    #+#             */
/*   Updated: 2023/02/06 03:42:07 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	checker_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->died));
	if (philo->data->philo_died == 1)
	{
		pthread_mutex_unlock(&(philo->data->died));
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->died));
	pthread_mutex_lock(&(philo->data->died));
	if (philo->data->philo_died == 0 && \
		ft_mstime() - philo->last_meal >= philo->data->input->time_to_die)
	{
		philo->data->philo_died = 1;
		usleep(500);
		print_dead(philo, ft_mstime() - philo->data->start_time);
		pthread_mutex_unlock(&(philo->data->died));
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->died));
	return (1);
}

int	checker_all_ate(t_philo *philo)
{
	if (philo->data->input->number_of_meals != 0 && \
		philo->eat_times == philo->data->input->number_of_meals)
	{
		pthread_mutex_lock(&(philo->data->finish_eat));
		philo->data->all_ate++;
		philo->eat_times++;
		pthread_mutex_unlock(&(philo->data->finish_eat));
	}
	pthread_mutex_lock(&(philo->data->finish_eat));
	if (philo->data->all_ate == philo->data->input->number_of_philo)
	{
		pthread_mutex_unlock(&(philo->data->finish_eat));
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->finish_eat));
	return (1);
}

int	checker(t_philo *philo)
{
	if (!checker_dead(philo))
		return (0);
	if (!checker_all_ate(philo))
		return (0);
	return (1);
}
