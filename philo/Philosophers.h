/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:57:50 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/27 17:31:05 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define ERROR_ARGS "Usage: program <number_of_philosophers> <time_to_die> <time_to_sleep> \
[<number_of_times_each_philosopher_must_eat>]\n"
# define ERROR_ARG1 "First argument must be a positive integer \
(number_of_philosophers)\n"
# define ERROR_ARG2 "Second argument must be a non-negative number \
(time_to_die)\n"
# define ERROR_ARG3 "Third argument must be a non-negative number \
(time_to_eat)\n"
# define ERROR_ARG4 "Third argument must be a non-negative number \
(time_to_sleep)\n"
# define ERROR_ARG5 "Fourth argument must be a non-negative number \
(number_of_times_each_philosopher_must_eat)\n"
# define ERROR_MALLOC "Memory allocation failed\n"
# define PHILO_FEED "All philosophers have been fed\n"

typedef struct s_philothread
{
	long long		time_to_die;
	int				nbr_of_philos;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat;
	int				*table;
	long long		last_meal;
	int				nbr;
	long long		launch_time;
	long long		timer;
	int				meals;
	int				*philo_feed;
	struct timeval	*current_time;
	int				forks;
	int				*dead;
	pthread_t		thr;
	pthread_mutex_t	*lock;
}				t_philothread;

typedef struct s_philo
{
	t_philothread	**philos;
	int				nbr_of_philos;
	int				*table;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat;
	int				*philo_feed;
	int				*dead;
	long long		last_meal;
	long long		launch_time;
	long long		timer;
	pthread_mutex_t	*lock;
}				t_philo;

int		ft_atoi(const char *str);
int		ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr(char *s);
void	ft_putnbr(int n);
void	ft_putchar(char c);
int		ft_isdigit(int c);

#endif 