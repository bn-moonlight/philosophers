/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:32:05 by sakkaya           #+#    #+#             */
/*   Updated: 2023/07/26 03:17:50 by myagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	starteating(t_list *free)
{
	pthread_mutex_lock(&free->s_stk->fork_mutex[free->l_forkid]); // filozof sol çatalı aldığında mutex kilitlenir.
	printthreadm(free->id, BLUE"has taken the left fork\n"RESET, free->s_stk);
	pthread_mutex_lock(&free->s_stk->fork_mutex[free->r_forkid]);// filozof sağ çatalı aldığında mutex kilitlenir.
	printthreadm(free->id, BLUE"has taken the right fork\n"RESET, free->s_stk);
	printthreadm(free->id, PINK"is eating\n"RESET, free->s_stk);
	free->last_eat = gettime(); // filozof yemek yediği zamanı kaydeder.
	passtime(free->s_stk->time_to_eat, free);
	pthread_mutex_unlock(&free->s_stk->fork_mutex[free->l_forkid]); // çatalları tek tek bırakıyor yani mutexleri açıyor ve
	pthread_mutex_unlock(&free->s_stk->fork_mutex[free->r_forkid]); // sistem o kadar çok hızlı ki hemen diğer filazof çatalı alıyor.
	free->count_eat++ ;
}

void	*start(void *stk) // sıra sıra tüm filozofları çalıştırıyoruz.
{
	t_list	*free;

	free = (t_list *)stk;
	free->last_eat = gettime();
	if (free->id % 2) // filozofların sırasıyla çalışmasını sağlıyoruz. 2,4,6,8 şeklinde ilk olarak çift sayılı orgümana sahip filozoflar çalışıyor.
		usleep(1000); // usleep ile 1000 mikrosaniye bekletiyoruz, tek sayılı argümanları.

	while (free->s_stk->dead == 0) // bruada filozofların ölüp ölmediğini kontrol ediyoruz. aynı zamanda
									// pthread_create(&id, NULL, &deadcheck, stk); ile oluşturduğumuz iş parçacığını kontrol ediyoruz.
									// eğer ölüm olursa burası çalışmayacak. ve pthread_create(&id, NULL, &deadcheck, stk); ile tespit edilecek
	{								// çünkü aynı anda çalışıyorlar
		starteating(free); // burada çatalları kitleme oldu ve yemek yeme süresi geçti.
		if (!eatcheck(free)) // filozoflar belirlediğimiz kadardan fazla yemek yediğinde sistem durur.
			break ;
		if (free->s_stk->dead == 1)
			break ;
		printthreadm(free->id, RED"is sleeping\n"RESET, free->s_stk);
		passtime(free->s_stk->time_to_sleep, free); // filozoflar uyuyor, uyku süresi kadar bekliyor.
		printthreadm(free->id, CYAN"is thinking\n"RESET, free->s_stk);
	}
	return (NULL);
}

int	createthread(t_philos *stk, int i, uint64_t time)
{
	pthread_t	id;

	while (i < stk->number_of_philo)
	{
		pthread_create(&stk->link[i].th_id, NULL, &start, &stk->link[i]); //  iş parçacığı oluşturuğ başlatıyoruz her filozof için.
																			// &stk->link[i].th_id    ->  iş parçacığı id'si
																			// NULL                    ->  iş parçacığı standart özellikleri
																			// &start                  ->  iş parçacığının gideceği fonksiyon
																			// &stk->link[i]           ->  iş parçacığının gideceği fonksiyonun parametresi (start fonksiynunun parametresi)

																			// start burada sürekli olarak çalışırken aynı zamanda aşağıda ölğm durumlarını da kontrol ediyoruz. deadcheck'de


		i++;
	}
	pthread_create(&id, NULL, &deadcheck, stk); // deadcheck fonksiyonu, ölüm kontrolünü sürekli olarka yapar.
	i = -1;
	while (++i < stk->number_of_philo)
	{
		pthread_join(stk->link[i].th_id, NULL); // iş parçacıklarının bitmesini bekliyoruz. yani tüm filozofların ölmesini bekliyoruz.
		pthread_detach(stk->link[i].th_id); //  iş parçacıkları bittikten sonra iş parçacıklarını temizliyoruz. freeliyoruz.
											// burada tüm filozofları topladık, sonlandırdık. ve iş parçacıklarını temizledik.
	}
	pthread_join(id, NULL); // burada da deadcheck iş parçacığının bitmesini bekliyoruz.
	pthread_detach(id);		// aynısını deadcheck için de yapıyoruz.
	while (i < stk->number_of_philo)
		pthread_mutex_destroy(&stk->fork_mutex[--i]); // filozoflaırn mutexlerini temizliyoruz.
	pthread_mutex_destroy(&stk->random); //randomun mutexini temizliyoruz. (5. mutexten bahsetmiştik onu temizliyoruz.)
	return (0);
}
