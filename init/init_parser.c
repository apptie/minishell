/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slee2 <slee2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 20:23:03 by slee2             #+#    #+#             */
/*   Updated: 2021/08/25 09:40:31 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case_quote_temp(char *result, char *s, int *i, int *j)
{
	if (s[*i + 1] && s[*i + 1] == '\"')
		result[(*j)++] = (char)(s[(*i)++]);
	else if (s[*i + 1] && s[*i + 1] == '\'')
		(*i)++;
	else
		result[(*j)++] = (char)(-s[(*i)++]);
}

void	case_quote(t_data *data, char *s, int *i)
{
	int	count;
	int	k;

	k = 0;
	count = 0;
	if (check_quote(s, *i) <= 1)
	{
		if (check_quote(s, *i) == 1)
		{
			k = *i;
			while (check_quote(s, k++) != 0)
				count++;
			count -= 2;
			data->d_int[data->d_idx++] = count;
		}
		else
			data->d_int[data->d_idx++] = ft_strlen(s + *i + 1);
	}
}

void	set_special(char *result, char *s, int *i, int *j)
{
	result[(*j)++] = ' ';
	result[(*j)++] = s[(*i)++];
	if (check_quote(s, *i) == 0
		&& (s[*i] == '>' || s[*i] == '<' || s[*i] == '|'))
		result[(*j)++] = s[(*i)++];
	result[(*j)++] = ' ';
}

char	*set_line(t_data *data, char *s)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc_parser_line(s);
	while (result && s[i])
	{
		if (check_quote(s, i) != 2 && s[i] == '$' && i && s[i - 1] != '\\')
		{
			case_quote(data, s, &i);
			case_quote_temp(result, s, &i, &j);
		}
		else if (check_quote(s, i) == 0 && check_special(s, i))
			set_special(result, s, &i, &j);
		else
			result[j++] = s[i++];
	}
	result[j] = 0;
	data->d_idx = 0;
	return (result);
}

t_parser	*init_parser(t_data *data, char *read_line)
{
	t_parser	*parser;
	t_node		*before;
	char		*line;

	line = set_line(data, read_line);
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);
	parser = malloc(sizeof(t_parser));
	if (!parser)
		print_error_cmd();
	before = 0;
	parser->size = 0;
	parser->start = 0;
	parser->end = 0;
	set_node(line, &before, parser);
	if (!before->next)
		parser->end = before;
	free(line);
	return (parser);
}
