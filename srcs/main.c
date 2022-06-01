/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:04:54 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/01 17:30:25 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	pthread_t		*th;
	t_philo			*philo;

	if (!check_args(ac, av))
		return (2);
	philo = get_philos(get_param(ac, av));
	if (!philo)
		return (free_all(philo, NULL));
	if (philo[0].param->nb == 1)
		return (one_philo(philo));
	th = malloc(sizeof(*th) * philo[0].param->nb);
	if (!th)
		return (free_all(philo, NULL));
	if (start_philo(philo, th) != 0)
		return (free_all(philo, th));
	philo_loop(philo);
	if (philo_ending(philo, th) != 0)
		return (free_all(philo, th));
	return (free_all(philo, th));
}

int	start_philo(t_philo *philo, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < philo[0].param->nb)
	{
		if (pthread_create(&th[i], NULL, &philo_routine, &philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	philo_loop(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].param->nb)
	{
		if (check_stop_loop(&philo[i], &philo[0]) >= 1)
		{
			pthread_mutex_lock(&philo[0].param->protect_dead);
			philo[0].param->dead = 1;
			if (check_stop_loop(&philo[i], &philo[0]) == 1)
				printf(DIE, get_time(philo[0].param), philo[i].x);
			usleep(1000);
			pthread_mutex_unlock(&philo[0].param->protect_dead);
			break ;
		}
		usleep(500);
		i++;
		if (i >= philo[0].param->nb)
			i = 0;
	}
	return ;
}

int	philo_ending(t_philo *philo, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < philo[0].param->nb)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	*philo_routine(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->x % 2))
		usleep(1000 * philo->param->tte);
	pthread_mutex_lock(&philo->protect_le);
	philo->last_eat = get_time(philo->param);
	pthread_mutex_unlock(&philo->protect_le);
	while (1)
	{
		if (check_stop(philo))
			break ;
		eat(philo);
		check_dead_then_print(philo, SLEEP);
		usleep(philo->param->tts * 1000);
		check_dead_then_print(philo, THINK);
	}
	return (NULL);
}
