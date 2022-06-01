/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifespan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:35:24 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/01 17:27:54 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->forks[(philo->x) % philo->param->nb]);
	check_dead_then_print(philo, FORK);
	pthread_mutex_lock(&philo->param->forks[(philo->x - 1)]);
	check_dead_then_print(philo, FORK);
	pthread_mutex_lock(&philo->protect_le);
	philo->last_eat = get_time(philo->param);
	pthread_mutex_unlock(&philo->protect_le);
	check_dead_then_print(philo, EAT);
	pthread_mutex_lock(&philo->protect_nb_eat);
	if (philo->param->end >= 0 && philo->nb_eat < philo->param->end)
		philo->nb_eat++;
	pthread_mutex_unlock(&philo->protect_nb_eat);
	usleep(philo->param->tte * 1000);
	pthread_mutex_unlock(&philo->param->forks[(philo->x - 1)]);
	pthread_mutex_unlock(&philo->param->forks[(philo->x) % philo->param->nb]);
}

int	one_philo(t_philo *philo)
{
	pthread_t		*th;

	th = malloc(sizeof(*th));
	if (!th)
		return (1);
	if (pthread_create(th, NULL, &one_philo_routine, philo) != 0)
		return (1);
	if (pthread_join(*th, NULL) != 0)
		return (1);
	return (free_all(philo, th));
}

void	*one_philo_routine(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	philo.last_eat = get_time(philo.param);
	pthread_mutex_lock(&philo.param->forks[(philo.x - 1)]);
	printf(FORK, get_time(philo.param), philo.x);
	while (1)
	{
		if (get_time(philo.param) - philo.last_eat > philo.param->ttd)
		{
			pthread_mutex_lock(&philo.param->protect_dead);
			philo.param->dead = 1;
			printf(DIE, get_time(philo.param), philo.x);
			pthread_mutex_unlock(&philo.param->protect_dead);
			pthread_mutex_unlock(&philo.param->forks[(philo.x - 1)]);
			break ;
		}
	}
	return (NULL);
}
