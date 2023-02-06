/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:56:10 by mtomomit          #+#    #+#             */
/*   Updated: 2023/02/02 16:27:41 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	sanitize_philos(t_philo *philos, size_t number_of_philo)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(&(philos[i].data->finish_eat));
	pthread_mutex_destroy(&(philos[i].data->died));
	pthread_mutex_destroy(&(philos[i].data->print));
	philos[i].data->input = NULL;
	free(philos[i].data);
	while (i < number_of_philo)
	{
		pthread_mutex_destroy(&(philos[i].l_fork->fork));
		i++;
	}
	free(philos);
}
