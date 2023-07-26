/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkaya <sakkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:31:51 by sakkaya           #+#    #+#             */
/*   Updated: 2023/07/26 03:57:21 by sakkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	freesth(t_list	*stk, t_philos	*philos)
{
	free (stk);
	free (philos->fork_mutex);
	free (philos);
}

void	*deadcheck(void *asd)
{
	int			i;
	uint64_t	time;
	t_philos	*stk;

	stk = (t_philos *)asd;
	i = 0;
	while (stk && stk->check == -1)
	{
		time = stk->link[i].last_eat;
		if (stk->time_to_die < gettime() - time)
		{
			printthreadm(stk->link[i].id, YELLOW"died\n"RESET, stk);
			stk->dead = 1;
			i = 0;
		}
		if (stk->dead == 1)
			return (NULL);
		i++;
		if (i == stk->number_of_philo)
			i = 0;
	}
	return (NULL);
}

int	eatcheck(t_list *stk)
{
	if (stk->count_eat >= stk->s_stk->must_eat && stk->s_stk->must_eat != -1)
	{
		stk->s_stk->check = 1;
		return (0);
	}
	return (1);
}

int	checkargs(char **av, int i)
{
	while (av[i])
	{
		if (i == 1 && ft_atoi(av[i]) < 1)
			return (0);
		if (ft_atoi(av[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}
