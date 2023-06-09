/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:17 by samy              #+#    #+#             */
/*   Updated: 2023/06/14 16:17:48 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int long	nl;

	nl = n;
	if (nl < 0)
	{
		nl = nl * (-1);
		ft_putchar_fd('-', fd);
	}
	if (nl >= 10)
	{
		ft_putnbr_fd(nl / 10, fd);
		nl = nl % 10;
	}
	ft_putchar_fd(nl + '0', fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || !fd)
		return ;
	write(fd, s, ft_strlen(s));
}
