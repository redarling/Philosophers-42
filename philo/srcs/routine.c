/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:22:55 by asyvash           #+#    #+#             */
/*   Updated: 2024/05/16 11:57:32 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_death(t_philo *philo)
{
	if (get_time() + philo->data->time_to_eat > philo->to_die)
	{
		pthread_mutex_unlock(philo->first_fork);
		died(philo);
		return (0);
	}
	return (1);
}

static int	actions(t_philo *philo)
{
	if (monitoring(philo) == 0)
		return (0);
	pthread_mutex_lock(philo->first_fork);
	if (get_time() + philo->data->time_to_eat <= philo->to_die)
		is_eating(philo);
	if (check_death(philo) == 0)
		return (0);
	if (monitoring(philo) == 0)
		return (0);
	if (check_death(philo) == 0)
		return (0);
	is_sleeping(philo);
	if (check_death(philo) == 0)
		return (0);
	if (monitoring(philo) == 0)
		return (0);
	if (check_death(philo) == 0)
		return (0);
	is_thinking(philo);
	if (check_death(philo) == 0)
		return (0);
	return (1);
}

int	monitoring(t_philo *philo)
{
	pthread_mutex_lock(&philo->root->stop_simulation);
	if (philo->root->stop_sim == true)
	{
		pthread_mutex_unlock(&philo->root->stop_simulation);
		return (0);
	}
	pthread_mutex_unlock(&philo->root->stop_simulation);
	return (1);
}

static void	*philo_routine(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	philo->to_die = philo->data->start_time + \
		philo->data->time_to_die;
	if (philo->num % 2 == 0)
		ft_usleep(get_time() + philo->data->time_to_eat);
	while (1)
	{
		if (actions(philo) == 0)
			return (NULL);
	}
	return (NULL);
}

void	create_and_join_threads(t_root *root)
{
	int	i;

	i = 0;
	while (i < root->quantity)
	{
		pthread_create(&root->threads[i], NULL, philo_routine,
			(void *)&root->philos[i]);
		i++;
	}
	i = 0;
	while (i < root->quantity)
	{
		pthread_join(root->threads[i], NULL);
		i++;
	}
}
