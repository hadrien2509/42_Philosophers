/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:08:19 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/27 19:40:27 by hgeissle         ###   ########.fr       */
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
	int	error;

	error = 0;
	if (data->nbr_of_philos < 1)
		error = print_error(ERROR_ARG1);
	if (data->time_to_die < 0)
		error = print_error(ERROR_ARG2);
	if (data->time_to_eat < 0)
		error = print_error(ERROR_ARG3);
	if (data->time_to_sleep < 0)
		error = print_error(ERROR_ARG4);
	if (ac == 6 && (data->must_eat < 0))
		error = print_error(ERROR_ARG5);
	if (error)
		return (1);
	data->table = malloc(sizeof(int) * data->nbr_of_philos);
	if (!data->table)
		return (print_error(ERROR_MALLOC));
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

void	set_table(t_philo *data)
{
	int		i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		data->table[i] = 1;
		i++;
	}
}

int	convert_args(t_philo *data, int ac, char **av)
{
	data->nbr_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->philo_feed = 0;
	if (ac == 6)
	{
		data->must_eat = ft_atoi(av[5]);
		data->philo_feed = malloc(sizeof(int));
		if (!data->philo_feed)
			return (print_error(ERROR_MALLOC));
		*data->philo_feed = 0;
	}
	else
		data->must_eat = -1;
	return (0);
}

int	init_data(t_philo *data, int ac, char **av)
{
	int				i;
	int				error;

	data->philos = 0;
	data->table = 0;
	error = 0;
	error = convert_args(data, ac, av);
	data->dead = malloc(sizeof(int));
	*data->dead = 0;
	data->lock = malloc(sizeof(pthread_mutex_t));
	if (!data->lock || !data->dead || error)
		return (print_error(ERROR_MALLOC));
	if (pthread_mutex_init(data->lock, NULL) != 0)
		return (print_error("mutex init failed\n"));
	set_table(data);
	return (0);
}

void	print_mutex(t_philothread *philo, char *str)
{
	pthread_mutex_lock(philo->lock);
	ft_putnbr(philo->timer);
	ft_putstr(" ");
	ft_putnbr(philo->nbr);
	ft_putstr(str);
	pthread_mutex_unlock(philo->lock);
}

void	take_forks(t_philothread *philo)
{
	pthread_mutex_lock(philo->lock);
	if (philo->nbr == 1 && philo->table[philo->nbr_of_philos - 1] != 0)
	{
		get_timer(philo);
		printf("%lld %d has taken a fork\n", philo->timer, philo->nbr);
		philo->table[philo->nbr_of_philos - 1] = 0;
		philo->forks++;
	}
	if (philo->nbr != 1 && philo->table[philo->nbr - 2] != 0)
	{
		get_timer(philo);
		printf("%lld %d has taken a fork\n", philo->timer, philo->nbr);
		philo->table[philo->nbr - 2] = 0;
		philo->forks++;
	}
	if (philo->table[philo->nbr - 1] != 0)
	{
		get_timer(philo);
		printf("%lld %d has taken a fork\n", philo->timer, philo->nbr);
		philo->table[philo->nbr - 1] = 0;
		philo->forks++;
	}
	pthread_mutex_unlock(philo->lock);
}

int	check_death(t_philothread *philo)
{
	pthread_mutex_lock(philo->lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->lock);
		return (1);
	}
	if (philo->must_eat >= 0 && *philo->philo_feed == philo->nbr_of_philos)
	{
		pthread_mutex_unlock(philo->lock);
		return (1);
	}
	get_timer(philo);
	if (philo->timer > philo->last_meal + philo->time_to_die)
	{
		printf("%lld %d died\n", philo->timer, philo->nbr);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->lock);
		return (1);
	}
	pthread_mutex_unlock(philo->lock);
	return (0);
}

int	ft_usleep(long long time, t_philothread *philo)
{
	struct timeval	*tv;
	long long		old;

	get_timer(philo);
	old = philo->timer;
	while (philo->timer < old + time)
	{
		if (check_death(philo))
			return (1);
		usleep(100);
		get_timer(philo);
	}
	if (check_death(philo))
		return (1);
	return (0);
}

int	start_forks(t_philothread *philo)
{
	if (philo->nbr % 2 == 1 && philo->nbr != philo->nbr_of_philos)
	{
		if (check_death(philo))
			return (1);
		printf("%lld %d has taken a fork\n", philo->timer, philo->nbr);
		printf("%lld %d has taken a fork\n", philo->timer, philo->nbr);
		printf("%lld %d is eating\n", philo->timer, philo->nbr);
		philo->last_meal = philo->timer;
		if (ft_usleep(philo->time_to_eat, philo))
			return (1);
		printf("%lld %d is sleeping\n", philo->timer, philo->nbr);
		if (ft_usleep(philo->time_to_sleep, philo))
			return (1);
		printf("%lld %d is thinking\n", philo->timer, philo->nbr);
	}
	else
	{
		if (ft_usleep(philo->time_to_eat, philo))
			return (1);
	}
	return (0);
}

