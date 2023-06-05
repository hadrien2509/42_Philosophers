/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:08:19 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/04 15:08:19 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

int check_arguments(int ac, char **av, t_philo	*data)
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
	if (ac == 5 && (data->must_eat < 0))
		return (print_error(ERROR_ARG4));
	return (0);
}

void	init_data(t_philo *data, int ac, char **av)
{
	data->nbr_of_philos = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	if (ac == 5)
		data->must_eat = ft_atoi(av[4]);
	else
		data->must_eat = -1;
	data->last_meal = 0;
}

int	main(int ac, char **av)
{
	pthread_t	**philo;
	t_philo		*data;

	if (check_arguments(ac, av, data) == 1)
	{

		return (1);
	init_data(data, av);
	data->philos = malloc(sizeof(pthread_t) * ac);
	if (!data->philos)
		return(42);
	pthread_create();
	return (0);	
}

