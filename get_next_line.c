/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:06:48 by yulpark           #+#    #+#             */
/*   Updated: 2024/11/07 19:45:51 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char *result, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(result, buffer);
	free(result);
	return (temp);
}

static char	*ft_findn(int fd, char *result)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(result);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!result)
			result = ft_strdup("");
		result = ft_free(result, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (result);
}

static char	*ft_lineprinter(char	*buffer)
{
	char	*result;
	int		i;

	i = 0;
	if (buffer[0] == '\0')
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return (ft_strdup(buffer));
	else
		result = malloc((i + 2) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		result[i] = buffer[i];
		i++;
	}
	result[i] = '\n';
	result[i + 1] = '\0';
	return (result);
}

static char	*ft_nextkeeper(char *buffer, char **tofree)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0' || buffer[i + 1] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	i++;
	result = malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
	if (!result)
	{
		free(buffer);
		*tofree = NULL;
		return (NULL);
	}
	j = 0;
	while (buffer[i + j] != '\0')
	{
		result[j] = buffer[i + j];
		j++;
	}
	result[j] = '\0';
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_findn(fd, buffer);
	if (!buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	result = ft_lineprinter(buffer);
	if (!result)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_nextkeeper(buffer, &result);
	return (result);
}
//int main()
//{
//	int fd = open("multiple_nl.txt", O_RDONLY);
//	char *result = "";

//	while (result != NULL)
//	{
//		result = get_next_line(fd);
//		if (result != NULL)
//		{
//			printf("%s", result);
//			free(result);
//		}
//	}
//	close(fd);
//	return 0;
//}
