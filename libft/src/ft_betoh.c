/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_betoh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

/*
** ft_betoh16() - Convert a 16 bits long integer from big-endian to host order
** @value: The value to convert
**
** Return: The value in host order.
*/

uint16_t	ft_betoh16(uint16_t value)
{
	uint16_t	converted;
	size_t		i;

	converted = 0;
	i = 0;
	while (i < sizeof(value))
	{
		converted |= (typeof(value))((uint8_t*)&value)[i]
			<< (8 * (sizeof(value) - 1 - i));
		i++;
	}
	return (converted);
}

/*
** ft_betoh32() - Convert a 32 bits long integer from big-endian to host order
** @value: The value to convert
**
** Return: The value in host order.
*/

uint32_t	ft_betoh32(uint32_t value)
{
	uint32_t	converted;
	size_t		i;

	converted = 0;
	i = 0;
	while (i < sizeof(value))
	{
		converted |= (typeof(value))((uint8_t*)&value)[i]
			<< (8 * (sizeof(value) - 1 - i));
		i++;
	}
	return (converted);
}

/*
** ft_betoh64() - Convert a 64 bits long integer from big-endian to host order
** @value: The value to convert
**
** Return: The value in host order.
*/

uint64_t	ft_betoh64(uint64_t value)
{
	uint64_t	converted;
	size_t		i;

	converted = 0;
	i = 0;
	while (i < sizeof(value))
	{
		converted |= (typeof(value))((uint8_t*)&value)[i]
			<< (8 * (sizeof(value) - 1 - i));
		i++;
	}
	return (converted);
}
