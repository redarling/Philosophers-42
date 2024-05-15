/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:57:19 by asyvash           #+#    #+#             */
/*   Updated: 2024/05/12 18:53:16 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->root->printing);
	if (monitoring(philo) == 0)
	{
		pthread_mutex_unlock(&philo->root->printing);
		return ;
	}
	if (msg[0] && msg[0] == 'd')
	{
		printf("%lld %d %s\n", get_time() - \
			philo->data->start_time, philo->num + 1, msg);
		pthread_mutex_lock(&philo->root->stop_simulation);
		philo->root->stop_sim = true;
		pthread_mutex_unlock(&philo->root->stop_simulation);
	}
	if (monitoring(philo) == 0)
	{
		pthread_mutex_unlock(&philo->root->printing);
		return ;
	}
	printf("%lld %d %s\n", get_time() - \
	philo->data->start_time, philo->num + 1, msg);
	pthread_mutex_unlock(&philo->root->printing);
}

int	ft_ato_i_ll(const char *nptr, bool int_val)
{
	int			i;
	long long	res;
	long long	sign;

	res = 0;
	i = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res *= 10;
		res += nptr[i] - '0';
		i++;
	}
	if ((res * sign < INT_MIN || res * sign > INT_MAX) && \
		int_val == true)
		return (-1);
	if (int_val == true)
		return ((int)(res * sign));
	return ((long long)(res * sign));
}

long long	get_time(void)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL))
		return (-1);
	return (((long long)tp.tv_sec * 1000) + ((long long)tp.tv_usec / 1000));
}

void	ft_usleep(long long waiting_time)
{
	long long	time;

	time = get_time();
	while (waiting_time - time > 1)
	{
		usleep(1000 * (waiting_time - time - 1));
		time = get_time();
	}
	while (waiting_time > time)
		time = get_time();
}
