/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:08:19 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/05 16:23:24 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

int	check_arguments(int ac, char **av, t_philo *data)
{
	if (ac != 4 && ac != 5)
		return (print_error(ERROR_ARGS));
	if (data->nbr_of_philos < 1)
		return (print_error(ERROR_ARG0));
	if (data->time_to_die < 0)
		return (print_error(ERROR_ARG1));
	if (data->time_to_eat < 0)
		return (print_error(ERROR_ARG2));
	if (data->time_to_sleep < 0)
		return (print_error(ERROR_ARG3));
	if (ac == 6 && (data->must_eat < 0))
		return (print_error(ERROR_ARG4));
	return (0);
}

int	timeval_to_long(const struct timeval *tv)
{
	long long	milliseconds;

	milliseconds = tv->tv_sec * 1000;
	milliseconds += tv->tv_usec / 1000;
	return (milliseconds);
}

int	get_timer(t_philo *data)
{
	long long	current_time;

	if (gettimeofday(data->current_time, NULL) == -1)
		return (print_error("gettimeofday error\n"));
	current_time = timeval_to_long(data->current_time);
	data->timer = current_time - data->launch_time;
	return (0);
}

void	init_data(t_philo *data, int ac, char **av)
{
	data->philo_nbr = 1;
	data->launch_time = 0;
	data->current_time = malloc(sizeof(struct timeval));
	if (!data->current_time)
		return ;
	data->nbr_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	data->last_meal = 0;
}

void	*routine(t_philo *data)
{
	while (1)
	{
		get_timer(data);
		printf("%lld %d has taken a fork\n", data->timer, data->philo_nbr);
		printf("%lld %d is eating\n", data->timer, data->philo_nbr);
		usleep(data->time_to_eat);
		get_timer(data);
		printf("%lld %d is sleeping\n", data->timer, data->philo_nbr);
		usleep(data->time_to_sleep);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t	**philo;
	t_philo		*data;
	int			i;

	data = malloc(sizeof(t_philo));
	if (!data)
		return (print_error("data structure malloc failed\n"));
	init_data(data, ac, av);
	if (check_arguments(ac, av, data) == 1)
		return (1);
	data->philos = malloc(sizeof(pthread_t *) * (data->nbr_of_philos + 1));
	if (!data->philos)
		return (42);
	data->philos[data->nbr_of_philos] = 0;
	get_timer(data);
	data->launch_time = data->timer;
	while (data->philo_nbr <= data->nbr_of_philos)
	{
		data->philos[data->philo_nbr] = malloc(sizeof(pthread_t));
		if (!data->philos[data->philo_nbr])
			return (print_error("philo malloc failed\n"));
		pthread_create(data->philos[data->philo_nbr], NULL, (void*)routine, data);
		data->philo_nbr++;
	}
	return (0);
}
