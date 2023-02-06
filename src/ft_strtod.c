/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:19:20 by mtomomit          #+#    #+#             */
/*   Updated: 2023/01/31 17:54:05 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	verify_point(size_t	*i, char *nptr, double *nb)
{
	size_t	div;

	div = 0;
	if (nptr[*i] == '.' || nptr[*i] == ',')
		*i = *i + 1;
	while (nptr[*i] >= '0' && nptr[*i] <= '9')
	{
		*nb = (*nb * 10) + (nptr[*i] - 48);
		div++;
		*i = *i + 1;
	}
	while (div > 0)
	{
		*nb = *nb / 10;
		div--;
	}
}

double	verify_signal_and_space(size_t	*i, char *nptr)
{
	double	signal;

	signal = 1.0;
	while ((nptr[*i] >= 9 && nptr[*i] <= 13) || nptr[*i] == 32)
		*i = *i + 1;
	if (nptr[*i] == '-')
	{
		signal *= -1;
		*i = *i + 1;
	}
	else
	{
		if (nptr[*i] == '+')
			*i = *i + 1;
	}
	return (signal);
}

double	ft_strtod(char *nptr)
{
	size_t	i;
	double	signal;
	double	nb;

	i = 0;
	signal = verify_signal_and_space(&i, nptr);
	nb = 0.0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = (nb * 10) + (nptr[i] - 48);
		i++;
	}
	verify_point(&i, nptr, &nb);
	return (signal * nb);
}
