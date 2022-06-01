/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:08:17 by rmorel            #+#    #+#             */
/*   Updated: 2022/05/31 14:50:56 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<pthread.h>
# include	<sys/time.h>

# define DIE "\e[0m[%4ldms] Philo %d \e[1;31mdied\n\e[0m"
# define THINK "\e[0m[%4ldms] Philo %d \e[0;33mis thinking\n\e[0m"
# define FORK "\e[0m[%4ldms] Philo %d \e[0;32mhas taken a fork\n\e[0m"
# define SLEEP "\e[0m[%4ldms] Philo %d \e[0;34mis sleeping\n\e[0m"
# define EAT "\e[0m[%4ldms] Philo %d \e[0;35mis eating\n\e[0m"

typedef struct s_param {
	int				nb;
	int				ttd;
	int				tte;
	int				tts;
	int				end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	protect_dead;
	pthread_mutex_t	print_dead;
	int				dead;
	struct timeval	start;
}				t_param;

typedef struct s_philo {
	int				x;
	long			last_eat;
	pthread_mutex_t	protect_le;
	pthread_mutex_t	protect_nb_eat;
	int				nb_eat;
	t_param			*param;
}				t_philo;
//	check.c

int		check_args(int ac, char **av);
void	check_dead_then_print(t_philo *philo, char *str);
int		check_stop(t_philo *philo);
int		check_stop_loop(t_philo *philo, t_philo *philo_tab);
int		check_all_have_eaten(t_philo *philo);

//	lifespan.c

void	eat(t_philo *philo);
int		one_philo(t_philo *philo);
void	*one_philo_routine(void *arg);

//	main.c

int		start_philo(t_philo *philo, pthread_t *th);
void	philo_loop(t_philo *philo);
int		philo_ending(t_philo *philo, pthread_t *th);
void	*philo_routine(void	*arg);

//	parser.c

void	print_args(t_philo *philo);
t_param	*get_param(int ac, char **av);
int		get_param_2(t_param *param, int i);
t_philo	*get_philos(t_param *param);

//	utils.c

int		ft_isdigit(char c);
long	ft_atol(char *str);
int		free_all(t_philo *philo, pthread_t *th);
long	get_time(t_param *param);
int		check_no_char(int ac, char **av);

#endif
