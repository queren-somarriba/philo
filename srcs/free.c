/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:25:08 by qsomarri          #+#    #+#             */
/*   Updated: 2024/10/17 16:16:09 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo_data(t_data *data)
{
	size_t	i;

	i = -1;
	if (data)
	{
		if (data->fork_locks)
			free(data->fork_locks);
		if (data->philo)
		{
			while (++i < data->philo_nb)
			{
				if (data->philo[i])
					free(data->philo[i]);
			}
			free(data->philo);
		}
		free(data);
	}
}

void	free_mutex(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->fork_locks[i]);
		pthread_mutex_destroy(&data->philo[i]->meal_lock);
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->end_sim_lock);
}

int	join_and_free(t_data	*data)
{
	size_t	i;

	i = -1;
	while (++i < data->philo_nb)
	{
		if (pthread_join(data->philo[i]->thread, NULL))
			return (philo_error(data, "pthread_join error\n"), 1);
	}
	if (data->philo_nb > 1)
	{
		if (pthread_join(data->monitor, NULL))
			return (philo_error(data, "pthread_join error\n"), 1);
	}
	free_mutex(data);
	free_philo_data(data);
	return (0);
}
