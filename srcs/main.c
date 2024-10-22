/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:17:06 by qsomarri          #+#    #+#             */
/*   Updated: 2024/10/17 19:04:59 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_argv(int argc, char **argv)
{
	int	i;
	int	nb;

	i = 0;
	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("Error: Invalid number of argumments!\n", 2), 1);
	while (++i < argc)
	{
		if (check_digits(argv[i]))
			return (ft_putstr_fd("Error: Invalid argumments!\n", 2), 1);
		nb = ft_atol(argv[i]);
		if (i == 1 && (nb <= 0 || nb > 200))
			return (ft_putstr_fd("Error: Invalid argumments!\n", 2), 1);
		if (i != 1 && nb <= 0)
			return (ft_putstr_fd("Error: Invalid argumments!\n", 2), 1);
	}
	return (0);
}

static int	thread_init(t_data *data)
{
	size_t	i;

	data->start_time = get_time() + (data->philo_nb * 10);
	i = -1;
	while (++i < data->philo_nb)
	{
		if (pthread_create(&data->philo[i]->thread, NULL,
				&routine, data->philo[i]))
			return (philo_error(data, "pthread_create error\n"), 1);
	}
	if (data->philo_nb > 1)
	{
		if (pthread_create(&data->monitor, NULL,
				&monitor_thread, data))
			return (philo_error(data, "pthread_create error\n"), 1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (check_argv(argc, argv))
		return (EXIT_FAILURE);
	data = init_data(argv);
	if (!data)
		return (EXIT_FAILURE);
	if (thread_init(data))
		return (EXIT_FAILURE);
	if (join_and_free(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
