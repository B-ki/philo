/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:12:14 by rmorel            #+#    #+#             */
/*   Updated: 2022/05/31 14:52:03 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_args(t_philo *philo)
{
	printf("Nb philo = %d - ttd = %d - tte = %d - tts = %d - end = %d\n",
		philo->param->nb, philo->param->ttd, philo->param->tte,
		philo->param->tts, philo->param->end);
	return ;
}

t_param	*get_param(int ac, char **av)
{
	t_param	*param;
	int		i;

	param = malloc(sizeof(*param));
	if (!param)
		return (NULL);
	i = 0;
	param->nb = ft_atol(av[1]);
	param->ttd = ft_atol(av[2]);
	param->tte = ft_atol(av[3]);
	param->tts = ft_atol(av[4]);
	if (ac == 6)
		param->end = ft_atol(av[5]);
	else
		param->end = -1;
	param->forks = malloc(sizeof(pthread_mutex_t) * param->nb);
	if (!param->forks)
		return (NULL);
	if (get_param_2(param, i) != 0)
		return (NULL);
	return (param);
}

int	get_param_2(t_param *param, int i)
{
	while (i < param->nb)
	{
		pthread_mutex_init(&param->forks[i], NULL);
		i++;
	}
	if (pthread_mutex_init(&param->protect_dead, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&param->print_dead, NULL) != 0)
		return (-1);
	param->dead = 0;
	gettimeofday(&param->start, NULL);
	return (0);
}

t_philo	*get_philos(t_param *param)
{
	t_philo	*philo;
	int		i;

	if (!param)
		return (NULL);
	philo = malloc(sizeof(t_philo) * param->nb);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < param->nb)
	{
		philo[i].x = i + 1;
		philo[i].last_eat = 0;
		philo[i].nb_eat = 0;
		philo[i].param = param;
		if (pthread_mutex_init(&philo[i].protect_le, NULL) != 0)
			return (NULL);
		if (pthread_mutex_init(&philo[i].protect_nb_eat, NULL))
			return (NULL);
		i++;
	}
	return (philo);
}
