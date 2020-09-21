/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-nada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 19:23:28 by ede-nada          #+#    #+#             */
/*   Updated: 2020/09/17 23:03:01 by ede-nada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char				*str;
	unsigned long int	i;
	unsigned long int	j;

	if (!s1)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (0);
	i = 0;
	while (s1[i] != 0)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int new_line(char *s_line)
{
	int i;

	if (!(s_line))
		return (-1);
	i = 0;
	while (s_line[i])
	{
		if (s_line[i] == '\n')
			return (i);
		else if (s_line[i] == EOF)
			return (0);
		i++;
	}
	return (-1);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	j = 0;
	while (s1[i] != 0)
		i++;
	s2 = (char *)malloc((i + 1) * sizeof(char));
	if (!s2)
		return (0);
	while (j < i)
	{
		*(s2 + j) = *((char *)s1 + j);
		j++;
	}
	s2[j] = 0;
	return ((char *)s2);
}

char *ft_break_line(char **line, char *s_line)
{
	int nl;
	int j;
	char *tmp_line;
	char *tmp_sline;

	nl = new_line(s_line);
	j = ft_strlen(s_line);
	tmp_line = (char *)malloc(sizeof(char) * nl);
	tmp_sline = (char *)malloc(sizeof(char) * (j - nl));
	tmp_line = ft_substr(s_line, 0, nl);
	tmp_sline = ft_substr(s_line, nl + 1, (j - nl)); 
	*line = ft_strdup(tmp_line);
	free(tmp_line);
	return (tmp_sline);
}

void	ft_bzero(void *s, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)s + i) = 0;
		i++;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;
	size_t			l;

	if (!s)
		return (0);
	i = 0;
	l = ft_strlen(s);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	if (!str)
		return (0);
	while (i < len && (start + i) < l)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
