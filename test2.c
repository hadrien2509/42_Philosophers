/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:03:25 by hgeissle          #+#    #+#             */
/*   Updated: 2022/10/17 13:03:25 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	buffer[20];
	
	buffer[20] = '\0';
	fd = open("text.txt", O_RDONLY);
	while (read(fd, buffer, 20))
	{
		printf("%s\n", buffer);
	}
	read(fd, buffer, 20);
	printf("%s\n", buffer);
	return (0);
}