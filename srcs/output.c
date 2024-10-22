/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:17:25 by qsomarri          #+#    #+#             */
/*   Updated: 2024/10/18 16:35:18 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}

void	philo_error(t_data *data, char *str)
{
	ft_putstr_fd(str, 2);
	if (data)
		free_philo_data(data);
}

void	print_msg(t_philo *philo, char *str)
{
	time_t	time;

	pthread_mutex_lock(&philo->data->write_lock);
	time = get_time() - philo->data->start_time;
	if (check_end_sim(philo->data))
	{
		pthread_mutex_unlock(&philo->data->write_lock);
		return ;
	}
	printf("%zu %zu %s\n", time, philo->index, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}
