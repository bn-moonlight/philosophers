/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:31:51 by sakkaya           #+#    #+#             */
/*   Updated: 2023/07/26 03:11:42 by myagiz           ###   ########.fr       */
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
	while (stk && stk->check == -1) // check -1 isr filozoflar yaşamaya devam eder demektir.
	{
		time = stk->link[i].last_eat; // filozofun son yemek yeme zaman.
		if (stk->time_to_die < gettime() - time) // geçen süreyi hesaplayarak filozofun ölüp ölmediğini kontrol ediyoruz.
		{
			printthreadm(stk->link[i].id, YELLOW"died\n"RESET, stk);
			stk->dead = 1;
			i = 0;
		}
		if (stk->dead == 1) // yukarıda filozofumuz öldüğünde dead değişkenini 1 yapıyoruz ve burada while döngüsünü kırıyoruz.
			return (NULL);
		i++;
		if (i == stk->number_of_philo) //  filozofları kontrol etmek için döngü başına sarılır.
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
		if (i == 1 && ft_atoi(av[i]) < 1) // 0 ve - li değerler girilmemeli
			return (0);
		if (ft_atoi(av[i]) == -1) // ??? pdf e bak bu bi kural olabilir ya da kaldır dene hata verebilir
			return (0);
		i++;
	}
	return (1);
}
