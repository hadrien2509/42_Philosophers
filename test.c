/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:11:03 by hgeissle          #+#    #+#             */
/*   Updated: 2022/10/16 17:11:03 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


int main(void)
{
    char    buffer[5];
	int		fd;
	int		d;
	char	*line;
/*
	fd = open("text.txt",  O_CREAT | O_WRONLY, 0600);
	if (fd == -1)
	{
		printf("failed to create and open the file.\n");
	}
	write(fd, "salut michael\n", 14);
	close(fd);
*/
	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("failed to create and open the file.\n");
	}
	while ()
	line = get_next_line(fd);
	free(line);
}

int	ft_newline(char *buffer)
{
	char*	buffer;

	while (*buffer)
	{
		if (buffer == '\n')
			return (1);
	}
	return (0);
}

int	get_next_line_len(int fd, int r)
{
	char	*buffer;
	size_t	len;
	size_t	r;

	len = 0;
	while (r)
	{
		r = read(fd, buffer, 20);
		len += r;
		if (ft_newline(buffer))
		{	
			while (buffer[len] != '\n')
				len--;
			r = len;
			return (len);
		}
	}
	return (len);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	size_t		len;
	static int	r;

	len = get_next_line_len(r, fd);
	line = malloc(sizeof(char) * len);
	while (read(fd, buffer, 50))
	{
		printf("%d\n", sizeof(char));
		buffer[50] = '\0';
		while (!(*buffer) && *buffer =! '\n')
		{	
			*line = *buffer;
			buffer++;
		}
		printf("%s\n", buffer);
	}
	return (line);
}
	