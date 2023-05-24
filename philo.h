/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 09:49:16 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/05/24 13:44:38 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
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
	pthread_mutex_t	p_lock;
	long long		start_time;
	long long		curr_time;
}t_philo;

int			ft_atoi(const char *str);
void		init_forks(pthread_mutex_t *forks, int num_of_philos);
void		destroy_forks(pthread_mutex_t *forks, int num_of_philos);
void		fork_up(pthread_mutex_t *p_lock, t_philo *philo, pthread_mutex_t *fork);
void		fork_down(pthread_mutex_t *fork);
int			eat(pthread_mutex_t *p_lock, t_philo *philo);
void		sleepy(pthread_mutex_t p_lock, t_philo *philo);
long long	time_diff(long long tv1);
void		forks_down(t_philo *philo);
void		forks_up(pthread_mutex_t *p_lock, t_philo *philo);

#endif