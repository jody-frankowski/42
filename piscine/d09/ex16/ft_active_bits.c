/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_active_bits.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 14:53:13 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 14:53:14 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

unsigned int	ft_active_bits(int value)
{
	unsigned int bits;

	bits = 0;
	while (value != 0)
	{
		if (value & 1)
			bits++;
		value >>= 1;
	}
	return (bits);
}
