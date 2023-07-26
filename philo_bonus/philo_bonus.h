/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdemirci <kdemirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 02:09:04 by kdemirci          #+#    #+#             */
/*   Updated: 2022/12/13 11:03:12 by kdemirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int				num_philo;
	int				num_fork;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				ate;
	long			start_time;
	int				is_died;
	sem_t			*print_lock;
	sem_t			*fork_lock;
	pthread_t		monitor;
	long			last_meal;
	int				*philo_id;
	int				index;
}	t_philo;

//init
t_philo	*init_philo(int ac, char **av);
//utils
void	check_args(t_philo *philo);
void	print(t_philo *philo, char *state);
long	get_time(void);
int		check_meals(t_philo *philo);
int		ft_atoi(char *str);
//dinner
void	fin_dinner(t_philo **philo);
void	*monitoring(void *ptr);
void	*start_dinner(t_philo *philo);

#endif
