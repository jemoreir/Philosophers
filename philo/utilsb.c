/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:09:28 by marvin            #+#    #+#             */
/*   Updated: 2025/12/01 17:09:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_time_ms(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	ft_fork_atr(t_data *data, int i)
{
	int	n;

	n = data->n_philos;
	if (i % 2 == 0)
	{
		data->philosophers[i].fork_one = &data->forks[(i + 1) % n];
		data->philosophers[i].fork_two = &data->forks[i];
	}
	else
	{
		data->philosophers[i].fork_one = &data->forks[i];
		data->philosophers[i].fork_two = &data->forks[(i + 1) % n];
	}
	return ;
}
void *rt(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	ft_print_status(philo, "is thinking");
	usleep(100000);
	ft_print_status(philo, "end test");
	return (NULL);
}

int ft_start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time_ms();
	while (i < data->n_philos)
	{
		if (pthread_create(&data->philosophers[i].t, NULL, rt,
			&data->philosophers[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < data->n_philos)
		pthread_join(data->philosophers[i++].t, NULL);
	return (1);
}

void ft_print_status(t_philo *philo, char *msg)
{
	t_data		*data;
	long long	timestamp;

	data = philo->data;
	pthread_mutex_lock(&data->print_mutex);
	timestamp = ft_get_time_ms() - data->start_time;
	printf("%lld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&data->print_mutex);
	return ;
}