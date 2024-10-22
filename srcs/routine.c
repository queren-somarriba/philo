/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:18:00 by qsomarri          #+#    #+#             */
/*   Updated: 2024/10/22 16:48:25 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	time_to_think_check(t_data *data, time_t philo_last_meal)
{
	if (philo_last_meal - data->start_time < (data->time_to_die
			- data->time_to_eat - data->time_to_sleep) / 2)
		return (1);
	return (0);
}

static void	eat_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_locks[philo->r_fork]);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->fork_locks[philo->l_fork]);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	philo_sleep(philo->data, philo->data->time_to_eat);
	if (!check_end_sim(philo->data))
	{
		pthread_mutex_lock(&philo->meal_lock);
		philo->meal_count += 1;
		pthread_mutex_unlock(&philo->meal_lock);
	}
	pthread_mutex_unlock(&philo->data->fork_locks[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->fork_locks[philo->r_fork]);
	print_msg(philo, "is sleeping");
	philo_sleep(philo->data, philo->data->time_to_sleep);
	print_msg(philo, "is thinking");
	if (time_to_think_check(philo->data, philo->last_meal))
		philo_sleep(philo->data, (philo->data->time_to_die
				- philo->data->time_to_eat - philo->data-> time_to_sleep) / 3);
	else
		philo_sleep(philo->data, 1);
}

static void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_locks[philo->r_fork]);
	print_msg(philo, "has taken a fork");
	philo_sleep(philo->data, philo->data->time_to_die);
	print_msg(philo, "died");
	pthread_mutex_unlock(&philo->data->fork_locks[philo->r_fork]);
	return (NULL);
}

void	*routine(void *philo)
{
	t_philo	*philo_cpy;

	philo_cpy = (t_philo *)philo;
	pthread_mutex_lock(&philo_cpy->meal_lock);
	philo_cpy->last_meal = philo_cpy->data->start_time;
	pthread_mutex_unlock(&philo_cpy->meal_lock);
	while (get_time() < philo_cpy->data->start_time)
		continue ;
	if (philo_cpy->data->philo_nb == 1)
		return (one_philo(philo_cpy));
	if (philo_cpy->index % 2)
		philo_sleep(philo_cpy->data, philo_cpy->data->time_to_eat);
	while (!check_end_sim(philo_cpy->data))
		eat_sleep_think(philo_cpy);
	return (NULL);
}
