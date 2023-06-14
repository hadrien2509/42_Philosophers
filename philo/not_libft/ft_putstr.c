/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_and_nbr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:14:44 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/14 16:17:06 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putnbr(int n)
{
	int long	nl;

	nl = n;
	if (nl < 0)
	{
		nl = nl * (-1);
		ft_putchar('-');
	}
	if (nl >= 10)
	{
		ft_putnbr(nl / 10);
		nl = nl % 10;
	}
	ft_putchar(nl + '0');
}

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}
