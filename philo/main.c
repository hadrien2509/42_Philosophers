/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:08:19 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/14 17:51:25 by hgeissle         ###   ########.fr       */
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

long long	timeval_to_long(const struct timeval *tv)
{
	long long	milliseconds;

	milliseconds = tv->tv_sec * 1000;
	milliseconds += tv->tv_usec / 1000;
	return (milliseconds);
}

int	get_timer(t_philothread *philo)
{
	struct timeval	tv;
	long long		current_time;

	if (gettimeofday(&tv, NULL) == -1)
		return (print_error("gettimeofday error\n"));
	current_time = timeval_to_long(&tv);
	philo->timer = current_time - philo->launch_time;
	return (0);
}

void	init_data(t_philo *data, int ac, char **av)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		exit (print_error("gettimeofday error\n"));
	data->launch_time = timeval_to_long(&tv);
	data->nbr_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	data->last_meal = data->launch_time;
	data->lock = malloc(sizeof(pthread_mutex_t));
	if (!data->lock)
		exit (printf("malloc failed\n"));
	if (pthread_mutex_init(data->lock, NULL) != 0)
		exit (print_error("\n mutex init failed\n"));
}

void	print_mutex(t_philothread *philo, int status)
{
	pthread_mutex_lock(philo->lock);
	ft_putnbr(philo->timer);
	ft_putstr(" ");
	ft_putnbr(philo->nbr);
	if (status == 1)
		ft_putstr(" has taken a fork\n");
	if (status == 2)
		ft_putstr(" is eating\n");
	if (status == 3)
		ft_putstr(" is sleeping\n");
	if (status == 4)
		ft_putstr(" is thinking\n");
	pthread_mutex_unlock(philo->lock);
}

void	*routine(t_philothread *philo)
{
	while (1)
	{
		get_timer(philo);
		print_mutex(philo, 1);
		print_mutex(philo, 2);
		usleep(philo->time_to_eat * 1000);
		get_timer(philo);
		print_mutex(philo, 3);
		usleep(philo->time_to_sleep * 1000);
		print_mutex(philo, 4);
	}
	return (NULL);
}

void	init_philos(t_philo *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philothread *) * (data->nbr_of_philos + 1));
	if (!data->philos)
		exit (42);
	data->philos[data->nbr_of_philos] = 0;
	i = 1;
	while (i <= data->nbr_of_philos)
	{
		data->philos[i - 1] = malloc(sizeof(t_philothread));
		if (!data->philos[i - 1])
			exit (print_error("philo malloc failed\n"));
		data->philos[i - 1]->nbr = i;
		data->philos[i - 1]->time_to_die = data->time_to_die;
		data->philos[i - 1]->time_to_eat = data->time_to_eat;
		data->philos[i - 1]->time_to_sleep = data->time_to_sleep;
		data->philos[i - 1]->must_eat = data->must_eat;
		data->philos[i - 1]->must_eat = data->last_meal;
		data->philos[i - 1]->launch_time = data->launch_time;
		data->philos[i - 1]->lock = data->lock;
		// data->philos[i - 1]->thread = malloc(sizeof(pthread_t));
		// if (!data->philos[i - 1]->thread)
		// 	exit (1);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo		*data;
	int			i;

	data = malloc(sizeof(t_philo));
	if (!data)
		return (print_error("data structure malloc failed\n"));
	init_data(data, ac, av);
	if (check_arguments(ac, av, data) == 1)
		return (1);
	init_philos(data);
	i = 0;
	while (i < data->nbr_of_philos)
	{
		pthread_create(&data->philos[i]->thread, NULL, (void *)routine, data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->nbr_of_philos)
	{
		pthread_join(data->philos[i]->thread, NULL);
		i++;
	}
	return (0);
}
