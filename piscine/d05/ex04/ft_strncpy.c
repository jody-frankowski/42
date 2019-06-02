/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/08 19:24:16 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/08 19:24:17 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	char *dest_save;

	dest_save = dest;
	if (n != 0)
	{
		while (*src && n > 0)
		{
			*dest = *src;
			src++;
			dest++;
			n--;
		}
		while (n > 0)
		{
			*dest = '\0';
			dest++;
			n--;
		}
	}
	return (dest_save);
}
