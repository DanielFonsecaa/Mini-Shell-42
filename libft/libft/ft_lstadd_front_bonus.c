/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:02:10 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 18:15:45 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
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
        return (1);
    }
    t_list *list = NULL;
    ft_lstadd_front(&list, node3);
    ft_lstadd_front(&list, node2);
    ft_lstadd_front(&list, node1);
    print_list(list);
    free(node1);
    free(node2);
    free(node3);
    return 0;
}
*/
