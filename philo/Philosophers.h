/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:57:50 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/04 14:57:50 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define ERROR_ARGS "This program four or five argument :\n - number_of_philosophers\n -  time_to_die\n - time_to_sleep\n - number_of_times_each_philosopher_must_eat (Optional)\n"
#define ERROR_ARG0 "First argument is the number of philosophers and must be a number superior or equal to one\n"
#define ERROR_ARG1 "Second argument is the time of death and must be a number superior or equal to zero\n"
#define ERROR_ARG2 "Third argument is the time it takes each philosopher to eat and it must be a number superior or equal to zero\n"
#define ERROR_ARG3 "Fourth argument is the maximum of time a philosopher can survive since last meal and it must be a number superior or equal to zero\n"
#define ERROR_ARG4 "Fifth argument is how much times each philosopher has to eat and it must be a number superior or equal to zero\n"

typedef struct s_philo
{
	pthread_t	**philos;
	int			nbr_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	int			last_meal;
}				t_philo;

int		ft_atoi(const char *str);
int		ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);

#endif 