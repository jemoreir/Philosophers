/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoreir <jemoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:01:31 by jemoreir          #+#    #+#             */
/*   Updated: 2025/12/03 17:01:31 by jemoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!ft_init_data(&data, argc, argv))
		return (printf("Error init data\n"));
	if (!ft_init_inside_data(&data))
		return (printf("Error init inside data\n"));
	if (!ft_init_philos(&data))
		return (printf("Error init philos\n"));
	if (!ft_start_simulation(&data))
		return (printf("Error start simulation\n"));
	ft_destroy_all(&data);
	return (0);
}
