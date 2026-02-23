/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:56:27 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 21:15:30 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int					ft_isascii(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
int					ft_strlen(const char *str);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, void const *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
int					ft_strlcpy(char *dst, const char *src, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *src, int c);
char				*ft_strrchr(const char *src, int c);
int					ft_strncmp(const char *s1, const char *s2, unsigned int n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_atoi(char *str);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				**ft_split(char *s, char c);
char				*ft_itoa(int n);
int ft_printchar(char c);
int ft_printstr(char *str);
int ft_printnbr(int nb);
int ft_printunbr(unsigned int nb);
int ft_printhex(unsigned long const nb, char c);
int ft_condition(char const p, va_list args);
int ft_printf(char const *p, ...);
char *ft_strcpy(char *dest, char *src);
char	*extract_line(char *aux_read);
char	*remove_first_line(char *statica);
int		mystrlen(char *str);
char	*mystrjoin(char *statica, char *aux_read);
char	*get_read(int fd, char *statica);
char	*aux_get_read(int fd, char *statica, char *aux_read);
char	*get_next_line(int fd);
int	mystrchr(const char *src, int c);


#endif