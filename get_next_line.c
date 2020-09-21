/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_Line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-nada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 22:45:05 by ede-nada          #+#    #+#             */
/*   Updated: 2020/09/17 23:22:00 by ede-nada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char	*s_line;
	char		buffer[BUFFER_SIZE + 1];
	int			ret;

	if (fd < 0 || BUFFER_SIZE < 1 || !(line))
		return (-1);
	if (!s_line)
		s_line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (new_line(s_line) == -1 && (ret = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[ret] = '\0';
		if (ret >= 1 && ret <= BUFFER_SIZE)
			s_line = ft_strjoin(s_line, buffer);
		ft_bzero(buffer, BUFFER_SIZE);
	}
	if (ret >= 0 && ret <= BUFFER_SIZE)
		s_line = ft_break_line(line, s_line);
	if (ret > 0 && ret <= BUFFER_SIZE)
		return (1);
	return (ret == 0 ? 0 : -1);
}
