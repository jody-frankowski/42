/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/09 18:21:58 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/09 18:21:59 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int				ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int dest_len;
	unsigned int src_len;
	unsigned int osize;

	dest_len = 0;
	src_len = ft_strlen(src);
	osize = size;
	while (*dest && size > 0)
	{
		dest++;
		dest_len++;
		size--;
	}
	if (size == 0)
		return (osize < dest_len ? src_len + osize : src_len + dest_len);
	while (*src && size > 1)
	{
		*dest = *src;
		size--;
		dest++;
		src++;
	}
	*dest = '\0';
	return (osize < dest_len ? src_len + osize : src_len + dest_len);
}
