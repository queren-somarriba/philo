/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:16:08 by qsomarri          #+#    #+#             */
/*   Updated: 2024/10/18 16:35:07 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_end_sim(t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->end_sim_lock);
	if (data->end_sim == 1)
		res = 1;
	pthread_mutex_unlock(&data->end_sim_lock);
	return (res);
}

static int	check_dead_philo(t_philo *philo)
{
	time_t	time;

	time = get_time();
	if ((time - philo->last_meal) >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->end_sim_lock);
		philo->data->end_sim = 1;
		pthread_mutex_unlock(&philo->data->end_sim_lock);
		pthread_mutex_lock(&philo->data->write_lock);
		time = get_time() - philo->data->start_time;
		printf("%zu %zu died\n", time, philo->index);
		pthread_mutex_unlock(&philo->data->write_lock);
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	return (0);
}

static int	check_monitor(t_data *data)
{
	size_t	i;
	int		all_philo_full;

	all_philo_full = 1;
	i = -1;
	while (++i < data->philo_nb)
	{
		pthread_mutex_lock(&data->philo[i]->meal_lock);
		if (check_dead_philo(data->philo[i]))
			return (1);
		if (data->max_meal != -1)
			if (data->philo[i]->meal_count < (size_t)data->max_meal)
				all_philo_full = 0;
		pthread_mutex_unlock(&data->philo[i]->meal_lock);
	}
	if (data->max_meal != -1 && all_philo_full == 1)
	{
		pthread_mutex_lock(&data->end_sim_lock);
		data->end_sim = 1;
		pthread_mutex_unlock(&data->end_sim_lock);
		return (1);
	}
	return (0);
}

void	*monitor_thread(void *data)
{
	t_data			*data_cpy;

	data_cpy = (t_data *)data;
	pthread_mutex_lock(&data_cpy->end_sim_lock);
	data_cpy->end_sim = 0;
	pthread_mutex_unlock(&data_cpy->end_sim_lock);
	while (get_time() < data_cpy->start_time)
		continue ;
	while (1)
	{
		if (check_monitor(data_cpy))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
