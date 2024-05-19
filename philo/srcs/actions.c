/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:18:30 by asyvash           #+#    #+#             */
/*   Updated: 2024/05/12 17:44:23 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	handle_meals(t_philo *philo)
{
	philo->meals += 1;
	if (philo->data->meals_quantity != -1 && \
		philo->meals == philo->data->meals_quantity)
	{
		pthread_mutex_lock(&philo->root->stop_simulation);
		philo->root->ate_enough--;
		pthread_mutex_unlock(&philo->root->stop_simulation);
		pthread_mutex_lock(&philo->root->stop_simulation);
		if (philo->root->ate_enough == 0)
		{
			pthread_mutex_unlock(&philo->root->stop_simulation);
			pthread_mutex_lock(&philo->root->stop_simulation);
			philo->root->stop_sim = true;
		}
		pthread_mutex_unlock(&philo->root->stop_simulation);
	}
}

void	is_eating(t_philo *philo)
{
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	philo->to_die = get_time() + \
		philo->data->time_to_die + philo->data->time_to_eat;
	ft_usleep(get_time() + philo->data->time_to_eat);
	if (philo->data->meals_quantity != -1)
		handle_meals(philo);
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
}

void	is_sleeping(t_philo *philo)
{
	if (monitoring(philo) == 0)
		return ;
	print_msg(philo, "is sleeping");
	ft_usleep(get_time() + philo->data->time_to_sleep);
}

void	is_thinking(t_philo *philo)
{
	if (monitoring(philo) == 0)
		return ;
	print_msg(philo, "is thinking");
}

void	died(t_philo *philo)
{
	if (monitoring(philo) == 0)
		return ;
	ft_usleep(philo->to_die);
	print_msg(philo, "died");
}
