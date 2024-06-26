/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by tfalchi           #+#    #+#             */
/*   Updated: 2024/04/10 15:05:47 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	unsigned int		s_len;
	unsigned int		i;
	char				*p;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	p = (char *)malloc((s_len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (s_len > i)
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
