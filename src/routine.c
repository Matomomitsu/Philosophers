/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:51:09 by mtomomit          #+#    #+#             */
/*   Updated: 2023/02/06 03:51:04 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_think(t_philo *philo)
{
	print_action(philo, ft_mstime() - philo->data->start_time, "is thinking");
	if (philo->data->input->time_to_eat > philo->data->input->time_to_sleep)
	{
		if ((ft_mstime() - philo->last_meal + philo->data->input->time_to_eat)
			- philo->data->input->time_to_sleep > \
			philo->data->input->time_to_die)
			ft_msleep(philo->data->input->time_to_die - (ft_mstime() - \
					philo->last_meal));
		else
			ft_msleep(philo->data->input->time_to_eat - \
				philo->data->input->time_to_sleep);
	}
	usleep(1000);
}

void	philo_taken_a_fork(t_philo *philo)
{
	print_action(philo, ft_mstime() - philo->data->start_time, \
		"has taken a fork");
}

void	taking_forks_even(t_philo *philo)
{
	if (philo->data->input->time_to_die < philo->data->input->time_to_eat)
	{
		ft_msleep(philo->data->input->time_to_die - (ft_mstime() - \
			philo->last_meal));
		checker(philo);
	}
	pthread_mutex_lock(&(philo->r_fork->fork));
	philo_taken_a_fork(philo);
	pthread_mutex_lock(&(philo->l_fork->fork));
	philo_taken_a_fork(philo);
}

void	taking_forks(t_philo *philo)
{
	size_t	i;

	i = philo->philo_number;
	if (i % 2 == 1)
	{
		pthread_mutex_lock(&(philo->l_fork->fork));
		philo_taken_a_fork(philo);
		pthread_mutex_lock(&(philo->r_fork->fork));
		philo_taken_a_fork(philo);
	}
	else
		taking_forks_even(philo);
}

void	*routine(void *philo)
{
	while (1)
	{
		if (!checker((t_philo *)philo))
			break ;
		philo_eat((t_philo *)philo);
		philo_sleep((t_philo *)philo);
		philo_think((t_philo *)philo);
	}
	return (NULL);
}
