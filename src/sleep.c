/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:51:07 by mtomomit          #+#    #+#             */
/*   Updated: 2023/02/06 01:59:27 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_sleep(t_philo *philo)
{
	if (print_action(philo, ft_mstime() - philo->data->start_time,
			"is sleeping"))
	{
		if (philo->data->input->time_to_sleep > \
			philo->data->input->time_to_die)
			ft_msleep(philo->data->input->time_to_die);
		else
			ft_msleep(philo->data->input->time_to_sleep);
	}
}
