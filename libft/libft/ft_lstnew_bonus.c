/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:29:47 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 16:46:06 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
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
    char *content1 = "Hello, World!";
    char *content2 = "Linked List Test";

    t_list *node1 = ft_lstnew(content1);
    t_list *node2 = ft_lstnew(content2);
    if (!node1 || !node2)
    {
        printf("Memory allocation failed\n");
        return (1);
    }
    node1->next = node2;
    print_list(node1);
    free(node1);
    free(node2);
    return 0;
}
*/
