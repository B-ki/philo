/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:12:14 by rmorel            #+#    #+#             */
/*   Updated: 2022/05/31 14:52:13 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (0);
	if (check_no_char(ac, av))
		return (0);
	while (i < ac)
	{
		if (ft_atol(av[i]) < 0 || ft_atol(av[i]) > 2147483647)
			return (0);
		i++;
	}
	if (ft_atol(av[1]) <= 0 || ft_atol(av[1]) > 200)
		return (0);
	if (ft_atol(av[2]) < 6 || ft_atol(av[3]) < 6 || ft_atol(av[4]) < 6)
		return (0);
	return (1);
}

void	check_dead_then_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->param->protect_dead);
	if (!philo->param->dead)
		printf(str, get_time(philo->param), philo->x);
	pthread_mutex_unlock(&philo->param->protect_dead);
}

int	check_stop(t_philo *philo)
{
	int	answer;

	pthread_mutex_lock(&philo->param->protect_dead);
	answer = philo->param->dead;
	pthread_mutex_unlock(&philo->param->protect_dead);
	pthread_mutex_lock(&philo->protect_nb_eat);
	if (philo->param->end >= 0 && philo->nb_eat == philo->param->end)
		answer = 1;
	pthread_mutex_unlock(&philo->protect_nb_eat);
	return (answer);
}

int	check_stop_loop(t_philo *philo, t_philo *philo_tab)
{
	int	answer;

	answer = 0;
	pthread_mutex_lock(&philo->protect_le);
	if ((get_time(philo->param) - philo->last_eat) > philo->param->ttd)
		answer = 1;
	pthread_mutex_unlock(&philo->protect_le);
	if (check_all_have_eaten(philo_tab))
		answer = 2;
	return (answer);
}

int	check_all_have_eaten(t_philo *philo)
{
	int	i;
	int	end;

	i = 0;
	end = philo[0].param->end;
	while (i < philo[0].param->nb)
	{
		pthread_mutex_lock(&philo[i].protect_nb_eat);
		if (philo[i].nb_eat < end || end < 0)
		{
			pthread_mutex_unlock(&philo[i].protect_nb_eat);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].protect_nb_eat);
		i++;
	}
	return (1);
}	
