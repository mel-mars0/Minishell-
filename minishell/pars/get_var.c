/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mars < mel-mars@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:07:37 by mel-mars          #+#    #+#             */
/*   Updated: 2023/03/16 10:08:47 by mel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syn(char *str, int i)
{
	int	k;

	k = 1;
	while (str[i] && (str[i + k] == ' ' || str[i + k] == '\t'))
		k++;
	if ((str[i] == '<' || str[i] == '>' || str[i] == '|')
		&& str[i + k] == '\0')
		return (-2);
	if (str[i] == '<' && (str[i + k] == '\0'
			|| str[i + k] == '|' || str[i + k] == '>'
			|| (str[i + k] == '<' && k != 1)))
		return (-2);
	if (str[i] == '>' && (str[i + k] == '\0'
			|| str[i + k] == '|' || str[i + k] == '<'
			|| (str[i + k] == '>' && k != 1)))
		return (-2);
	if (str[i] == '|' && (str[i + k] == '\0'
			|| str[i + k] == '|'))
		return (-2);
	return (0);
}

char	*ft_lost_var_r(char *arr, int i)
{
	char	*str;

	i = norm_get0(arr, i);
	if (i < (int )ft_strlen(arr) && arr[i] == '?')
		return (ft_strdup(&arr[i + 1]));
	while (arr[i] && !ft_strchr(" +*-\'\"|:;$<?>\t\r,.=/", arr[i]))
		i++;
	str = ft_strdup(&arr[i]);
	return (str);
}

int	norm_get1(char *arr, int i)
{
	while (arr[i] && arr[i] != '$')
	{
		while (arr[i] && arr[i] == '\'' && count_s_quote(arr) % 2 == 0
			&& check_the_first(&arr[i], 0) == 1)
		{
			i++;
			while (arr[i] && arr[i] != '\'')
				i++;
			if (arr[i] == '\'')
				break ;
		}
		i++;
	}
	return (i);
}

char	*ft_lost_var_l(char *arr, int i)
{
	char	*str;
	int		j;

	i = norm_get1(arr, i);
	str = ft_calloc(i + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	j = i;
	i = 0;
	while (arr[i] && i < j)
	{
		str[i] = arr[i];
		i++;
	}
	return (str);
}

char	*o_trim0(char *arr)
{
	char	**str;
	char	*dest;

	str = split_var_exp(arr, 0, 0);
	str = cmd_trim(str, 0);
	free(arr);
	arr = dbl_strjoin(str);
	ft_free_dbl(str);
	dest = ft_strdup(arr);
	return (dest);
}
