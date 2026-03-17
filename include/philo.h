/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoreir <jemoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:02:04 by jemoreir          #+#    #+#             */
/*   Updated: 2025/12/03 17:02:04 by jemoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				n_philos;
	int				must_eat;
	int				stop;
	long long		start_time;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	pthread_mutex_t	finished_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals;
	int				finished;
	long long		last_meal;
	pthread_t		t;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	*fork_one;
	pthread_mutex_t	*fork_two;
	t_data			*data;
}	t_philo;

int			ft_strlen(char *c);
int			ft_str_is_digit(char *c);
int			ft_int_max(char *str);
int			ft_safe_atoi(char *str, int *nbr);
int			ft_init_data(t_data *data, int argc, char **argv);
void		ft_destroy_forks(t_data *data, int s);
int			ft_init_mutexes(t_data *data);
int			ft_init_inside_data(t_data *data);
void		ft_destroy_all(t_data *data);
long long	ft_get_time_ms(void);
void		ft_fork_atr(t_data *data, int i);
int			ft_init_philos(t_data *data);
int			ft_start_simulation(t_data *data);
void		*rt(void *arg);
void		ft_print_status(t_philo *philo, char *msg);
void		ft_philo_eat(t_philo *philo);
void		ft_philo_sleep(t_philo *philo);
void		ft_philo_think(t_philo *philo);
int			ft_usleep(long long ms, t_data *data);
int			ft_runing(t_data *data);
void		ft_set_stop(t_data *data);
int			ft_check_death(t_data *data);
int			ft_check_all_ate(t_data *data);
void		*ft_monitor(void *arg);
void		ft_join_philos(t_data *data, int philos);

#endif
