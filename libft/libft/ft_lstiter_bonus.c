/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonusc                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:19:52 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/11 11:24:07 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void	to_uppercase(void *content)
{
	char	*str = (char *)content;
	int		i = 0;

	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
}

void print_list(t_list *list)
{
    while (list)
    {
        printf("Node content: %s\n", (char *)list->content);
        list = list->next;
    }
}

int main()
{
    char *content1 = ft_strdup("First Node");
    char *content2 = ft_strdup("Second Node");
    char *content3 = ft_strdup("Third Node");

    t_list *node1 = ft_lstnew(content1);
    t_list *node2 = ft_lstnew(content2);
    t_list *node3 = ft_lstnew(content3);

    if (!node1 || !node2 || !node3)
        return (1);

    t_list *list = NULL;
    ft_lstadd_front(&list, node3);
    ft_lstadd_front(&list, node2);
    ft_lstadd_front(&list, node1);

    printf("Before ft_lstiter:\n");
    print_list(list);

    ft_lstiter(list, to_uppercase);

    printf("\nAfter ft_lstiter:\n");
    print_list(list);

    free(content1);
    free(content2);
    free(content3);
    free(node1);
    free(node2);
    free(node3);

    return 0;
}
*/