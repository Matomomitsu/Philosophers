/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:45:46 by mtomomit          #+#    #+#             */
/*   Updated: 2023/02/02 16:22:52 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_input	*verify_input(char **argv, int argc)
{
	t_input	*input;

	if (argc < 5 || argc > 6)
	{
		if (argc < 5)
			write(STDERR_FILENO, "Less arguments than expected\n\0", 31);
		if (argc > 6)
			write(STDERR_FILENO, "More arguments than expected\n\0", 31);
		exit(1);
	}
	input = (t_input *)malloc(sizeof(t_input) * 1);
	input->number_of_philo = ft_atouli(argv[1]);
	input->time_to_die = ft_strtod(argv[2]);
	input->time_to_eat = ft_strtod(argv[3]);
	input->time_to_sleep = ft_strtod(argv[4]);
	if (argc == 6)
		input->number_of_meals = ft_atouli(argv[5]);
	else
		input->number_of_meals = 0;
	return (input);
}

void	init_pthreads(t_philo *philos, t_input *input)
{
	size_t		i;
	long long	start_time;

	i = 0;
	start_time = ft_mstime();
	philos[i].data->start_time = start_time;
	while (i < input->number_of_philo)
	{
		philos[i].last_meal = start_time;
		pthread_create(&philos[i].philo, NULL, &routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < input->number_of_philo)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
}

void	input_error(t_input *input, int argc)
{
	if ((argc == 6 && input->number_of_meals == 0) || \
		input->number_of_philo == 0)
	{
		write(STDERR_FILENO, "Wrong value in input\n\0", 22);
		free(input);
		exit(1);
	}
	if (input->time_to_die == 0.0 || input->time_to_eat == 0.0 || \
		input->time_to_sleep == 0.0)
	{
		write(STDERR_FILENO, "Wrong value in input\n\0", 22);
		free(input);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_input			*input;
	t_philo			*philos;
	t_fork			*forks;

	input = verify_input(argv, argc);
	input_error(input, argc);
	forks = init_forks(input);
	philos = init_philo(input, forks);
	if (input->number_of_philo >= 2)
		init_pthreads(philos, input);
	else
	{
		philos->data->start_time = ft_mstime();
		printf("%-5lli %li has taken a fork\n", ft_mstime() - \
			philos->data->start_time, philos->philo_number);
		ft_msleep(input->time_to_die);
		printf("%-5lli %li died\n", ft_mstime() - \
			philos->data->start_time, philos->philo_number);
	}
	sanitize_philos(philos, input->number_of_philo);
	free(forks);
	free(input);
}
