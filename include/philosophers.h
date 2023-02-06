/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:49:38 by mtomomit          #+#    #+#             */
/*   Updated: 2023/02/03 10:46:01 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_input
{
	size_t	number_of_philo;
	double	time_to_eat;
	double	time_to_die;
	double	time_to_sleep;
	size_t	number_of_meals;
}	t_input;

typedef struct s_fork
{
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_data
{
	t_input			*input;
	long long		start_time;
	int				philo_died;
	size_t			all_ate;
	pthread_mutex_t	finish_eat;
	pthread_mutex_t	died;
	pthread_mutex_t	print;
}	t_data;

typedef struct s_philo
{
	size_t		philo_number;
	t_data		*data;
	size_t		eat_times;
	long long	last_meal;
	t_fork		*l_fork;
	t_fork		*r_fork;
	pthread_t	philo;
}	t_philo;

size_t		ft_atouli(const char *nptr);

double		ft_strtod(char *time);

int			ft_msleep(long long ms);

long long	ft_mstime(void);

t_fork		*init_forks(t_input *input);

t_philo		*init_philo(t_input *input, t_fork *forks);

void		*routine(void *philo);

int			print_action(t_philo *philo, long long time, char *action);

void		print_dead(t_philo *philo, long long time);

void		philo_think(t_philo *philo);

void		taking_forks(t_philo *philo);

void		philo_sleep(t_philo *philo);

void		philo_eat(t_philo *philo);

int			checker(t_philo *philo);

void		sanitize_philos(t_philo *philos, size_t number_of_philo);

#endif
