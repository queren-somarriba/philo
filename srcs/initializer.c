/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:26:46 by qsomarri          #+#    #+#             */
/*   Updated: 2024/10/18 16:37:13 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	size_t			i;

	forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!forks)
		return (philo_error(data, "malloc error\n"), NULL);
	i = -1;
	while (++i < data->philo_nb)
	{
		if (pthread_mutex_init(&forks[i], 0))
			return (philo_error(data, "pthread_mutex_init error\n"), NULL);
	}
	return (forks);
}

static void	assign_forks(t_philo *philo)
{
	if ((philo->index) % 2 == 0)
	{
		philo->r_fork = philo->index - 1;
		philo->l_fork = (philo->index) % philo->data->philo_nb;
	}
	if ((philo->index) % 2)
	{
		philo->r_fork = (philo->index) % philo->data->philo_nb;
		philo->l_fork = philo->index - 1;
	}
}

static t_philo	**init_philo(t_data *data)
{
	t_philo	**philo;
	size_t	i;

	i = -1;
	philo = malloc(sizeof(t_philo) * data->philo_nb);
	if (!philo)
		return (NULL);
	while (++i < data->philo_nb)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (philo_error(data, "malloc error\n"), NULL);
		philo[i]->data = data;
		philo[i]->index = i + 1;
		philo[i]->meal_count = 0;
		if (pthread_mutex_init(&philo[i]->meal_lock, 0))
			return (philo_error(data, "pthread_mutex_init error\n"), NULL);
		assign_forks(philo[i]);
	}
	return (philo);
}

static int	init_mutex(t_data *data)
{
	data->fork_locks = init_forks(data);
	if (!data->fork_locks)
		return (1);
	if (pthread_mutex_init(&data->end_sim_lock, 0))
		return (philo_error(data, "pthread_mutex_init error\n"), 1);
	if (pthread_mutex_init(&data->write_lock, 0))
		return (philo_error(data, "pthread_mutex_init error\n"), 1);
	return (0);
}

t_data	*init_data(char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("malloc error\n", 2), NULL);
	data->philo_nb = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	data->max_meal = -1;
	data->end_sim = 0;
	if (av[5])
		data->max_meal = ft_atol(av[5]);
	data->philo = init_philo(data);
	if (!data->philo)
		return (NULL);
	if (init_mutex(data))
		return (NULL);
	return (data);
}
