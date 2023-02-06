/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:17:16 by mtomomit          #+#    #+#             */
/*   Updated: 2023/02/02 16:23:11 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_fork	*init_forks(t_input *input)
{
	t_fork	*forks;
	size_t	i;

	forks = (t_fork *)malloc(sizeof(t_fork) * input->number_of_philo);
	i = 0;
	while (i < input->number_of_philo)
	{
		pthread_mutex_init(&forks[i].fork, NULL);
		i++;
	}
	return (forks);
}

static t_data	*init_data(t_input *input)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->input = input;
	data->start_time = (long long)0;
	data->philo_died = 0;
	data->all_ate = 0;
	pthread_mutex_init(&data->finish_eat, NULL);
	pthread_mutex_init(&data->died, NULL);
	pthread_mutex_init(&data->print, NULL);
	return (data);
}

t_philo	*init_philo(t_input *input, t_fork *forks)
{
	t_philo	*philo;
	t_data	*data;
	size_t	i;

	i = 0;
	data = init_data(input);
	philo = (t_philo *)malloc(sizeof(t_philo) * input->number_of_philo);
	while (i < input->number_of_philo)
	{
		philo[i].philo_number = i + 1;
		philo[i].data = data;
		philo[i].eat_times = 0;
		philo[i].last_meal = 0;
		philo[i].r_fork = &forks[i];
		philo[i].l_fork = &forks[(i + 1) % input->number_of_philo];
		i++;
	}
	return (philo);
}
