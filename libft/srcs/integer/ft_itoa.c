/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:56:49 by wta               #+#    #+#             */
/*   Updated: 2019/05/15 23:43:33 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_itoa(int n)
{
	size_t	len;
	long	nb;
	char	*str;

	len = ft_intlen_base(n, 10);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	*(str + len) = 0;
	nb = n;
	nb = (nb < 0) ? -nb : nb;
	while (len > 1)
	{
		len--;
		*(str + len) = nb % 10 + '0';
		nb /= 10;
	}
	*str = (n < 0) ? '-' : nb % 10 + '0';
	return (str);
}
