/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 11:14:20 by jagan             #+#    #+#             */
/*   Updated: 2026/05/21 12:05:37 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 00:00:00 by jagan             #+#    #+#             */
/*   Updated: 2026/05/21 00:00:00 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Count the number of words in a string separated by spaces.
** Multiple spaces between words are treated as one separator.
** Leading and trailing spaces are ignored.
*/
static int	count_words(char *s)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != ' ' && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == ' ')
			in_word = 0;
		s++;
	}
	return (count);
}

/*
** Copy one word from s into a new malloc'd string.
** A word ends at a space or null terminator.
*/
static char	*get_word(char *s)
{
	char	*word;
	int		len;
	int		i;

	len = 0;
	while (s[len] && s[len] != ' ')
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

/*
** Free a NULL-terminated array of strings.
** Used when malloc fails mid-split.
*/
void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/*
** Split a string by spaces into a NULL-terminated array of words.
** Handles multiple spaces, leading spaces, and trailing spaces.
** Returns NULL on malloc failure.
**
** Examples:
**   "3 1 2"      → ["3", "1", "2", NULL]
**   "  1  2  3 " → ["1", "2", "3", NULL]
**   "42"         → ["42", NULL]
*/
static int	fill_words(char **result, char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == ' ')
		{
			s++;
			continue ;
		}
		result[i] = get_word(s);
		if (!result[i])
			return (0);
		while (*s && *s != ' ')
			s++;
		i++;
	}
	result[i] = NULL;
	return (1);
}

char	**ft_split_space(char *s)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	if (!fill_words(result, s))
	{
		ft_free_split(result);
		return (NULL);
	}
	return (result);
}
