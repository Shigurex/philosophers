/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:41:34 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/15 16:41:52 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers_bonus.h"

static int	ft_count_digit(int n)
{
	int	digit;

	digit = 1;
	if (n < 0)
	{
		if (n <= -10)
		{
			n /= 10;
			digit++;
		}
		n *= -1;
		digit++;
	}
	while (n >= 10)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

static void	ft_storenumber(int n, int digit, char *str)
{
	if (n < 0)
	{
		str[0] = '-';
		if (n <= -10)
			ft_storenumber(-(n / 10), digit - 1, str);
		n = -(n % 10);
	}
	else if (n >= 10)
	{
		ft_storenumber(n / 10, digit - 1, str);
		n = n % 10;
	}
	str[digit] = n + '0';
}

char	*ft_itoa(int n)
{
	int		digit;
	char	*str;

	digit = ft_count_digit(n);
	str = malloc(sizeof(char) * (digit + 1));
	if (str == NULL)
		return (NULL);
	ft_storenumber(n, digit - 1, str);
	str[digit] = '\0';
	return (str);
}