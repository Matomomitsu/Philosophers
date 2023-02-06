/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:43:52 by mtomomit          #+#    #+#             */
/*   Updated: 2023/02/06 03:50:24 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_msleep(long long ms)
{
	long long	start;

	start = ft_mstime();
	while (ms >= ft_mstime() - start)
		usleep(100);
	return (0);
}

long long	ft_mstime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

void	print_dead(t_philo *philo, long long time)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%-5lli %li died\n", time, philo->philo_number);
	pthread_mutex_unlock(&(philo->data->print));
}

int	print_action(t_philo *philo, long long time, char *action)
{
	if (!checker(philo))
		return (0);
	pthread_mutex_lock(&(philo->data->print));
	printf("%-5lli %li %s\n", time, philo->philo_number, action);
	pthread_mutex_unlock(&(philo->data->print));
	return (1);
}
