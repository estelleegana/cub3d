/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:32:57 by estegana          #+#    #+#             */
/*   Updated: 2023/05/17 19:09:08 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c <= 127 && c >= 0)
		return (1);
	else
		return (0);
}
/*#include <ctype.h>
#include <stdio.h>

int main()
{
	int c =160;

	printf("%d ref\n", isascii(c));
	printf("%d test bev", ft_isascii(c));
	return 0;
}*/
