/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:29:49 by rbouizer          #+#    #+#             */
/*   Updated: 2024/02/19 03:09:31 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line(char *str, size_t *len)
{
	char	*s;

	s = NULL;
	if (!*str)
		return (NULL);
	while (str[*len] && str[*len] != '\n')
		(*len)++;
	if (str[*len] == '\n')
		(*len)++;
	s = (char *)malloc(sizeof(char) * (*len + 1));
	if (!s)
		return (NULL);
	(*len) = 0;
	while (str[*len] && str[*len] != '\n')
	{
		s[*len] = str[*len];
		(*len)++;
	}
	if (str[*len] == '\n')
	{
		s[*len] = str[*len];
		(*len)++;
	}
	s[*len] = '\0';
	return (s);
}

char	*modifie_save(char *save, size_t len)
{
	char	*new_save;
	size_t	i;

	i = 0;
	new_save = (char *)malloc(sizeof(char) * (ft_strlen(save) - len + 1));
	if (!new_save)
		return (NULL);
	while (save[len])
		new_save[i++] = save[len++];
	new_save[i] = '\0';
	free(save);
	return (new_save);
}

char	*save_all(char *save, int fd)
{
	char	*str;
	int		readhandel;

	str = (char *)malloc(BUFFER_SIZE + 1);
	if (!str)
		return (free(save), NULL);
	readhandel = 1;
	while (!ft_strchr(save, '\n') && readhandel > 0)
	{
		readhandel = read(fd, str, BUFFER_SIZE);
		if (readhandel == -1)
			return (free(str), free(save), NULL);
		str[readhandel] = '\0';
		save = ft_strjoin(save, str);
		if (!save)
			return (free(str), NULL);
	}
	free(str);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;
	size_t		len;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 0)
		return (NULL);
	save[fd] = save_all(save[fd], fd);
	if (!save[fd] || *save[fd] == '\0')
		return (free(save[fd]), save[fd] = NULL, NULL);
	len = 0;
	line = get_line(save[fd], &len);
	if (!line)
		return (free(save[fd]), NULL);
	save[fd] = modifie_save(save[fd], len);
	if (!save[fd])
		return (NULL);
	return (line);
}
