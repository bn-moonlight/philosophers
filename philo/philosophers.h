/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkaya <sakkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 02:07:37 by kdemirci          #+#    #+#             */
/*   Updated: 2022/12/14 12:16:00 by sakkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define BLUE    "\x1b[34m"
# define CYAN    "\x1b[36m"
# define PINK    "\x1B[35m"
# define BLACK   "\x1B[30m"
# define YELLOW  "\x1B[33m"
# define RESET   "\x1b[0m"

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct addion
{
	int				id;
	int				l_forkid;
	int				r_forkid;
	int				count_eat;
	uint64_t		last_eat;
	pthread_t		th_id;
	struct p_stk	*s_stk;
}	t_list;

typedef struct p_stk
{
	int					id;
	int					must_eat;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_philo;
	int					dead;
	int					check;
	t_list				*link;
	uint64_t			start_time;
	pthread_mutex_t		random;
	pthread_mutex_t		*fork_mutex;
}	t_philos;

int			ft_atoi(char *s);
int			line_25(char **av);
int			eatcheck(t_list *stk);
int			checkargs(char **av, int i);
void		*deadcheck(void *asd);
int			createthread(t_philos *stk, int i, uint64_t time);

uint64_t	gettime(void);

void		passtime(int time, t_list *stk);
void		freesth(t_list *stk, t_philos *philos);
void		printthreadm(int id, char *s, t_philos *stk);

#endif