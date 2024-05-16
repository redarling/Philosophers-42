/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 22:43:44 by asyvash           #+#    #+#             */
/*   Updated: 2024/05/16 11:40:47 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_all(t_root *root)
{
	int	i;

	i = 0;
	while (i < root->quantity)
	{
		pthread_mutex_destroy(&root->philos[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&root->printing);
	pthread_mutex_destroy(&root->stop_simulation);
	free(root->philos);
	free(root->threads);
}

static void	fill_philos(t_philo *philos, t_data *data, int i)
{
	philos[i].num = i;
	philos[i].meals = 0;
	philos[i].data = data;
	philos[i].meals_finish = false;
	pthread_mutex_init(&philos[i].left_fork, NULL);
	if (i + 1 == data->number_of_philo)
		philos[i].right_fork = &(philos[0]).left_fork;
	else
		philos[i].right_fork = &(philos[i + 1]).left_fork;
	philos[i].first_fork = &philos[i].left_fork;
	philos[i].second_fork = philos[i].right_fork;
	if (i % 2)
	{
		philos[i].first_fork = philos[i].right_fork;
		philos[i].second_fork = &philos[i].left_fork;
	}
}

static int	init_philos(t_root *root, t_data *data)
{
	int	i;

	root->philos = malloc(sizeof(t_philo) * data->number_of_philo);
	root->threads = malloc(sizeof(pthread_t) * data->number_of_philo);
	root->quantity = data->number_of_philo;
	root->stop_sim = false;
	if (data->meals_quantity == -1)
		root->ate_enough = -1;
	else
		root->ate_enough = data->number_of_philo;
	pthread_mutex_init(&root->printing, NULL);
	pthread_mutex_init(&root->stop_simulation, NULL);
	if (!root->philos || !root->threads)
	{
		free_all(root);
		return (1);
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		root->philos[i].root = root;
		fill_philos(root->philos, data, i);
		i++;
	}
	return (0);
}

static void	init_data(char **argv, t_data *data)
{
	data->number_of_philo = ft_ato_i_ll(argv[1], true);
	data->time_to_die = ft_ato_i_ll(argv[2], false);
	data->time_to_eat = ft_ato_i_ll(argv[3], false);
	data->time_to_sleep = ft_ato_i_ll(argv[4], false);
	if (argv[5])
		data->meals_quantity = ft_ato_i_ll(argv[5], true);
	else
		data->meals_quantity = -1;
	data->start_time = get_time();
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_root	root;

	if (check_input(argv, argc) == 1)
		return (1);
	init_data(argv, &data);
	if (data.number_of_philo == 1)
	{
		printf("%lld %d has taken a fork\n", get_time() - \
			data.start_time, 1);
		ft_usleep(data.start_time + data.time_to_die);
		printf("%lld %d died\n", get_time() - data.start_time, 1);
		return (0);
	}
	if (init_philos(&root, &data) == 1)
	{
		ft_putstr_fd("Allocation error\n", 2);
		return (1);
	}
	create_and_join_threads(&root);
	free_all(&root);
	return (0);
}
