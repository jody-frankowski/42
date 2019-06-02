/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_takes_place.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 12:13:42 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 12:13:42 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>

void	ft_takes_place(int hour)
{
	int hour_12;
	int next_hour;

	hour_12 = hour % 12;
	next_hour = hour_12 + 1;
	printf("THE FOLLOWING TAKES PLACE BETWEEN ");
	if (hour == 00 || hour == 24)
	{
		hour_12 = 12;
		next_hour = 1;
	}
	if (hour == 12)
		hour_12 = 12;
	if (hour < 12)
		printf("%02d.00 A.M. AND %02d.00 A.M.\n", hour_12, next_hour);
	else if (hour == 24)
		printf("%02d.00 P.M. AND %02d.00 A.M.\n", hour_12, next_hour);
	else
		printf("%02d.00 P.M. AND %02d.00 P.M.\n", hour_12, next_hour);
}
