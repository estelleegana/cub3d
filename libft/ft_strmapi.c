/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <estegana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:39:06 by estegana          #+#    #+#             */
/*   Updated: 2024/11/26 10:33:22 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*sm;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	sm = (char *)(malloc(sizeof(char) * (len + 1)));
	if (!sm)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sm[i] = f(i, s[i]);
		i++;
	}
	sm[i] = '\0';
	return (sm);
}
