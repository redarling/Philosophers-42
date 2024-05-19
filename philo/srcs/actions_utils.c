/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:16:31 by asyvash           #+#    #+#             */
/*   Updated: 2024/05/19 15:16:32 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *philo, long long time_to_check)
{
	if (get_time() + time_to_check > philo->to_die)
	{
		died(philo);
		return (0);
	}
	return (1);
}

void	handle_meals(t_philo *philo)
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
