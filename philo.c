/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vess <vess@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:54:43 by vess              #+#    #+#             */
/*   Updated: 2022/05/01 23:04:24 by vess             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pickup_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	print_msg(philo, MSG_FORK);
	pthread_mutex_lock(philo->left);
	print_msg(philo, MSG_FORK);
}

static void	sleeping(t_philo *philo)
{
	print_msg(philo, MSG_SLP);
	usleep(philo->info->time_to_sleep * 1000);
}

static void	thinking(t_philo *philo)
{
	print_msg(philo, MSG_THK);
}

static void	eating(t_philo *philo)
{
	t_info	*tab;

	tab = philo->info;
	pthread_mutex_unlock(&tab->finish_mutex);
	pthread_mutex_lock(&tab->finish_mutex);
	philo->num_of_eat += 1;
	print_msg(philo, MSG_EAT);
	philo->last_time_to_eat = get_time();
	if (philo->num_of_eat == philo->info->num_of_must_eat)
		philo->info->num_of_eat_finish_philo += 1;
	pthread_mutex_unlock(&philo->info->finish_mutex);
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&philo->check_mutex);
}

void	*philo(void *av)
{
	t_philo	*philo;

	philo = av;
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->eat / 10);
	while (!check_death(philo, 0))
	{
		pthread_create(&philo->thread_death, NULL, is_dead, data);
		
		pthread_detach(philo->thread_death);
	}
	return (NULL);
}
