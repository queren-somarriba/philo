/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:16:41 by qsomarri          #+#    #+#             */
/*   Updated: 2024/10/18 16:29:14 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	time_t			start_time;
	size_t			philo_nb;
	pthread_t		monitor;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				max_meal;
	int				end_sim;
	pthread_mutex_t	end_sim_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philo			**philo;
}	t_data;

typedef struct s_philo
{
	pthread_t			thread;
	size_t				index;
	size_t				meal_count;
	size_t				r_fork;
	size_t				l_fork;
	pthread_mutex_t		meal_lock;
	time_t				last_meal;
	t_data				*data;
}	t_philo;

/*	free.c	 */
void				free_philo_data(t_data *data);
void				free_mutex(t_data *data);
int					join_and_free(t_data	*data);

/*	initializer.c	*/
t_data				*init_data(char **av);

/*	monitor.c	*/
void				*monitor_thread(void *data);
int					check_end_sim(t_data *data);

/*	output.c	*/
void				philo_error(t_data *data, char *str);
void				ft_putstr_fd(char *s, int fd);
void				print_msg(t_philo *philo, char *str);

/*	philo_utils.c	*/
int					check_digits(char *str);
long				ft_atol(const char *nptr);
time_t				get_time(void);
void				philo_sleep(t_data *data, time_t sleep_time);

/*	routine.c	*/
void				*routine(void *data);

#endif
