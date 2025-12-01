/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:06:10 by marvin            #+#    #+#             */
/*   Updated: 2025/11/24 16:06:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strlen(char *c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

int	ft_str_is_digit(char *c)
{
	int	i;

	i = 0;
	if (!c[i])
		return (0);
	while (c[i])
	{
		if (c[i] >= '0' && c[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_int_max(char *str)
{
	char	*max;
	int		i;

	max = "2147483647";
	i = 0;
	while (str[i] && max[i])
	{
		if (str[i] > max[i])
			return (1);
		else if (str[i] < max[i])
			return (0);
		i++;
	}
	return (0);
}

int	ft_safe_atoi(char *str, int *nbr)
{
	int		len;
	int		i;
	long	result;

	if (!ft_str_is_digit(str))
		return (0);
	len = ft_strlen(str);
	if (len > 10)
		return (0);
	if (len == 10 && ft_int_max(str))
		return (0);
	i = 0;
	result = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	*nbr = (int)result;
	return (1);
}

void ft_destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->philosophers[i].state_mutex);
		i++;
	}
	ft_destroy_forks(data, data->n_philos);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->finished_mutex);
	free(data->philosophers);
	return ;
}
