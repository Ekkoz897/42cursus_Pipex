/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:42:01 by apereira          #+#    #+#             */
/*   Updated: 2023/02/22 19:44:03 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Long because couldn't compile with int, said condition is always false

/**
 * It converts a string to an integer.
 * 
 * str The string to be converted.
 * 
 * res the number as an int.
 */

long	ft_atoi(const char *str)
{
	long long	res;
	int			i;
	int			posneg;

	res = 0;
	i = 0;
	posneg = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			posneg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * posneg);
}
