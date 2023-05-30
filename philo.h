/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 09:49:16 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/05/30 12:24:47 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct info{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
}t_info;

typedef struct philo{
	int				id;
	int				num_meals;
	int				num_of_philos;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		start_time;
	long long		curr_time;
	t_info			*info;
}t_philo;


int			ft_atoi(const char *str);
void		init_forks(pthread_mutex_t *forks, int num_of_philos);
void		destroy_forks(pthread_mutex_t *forks, int num_of_philos);
void		fork_up(pthread_mutex_t p_lock, t_philo *philo, pthread_mutex_t *fork);
void		fork_down(pthread_mutex_t *fork);
int			eat(pthread_mutex_t p_lock, t_philo *philo);
void		sleepy(pthread_mutex_t p_lock, t_philo *philo);
long long	time_diff(long long tv1);
void		forks_down(t_philo *philo);
void		forks_up(pthread_mutex_t p_lock, t_philo *philo);
int			input_val(int argc, char **argv);
void		free_philos_and_forks(t_philo *philo, pthread_mutex_t *forks);
void		think(pthread_mutex_t p_lock, t_philo *philo);
void		free_everything(t_philo *philo, pthread_mutex_t *forks);

#endif