/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 22:44:04 by asyvash           #+#    #+#             */
/*   Updated: 2024/05/12 18:54:00 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_data
{
	int			number_of_philo;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	start_time;
	int			meals_quantity;
}	t_data;

typedef struct s_philo
{
	int				num;
	long long		to_die;
	long long		to_eat;
	int				meals;
	t_data			*data;
	struct s_root	*root;
	bool			meals_finish;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
}	t_philo;

typedef struct s_root
{
	int				quantity;
	int				ate_enough;
	t_philo			*philos;
	pthread_t		*threads;
	pthread_mutex_t	printing;
	pthread_mutex_t	stop_simulation;
	bool			stop_sim;
}	t_root;

void		routine(t_root *philo_r);
int			monitoring(t_philo *philo);

/* ACTIONS */
void		is_eating(t_philo *philo);
void		is_sleeping(t_philo *philo);
void		is_thinking(t_philo *philo);
void		died(t_philo *philo);

/* TIME */
long long	get_time(void);
void		ft_usleep(long long waiting_time);

/* UTILS */
void		print_msg(t_philo *philo, char *msg);
int			check_input(char **argv, int argc);
int			ft_ato_i_ll(const char *nptr, bool int_val);
void		ft_putstr_fd(char *s, int fd);

#endif