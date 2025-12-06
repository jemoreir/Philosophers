/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoreir <jemoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:01:55 by jemoreir          #+#    #+#             */
/*   Updated: 2025/12/03 17:01:55 by jemoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(long long ms, t_data *data)
{
	long long	start;

	start = ft_get_time_ms();
	while (ft_get_time_ms() - start < ms)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop == 1)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->stop_mutex);
		usleep(100);
	}
	return (1);
}

void	ft_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_one);
	ft_print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_two);
	ft_print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->state_mutex);
	philo->last_meal = ft_get_time_ms();
	pthread_mutex_unlock(&philo->state_mutex);
	ft_print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->state_mutex);
	philo->meals++;
	if (philo->data->must_eat != -1 && philo->finished == 0
		&& philo->meals >= philo->data->must_eat)
		philo->finished = 1;
	pthread_mutex_unlock(&philo->state_mutex);
	pthread_mutex_unlock(philo->fork_two);
	pthread_mutex_unlock(philo->fork_one);
}

void	ft_philo_sleep(t_philo *philo)
{
	ft_print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	ft_philo_think(t_philo *philo)
{
	ft_print_status(philo, "is thinking");
	ft_usleep(100, philo->data);
}
