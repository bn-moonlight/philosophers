/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:31:26 by sakkaya           #+#    #+#             */
/*   Updated: 2023/07/26 02:16:30 by myagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philos(t_philos *stk, int ac) // filozofların kişiasel özelliklerini belirliyoruz.
{
	stk->link = malloc(sizeof(t_list) * stk->number_of_philo);
	if (!stk->link)
		return (0);
	while (ac < stk->number_of_philo)
	{
		stk->link[ac].id = ac;
		stk->link[ac].l_forkid = ac;
		stk->link[ac].r_forkid = (ac + 1) % stk->number_of_philo;
		stk->link[ac].count_eat = 0;
		stk->link[ac].s_stk = stk; // ??
		stk->link[ac].last_eat = gettime(); // son yemek yediğin süreyi aldık.
		ac++;
	}
	return (1);
}

int	init_arguments(int ac, char **av, t_philos *stk) // tüm filozoflar için ortak olan özellikleri belirliyoruz
{
	if (!line_25(av))
		return (0);
	stk->number_of_philo = ft_atoi(av[1]);
	stk->time_to_die = ft_atoi(av[2]);
	stk->time_to_eat = ft_atoi(av[3]);
	stk->time_to_sleep = ft_atoi(av[4]);
	stk->start_time = gettime();
	stk->check = -1;
	if (ac == 6) // opsiyonel (isteğe bağlı) argüman
		stk->must_eat = ft_atoi(av[5]);
	else
		stk->must_eat = -1;
	stk->dead = 0;
	stk->fork_mutex = malloc(sizeof(pthread_mutex_t) * stk->number_of_philo); // her bir filozof için mutex oluşturuyoruz. çatallatrımız pthread_mutex_t ve filozof sayısı kadar açtık.
	if (!stk->fork_mutex)
		return (0);
	ac = 0;
	// mutex, birden fazla iş parçacığının aynı anda çalıştığı programlardır.
	pthread_mutex_init(&stk->random, NULL); // mutexi başlatıyoruz, Null vermemizin sebebi mutexin varsayılan özelliklerini kullanmak istememiz.
											// sistemi dışarıdan gözetleyen göz gibi düşün. Her bir filozof için mutex oluşturuyoruz hemen aşıda ama
											// burada sistemi kontrol eden bi monitör oluşturduk.
	while (stk->number_of_philo > ac)
		pthread_mutex_init(&stk->fork_mutex[ac++], NULL); // her bir filozof için mutex oluşturuyoruz.
														  // yani toplam 5 tane muteximiz oldu. (eğer 4 filozofumuz varsa bir fazlası kadar mutex oldu)
	if (!init_philos(stk, 0))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_philos		*stk;
	uint64_t		time; // zamanı tutmak için kullandık.

	if (ac != 5 && ac != 6)
	{
		printf(RED"More or not enough arguments."RESET);
		return (0);
	}
	if (!checkargs(av, 1))
		return (0);
	stk = malloc(sizeof(t_philos));
	if (!init_arguments(ac, av, stk))
	{
		freesth (stk->link, stk);
		return (0);
	}
	if (!createthread(stk, 0, time))
	{
		freesth (stk->link, stk);
		return (0);
	}
	freesth (stk->link, stk);
}
