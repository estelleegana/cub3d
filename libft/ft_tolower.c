/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:04:52 by estegana          #+#    #+#             */
/*   Updated: 2023/05/17 18:55:54 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}
/*
#include <stdio.h>
#include <ctype.h>

int main()
{
        int i = 120;
        printf("%d\n", ft_tolower(i));
        printf("%d", tolower(i));
}*/
