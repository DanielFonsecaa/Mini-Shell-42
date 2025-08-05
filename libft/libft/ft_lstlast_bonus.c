/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:37:07 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 20:45:01 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
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
    char *content1 = "First Node";
    char *content2 = "Second Node";
    char *content3 = "Third Node";
    t_list *node1 = ft_lstnew(content1);
    t_list *node2 = ft_lstnew(content2);
    t_list *node3 = ft_lstnew(content3);

    if (!node1 || !node2 || !node3)
    {
        printf("Memory allocation failed\n");
        return (1);
    }
    t_list *list = NULL;
    ft_lstadd_front(&list, node3); 
    ft_lstadd_front(&list, node2); 
    ft_lstadd_front(&list, node1); 

    t_list *last_node = ft_lstlast(list);
    if (last_node)
        printf("The last node content: %s\n", (char *)last_node->content);
    free(node1);
    free(node2);
    free(node3);
    return 0;
}
*/