void	put_forks(t_philothread *philo)
{
	if (philo->nbr == 1)
		philo->table[philo->nbr_of_philos - 1] = 1;
	else
		philo->table[philo->nbr - 2] = 1;
	philo->table[philo->nbr - 1] = 1;
	philo->forks = 0;
}

int	check_philo_meals(t_philothread * philo)
{
	if (philo->must_eat >= 0)
	{
		philo->meals++;
		if (philo->meals == philo->must_eat)
			(*philo->philo_feed)++;
		if (*philo->philo_feed == philo->nbr_of_philos)
			return (print_error(PHILO_FEED));
	}
	return (0);
}

void	*rout(t_philothread *philo)
{
	start_forks(philo);
	while (1)
	{
		if (check_death(philo))
			return (NULL);
		take_forks(philo);
		if (philo->forks == 2)
		{
			get_timer(philo);
			printf("%lld %d is eating\n", philo->timer, philo->nbr);
			philo->last_meal = philo->timer;
			if (check_philo_meals(philo))
				return (NULL);
			if (ft_usleep(philo->time_to_eat, philo))
				return (NULL);
			printf("%lld %d is sleeping\n", philo->timer, philo->nbr);
			put_forks(philo);
			if (ft_usleep(philo->time_to_sleep, philo))
				return (NULL);
			printf("%lld %d is thinking\n", philo->timer, philo->nbr);
		}
	}
	return (NULL);
}

void	copy_data_to_philo(t_philo *data, int i)
{
	data->philos[i - 1]->nbr = i;
	data->philos[i - 1]->time_to_die = data->time_to_die;
	data->philos[i - 1]->time_to_eat = data->time_to_eat;
	data->philos[i - 1]->time_to_sleep = data->time_to_sleep;
	data->philos[i - 1]->must_eat = data->must_eat;
	data->philos[i - 1]->last_meal = 0;
	data->philos[i - 1]->lock = data->lock;
	data->philos[i - 1]->table = data->table;
	data->philos[i - 1]->nbr_of_philos = data->nbr_of_philos;
	data->philos[i - 1]->forks = 0;
	data->philos[i - 1]->dead = data->dead;
	data->philos[i - 1]->philo_feed = data->philo_feed;
	data->philos[i - 1]->meals = 0;
}

int	init_philos(t_philo *data)
{
	int				i;

	data->philos = malloc(sizeof(t_philothread *) * (data->nbr_of_philos + 1));
	if (!data->philos)
		return (print_error(ERROR_MALLOC));
	data->philos[data->nbr_of_philos] = 0;
	i = 1;
	while (i <= data->nbr_of_philos)
	{
		data->philos[i - 1] = malloc(sizeof(t_philothread));
		if (!data->philos[i - 1])
			return (print_error(ERROR_MALLOC));
		copy_data_to_philo(data, i);
		i++;
	}
	return (0);
}

void	free_threads(t_philo *data)
{
	int	i;

	i = 1;
	if (data->philos)
	{
		while (data->philos[i - 1])
		{
			free(data->philos[i - 1]);
			i++;
		}
		free(data->philos);
	}
}

void	free_memory(t_philo *data)
{
	if (data->lock)
	{
		pthread_mutex_destroy(data->lock);
		free(data->lock);
	}
	if (data->table)
		free(data->table);
	if (data->dead)
		free(data->dead);
	if (data->philo_feed)
		free(data->philo_feed);
	free_threads(data);
	free(data);
}

int	main(int ac, char **av)
{
	t_philo			*data;
	int				i;
	struct timeval	tv;

	if (ac != 5 && ac != 6)
		return (print_error(ERROR_ARGS));
	data = malloc(sizeof(t_philo));
	if (!data)
		return (print_error(ERROR_MALLOC));
	if (init_data(data, ac, av) == 1)
	{
		free_memory(data);
		return (1);
	}
	if (check_arguments(ac, av, data) == 1)
	{
		free_memory(data);
		return (1);
	}
	if (init_philos(data) == 1)
	{
		free_memory(data);
		return (1);
	}
	i = 0;
	if (gettimeofday(&tv, NULL) == -1)
		exit (print_error("gettimeofday error\n"));
	data->launch_time = timeval_to_long(&tv);
	while (i < data->nbr_of_philos)
	{
		data->philos[i]->launch_time = data->launch_time;
		pthread_create(&data->philos[i]->thr, 0, (void *)rout, data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->nbr_of_philos)
	{
		pthread_join(data->philos[i]->thr, 0);
		i++;
	}
	free_memory(data);
	return (0);
}
