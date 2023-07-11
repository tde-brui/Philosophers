/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 09:49:16 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/07/11 16:17:26 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct info{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	bool			died;
	long long		start_time;
	int				finished;
	pthread_mutex_t	p_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	monitor_lock;
}t_info;

typedef struct philo{
	int				id;
	int				num_meals;
	int				num_of_philos;
	int				compiled_time;
	long long		curr_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
}t_philo;

//announcement functions
void		fork_up(t_philo *philo, pthread_mutex_t *fork);
void		fork_down(pthread_mutex_t *fork);
void		eat(t_philo *philo);
void		sleepy( t_philo *philo);
void		think(t_philo *philo);

//one philo thread function
void		*onephilo(void *arg);

//time functions
void		ft_usleep(int ms);
long long	time_diff(t_philo *philo);
int			check_died(t_philo *philo, int i);

//util functions
void		print_message(t_philo *philo, long long time, char *msg);
int			ft_atoi(const char *str);
int			input_val(int argc, char **argv);
void		free_philos_and_forks(t_philo *philo, pthread_mutex_t *forks);
void		free_everything(t_philo *philo, pthread_mutex_t *forks);
bool		has_died(t_philo *philo);
int			compare_meals(t_philo *philo);
int			compare_eat_num(t_philo *philo);
int			compare_eat_times(t_philo *philo, long long death_time, int i);
void		add_to_finished(t_philo *philo);
void		add_to_meals(t_philo *philo);

//mutex functions
void		init_forks(pthread_mutex_t *forks, int num_of_philos);
void		destroy_mutexes(t_philo *philo, int num_of_philos);
int			detach_threads(int i, pthread_t *threads);
void		forks_down(t_philo *philo);
void		forks_up(t_philo *philo);

//monitoring script
void		monitoring(t_philo *philo, int num_of_philos);

#endif