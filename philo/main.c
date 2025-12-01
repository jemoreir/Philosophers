/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:39:54 by marvin            #+#    #+#             */
/*   Updated: 2025/12/01 19:39:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main()
{
    t_data data;

    data.n_philos = 5;
    data.time_to_die = 800;
    data.time_to_eat = 300;
    data.time_to_sleep = 500;
    data.must_eat = -1;

    if (!ft_init_inside_data(&data))
        return (printf("Erro init inside data\n"));
    if (!ft_init_philos(&data))
        return (printf("Erro init philos\n"));
    if (!ft_start_simulation(&data))
        return (printf("Erro start simulation\n"));
    ft_destroy_all(&data);
    return (0);
}
