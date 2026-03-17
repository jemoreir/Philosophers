/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoreir <jemoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:02:22 by jemoreir          #+#    #+#             */
/*   Updated: 2025/12/03 17:02:22 by jemoreir         ###   ########.fr       */
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

void	*rt(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->n_philos == 1)
	{
		pthread_mutex_lock(philo->fork_one);
		ft_print_status(philo, "has taken a fork");
		while (!ft_runing(philo->data))
			usleep(10000);
		pthread_mutex_unlock(philo->fork_one);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(10000);
	while (!ft_runing(philo->data))
	{
		ft_philo_eat(philo);
		if (!ft_runing(philo->data))
			ft_philo_sleep(philo);
		if (!ft_runing(philo->data))
			ft_philo_think(philo);
	}
	return (NULL);
}

int	ft_start_simulation(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_create(&data->philosophers[i].t, NULL, rt,
				&data->philosophers[i]) != 0)
		{
			ft_set_stop(data);
			ft_join_philos(data, i);
			return (0);
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, ft_monitor, data) != 0)
	{
		ft_set_stop(data);
		ft_join_philos(data, data->n_philos);
		return (0);
	}
	ft_join_philos(data, data->n_philos);
	pthread_join(monitor, NULL);
	return (1);
}

void	ft_print_status(t_philo *philo, char *msg)
{
	t_data		*data;
	long long	timestamp;

	data = philo->data;
	pthread_mutex_lock(&data->print_mutex);
	timestamp = ft_get_time_ms() - data->start_time;
	if (data->stop == 0)
		printf("%lld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&data->print_mutex);
	return ;
}
