/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:47:47 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/09 11:01:07 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lstadd_back_philo(t_philo **lst, t_philo *new_lst)
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
	tmp = lstlast_philo(*lst);
	if (!tmp)
		*lst = new_lst;
	else
		tmp->next = new_lst;
}

void	lstadd_back_fork(t_fork **lst, t_fork *new_lst)
{
	t_fork	*tmp;

	if (!lst || !new_lst)
	{
		if (!lst)
			ft_printf("Argument lst is NULL in ft_lstadd_back() function.\n");
		if (!new_lst)
			ft_printf("Argument new is NULL in ft_lstadd_back() function.\n");
		return ;
	}
	tmp = lstlast_fork(*lst);
	if (!tmp)
		*lst = new_lst;
	else
		tmp->next = new_lst;
}