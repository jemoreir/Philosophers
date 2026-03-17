/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoreir <jemoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:01:47 by jemoreir          #+#    #+#             */
/*   Updated: 2025/12/03 17:01:47 by jemoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_runing(t_data *data)
{
	int	r;

	pthread_mutex_lock(&data->stop_mutex);
	r = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (r);
}

void	ft_set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

int	ft_check_death(t_data *data)
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
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d %s\n", (ft_get_time_ms() - data->start_time),
				data->philosophers[i].id, "died");
			ft_set_stop(data);
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_unlock(&data->philosophers[i].state_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->philosophers[i].state_mutex);
		i++;
	}
	return (0);
}

int	ft_check_all_ate(t_data *data)
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
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("End Simulation.\n");
		ft_set_stop(data);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!ft_runing(data))
	{
		if (ft_check_death(data))
			return (NULL);
		if (data->must_eat != -1 && ft_check_all_ate(data))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
