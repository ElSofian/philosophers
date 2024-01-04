/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:47:47 by soelalou          #+#    #+#             */
/*   Updated: 2023/12/27 15:07:30 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lstadd_back(t_philo **lst, t_philo *new_lst)
{
	t_philo	*tmp;

	if (!lst || !new_lst)
	{
		if (!lst)
			ft_printf("Argument lst is NULL in ft_lstadd_back() function.\n");
		if (!new_lst)
			ft_printf("Argument new is NULL in ft_lstadd_back() function.\n");
		return ;
	}
	tmp = lstlast(*lst);
	if (!tmp)
		*lst = new_lst;
	else
		tmp->next = new_lst;
}
