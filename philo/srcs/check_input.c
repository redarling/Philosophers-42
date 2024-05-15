/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:09:39 by asyvash           #+#    #+#             */
/*   Updated: 2024/05/11 10:22:10 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	bad_quantity_error(void)
{
	ft_putstr_fd("\nUsage: \n", 2);
	ft_putstr_fd("./philo number_of_philosophers ", 2);
	ft_putstr_fd("time_to_die\ntime_", 2);
	ft_putstr_fd("to_eat time_to_sleep \n", 2);
	ft_putstr_fd("[number_of_times_each_", 2);
	ft_putstr_fd("philosopher_must_eat]\n\n", 2);
}

static int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static int	check_long_long(const char *str)
{
	int			i;
	long		is_neg;
	long long	res;

	if (!str)
		return (-1);
	i = 0;
	is_neg = 1;
	if (ft_strlen(str) > 20)
		return (-1);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (-1);
	if (is_neg == -1 || str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	res *= is_neg;
	if ((is_neg == -1 && res >= 0) || (is_neg == 1 && res < 0))
		return (-1);
	return (1);
}

static int	check_nums(char **argv, int i)
{
	int	num;

	if (ft_ato_i_ll(argv[1], true) < 1)
		return (1);
	while (i < 5)
	{
		num = check_long_long(argv[i]);
		if (num < 1)
			return (1);
		i++;
	}
	if (argv[5] && (ft_ato_i_ll(argv[5], true) < 1))
		return (1);
	return (0);
}

int	check_input(char **argv, int argc)
{
	if (argc < 5 || argc > 6)
	{
		bad_quantity_error();
		return (1);
	}
	if ((check_nums(argv, 2)) == 1)
	{
		ft_putstr_fd("Bad input\n", 2);
		return (1);
	}
	return (0);
}
