/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:57:51 by marvin            #+#    #+#             */
/*   Updated: 2025/12/01 22:57:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_runing(t_data *data)
{
	int	r;

	pthread_mutex_lock(&data->stop_mutex);
	r = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (r);
}

void ft_set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

int ft_check_death(t_data *data)
{
	long long	now;
	int			i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&data->philosophers[i].state_mutex);
		now = ft_get_time_ms();
		if (now - data->philosophers[i].last_meal > data->time_to_die)
		{
			ft_print_status(&data->philosophers[i], "died");
			pthread_mutex_unlock(&data->philosophers[i].state_mutex);
			ft_set_stop(data);
			return (1);
		}
		pthread_mutex_unlock(&data->philosophers[i].state_mutex);
		i++;
	}
	return (0);
}

void ft_check_all_ate(t_data *data)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&data->philosophers[i].state_mutex);
		if (data->philosophers[i].finished == 1)
			done++;
		pthread_mutex_unlock(&data->philosophers[i].state_mutex);
		i++;
	}
	if (done == data->n_philos)
		ft_set_stop(data);
	return ;
}

void *ft_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!ft_runing(data))
	{
		if (ft_check_death(data))
			return (NULL);
		if (data->must_eat != -1)
			ft_check_all_ate(data);
		usleep(100);
	}
	return (NULL);
}
