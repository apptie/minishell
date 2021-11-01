/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 13:45:26 by jimikim           #+#    #+#             */
/*   Updated: 2021/08/15 22:31:42 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

char	*ft_strchr(const char *s, int c);
char	**ft_split(const char *s, char c);
char	*ft_strdup(char *s1);
char	*ft_strndup(char *s1, int size);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strcat(char *dest, char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_isdigit(int c);
int		ft_atoi(char *str);
char	*ft_strtrim(char const *s1, char const *set);

#endif
