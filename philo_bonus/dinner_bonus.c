/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdemirci <kdemirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 02:08:53 by kdemirci          #+#    #+#             */
/*   Updated: 2022/12/13 12:57:36 by kdemirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	passtime(uint64_t time, t_philo *stk)
{
	uint64_t	start;

	start = get_time();
	while (stk->is_died == 0)
	{
		if (get_time() - start >= time)
			break ;
		usleep(32);
	}
}

void	fin_dinner(t_philo **philo)
{
	t_philo	*tmp;
	int		i;
	int		status;

	tmp = *philo;
	i = -1;
	while (++i < tmp->num_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			while (i < tmp->num_philo)
			{
				kill(tmp->philo_id[i], SIGKILL);
				i++;
			}
		}
	}
	sem_close(tmp->print_lock);
	sem_close(tmp->fork_lock);
	sem_unlink("/print_lock");
	sem_unlink("/fork_lock");
	free(tmp->philo_id);
	free(tmp);
}

void	*monitoring(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (!(check_meals(philo)))
	{
		if (get_time() - philo->last_meal > philo->t_die)
		{
			print(philo, "died");
			philo->is_died = 1;
			exit(-1);
		}
		passtime(2, philo);
	}
	exit(0);
}

void	*start_dinner(t_philo *philo)
{
	if (philo->index % 2 == 1)
		passtime(2, philo);
	pthread_create(&philo->monitor, NULL, monitoring, philo);
	while (!philo->is_died)
	{
		print(philo, "is thinking");
		sem_wait(philo->fork_lock);
		print(philo, "has taken a fork");
		sem_wait(philo->fork_lock);
		print(philo, "has taken a fork");
		print(philo, "is eating");
		passtime(philo->t_eat, philo);
		philo->last_meal = get_time();
		sem_post(philo->fork_lock);
		sem_post(philo->fork_lock);
		philo->ate++;
		print(philo, "is sleeping");
		passtime(philo->t_sleep, philo);
	}
	pthread_join(philo->monitor, NULL);
	pthread_detach(philo->monitor);
	exit(0);
}
