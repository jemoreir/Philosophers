/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoreir <jemoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:01:14 by jemoreir          #+#    #+#             */
/*   Updated: 2025/12/03 17:01:14 by jemoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_init_data(t_data *data, int argc, char **argv)
{
	int	p;

	if (argc < 5 || argc > 6)
		return (0);
	if (!ft_safe_atoi(argv[1], &p) || p <= 0)
		return (0);
	data->n_philos = p;
	if (!ft_safe_atoi(argv[2], &p) || p <= 0)
		return (0);
	data->time_to_die = p;
	if (!ft_safe_atoi(argv[3], &p) || p <= 0)
		return (0);
	data->time_to_eat = p;
	if (!ft_safe_atoi(argv[4], &p) || p <= 0)
		return (0);
	data->time_to_sleep = p;
	if (argc == 6)
	{
		if (!ft_safe_atoi(argv[5], &p) || p <= 0)
			return (0);
		data->must_eat = p;
	}
	else
		data->must_eat = -1;
	return (1);
}
void ft_destroy_forks(t_data *data, int s)
{
	int	i;

	i = 0;
	while (i < s)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	return ;
}
int ft_init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		ft_destroy_forks(data, data->n_philos);
		return (0);
	}
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		ft_destroy_forks(data, data->n_philos);
		return (0);
	}
	if (pthread_mutex_init(&data->finished_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->stop_mutex);
		ft_destroy_forks(data, data->n_philos);
		return (0);
	}
	return (1);
}

int ft_init_inside_data(t_data *data)
{
	int	i;

	i = 0;
	data->stop = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (0);
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			ft_destroy_forks(data, i);
			return (0);
		}
		i++;
	}
	if (!ft_init_mutexes(data))
		return (0);
	return (1);
}

int ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philosophers = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philosophers)
		return (0);
	while (i < data->n_philos)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].data = data;
		data->philosophers[i].meals = 0;
		data->philosophers[i].finished = 0;
		data->philosophers[i].last_meal = data->start_time;
		if (pthread_mutex_init(&data->philosophers[i].state_mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->philosophers[i].state_mutex);
			free(data->philosophers);
			return (0);
		}
		ft_fork_atr(data, i);
		i++;
	}
	return (1);
}
