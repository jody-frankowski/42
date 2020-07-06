/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libprintf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPRINTF_H
# define LIBPRINTF_H

# include <stdarg.h>

typedef struct		s_conversion_spec
{
	unsigned int	hash_flag:1;
	unsigned int	zero_flag:1;
	unsigned int	minus_flag:1;
	unsigned int	space_flag:1;
	unsigned int	plus_flag:1;
	unsigned int	precision_flag:1;
	unsigned int	length_modifier_flag:1;
	unsigned int	length_modifier:3;
	unsigned int	specifier:8;
	unsigned int	field_width;
	int				precision;
}					t_conv;

enum				e_length_modifier
{
	HH, H, L, LL, LF
};

extern char			*g_first_part;
extern char			*g_second_part;
extern char			*g_output;
extern int			(*g_converter['x' + 1])(va_list args, t_conv conv);

void				append_nchar(char *str, char c, int n);
void				prepend_nchar(char *str, char c, int n);
int					allocate_globals(t_conv conv, int num_chars);
int					biggest(int a, int b, int c);
void				cat_and_free();
int					ft_num_digits_ld(long double num);
int					ft_signbit_ld(long double num);
int					free_globals();
int					get_base(t_conv conv);
long double			get_num_ld(va_list args, t_conv conv);
long long			get_num_ll(va_list args, t_conv conv);
unsigned long long	get_num_ull(va_list args, t_conv conv);
void				init_converter();
void				pad_for_field_width(t_conv conv);

int					convert_di(va_list args, t_conv conv);
int					convert_ou(va_list args, t_conv conv);
int					convert_xx(va_list args, t_conv conv);
int					convert_ff(va_list args, t_conv conv);
int					convert_c(va_list args, t_conv conv);
int					convert_s(va_list args, t_conv conv);
int					convert_p(va_list args, t_conv conv);
int					convert_percent(va_list args, t_conv conv);

 __attribute__((format(printf,1,2)))
int					ft_printf(const char *format, ...);
 __attribute__((format(printf,2,3)))
int					ft_dprintf(int fd, const char *format, ...);
 __attribute__((format(printf,2,3)))
int					ft_sprintf(char *str, const char *format, ...);
 __attribute__((format(printf,1,0)))
int					ft_vprintf(const char *format, va_list args);
 __attribute__((format(printf,2,0)))
int					ft_vdprintf(int fd, const char *format, va_list args);
 __attribute__((format(printf,2,0)))
int					ft_vsprintf(char *str, const char *format, va_list args);

t_conv				parse_conversion(const char **format);

#endif
