/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 09:49:16 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/05/17 21:40:45 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <time.h>
# include <unistd.h>

typedef struct philo_info{
	int				id;
	int				num_meals;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}t_philo;

int		ft_atoi(const char *str);
void	init_forks(pthread_mutex_t *forks, int num_of_philos);
void	destroy_forks(pthread_mutex_t *forks, int num_of_philos);


#endif