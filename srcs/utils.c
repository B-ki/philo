/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:47:21 by rmorel            #+#    #+#             */
/*   Updated: 2022/05/31 14:46:31 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long	ft_atol(char *str)
{
	int		i;
	long	n;
	long	c_minus;

	i = 0;
	n = 0;
	c_minus = 1;
	while (str[i] && ((str[i] <= 9 && str[i] >= 13) || str[i] == 32))
		i++;
	if (str[i] == '-')
	{
		c_minus *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		n = n * 10 + str[i] - 48;
		i++;
	}
	return (n * c_minus);
}

int	free_all(t_philo *philo, pthread_t *th)
{
	int	i;

	i = 0;
	if (philo)
	{
		while (i < philo[0].param->nb)
		{
			pthread_mutex_destroy(&philo[0].param->forks[i]);
			i++;
		}
		pthread_mutex_destroy(&philo[0].param->protect_dead);
		pthread_mutex_destroy(&philo[0].param->print_dead);
		free(philo[0].param->forks);
		free(philo[0].param);
		free(philo);
	}
	if (th)
		free(th);
	return (0);
}

long	get_time(t_param *param)
{
	struct timeval	tv;
	long			ms;
	long			ms_init;

	gettimeofday(&tv, NULL);
	ms_init = param->start.tv_sec * 1000;
	ms_init += param->start.tv_usec / 1000;
	ms = tv.tv_sec * 1000;
	ms += tv.tv_usec / 1000;
	ms -= ms_init;
	return (ms);
}

int	check_no_char(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (j < ac)
	{
		while (av[j][i])
		{
			if (av[j][i] < '0' || av[j][i] > '9')
				return (1);
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}
