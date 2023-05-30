/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   announcements.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/20 15:09:45 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/05/30 12:02:53 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_up(pthread_mutex_t p_lock, t_philo *philo, pthread_mutex_t *fork)
{
	long long		curr_time;

	pthread_mutex_lock(fork);
	pthread_mutex_lock(&p_lock);
	curr_time = time_diff(philo->start_time);
	printf("%lld %d has taken a fork\n", curr_time, philo->id);
	pthread_mutex_unlock(&p_lock);
}

int	eat(pthread_mutex_t p_lock, t_philo *philo)
{
	struct timeval	tv;
	long long		curr_time;
	long long		elapsed_time;

	pthread_mutex_lock(&p_lock);
	if (philo->num_meals == 0)
		curr_time = time_diff(philo->start_time);
	else
		curr_time = time_diff(philo->curr_time);
	elapsed_time = time_diff(philo->start_time);
	if ((curr_time * 1000) > philo->info->time_to_die)
	{
		printf("%lld %d died\n", elapsed_time, philo->id);
		forks_down(philo);
		return (EXIT_FAILURE);
	}
	printf("%lld %d is eating\n", elapsed_time, philo->id);
	usleep(philo->info->time_to_eat);
	gettimeofday(&tv, NULL);
	philo->curr_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	pthread_mutex_unlock(&p_lock);
	return (EXIT_SUCCESS);
}

void	fork_down(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}

void	sleepy(pthread_mutex_t p_lock, t_philo *philo)
{
	long long		curr_time;

	pthread_mutex_lock(&p_lock);
	curr_time = time_diff(philo->start_time);
	printf("%lld %d is sleeping\n", curr_time, philo->id);
	usleep(philo->info->time_to_sleep);
	pthread_mutex_unlock(&p_lock);
}

void	think(pthread_mutex_t p_lock, t_philo *philo)
{
	long long	curr_time;

	pthread_mutex_lock(&p_lock);
	curr_time = time_diff(philo->start_time);
	printf("%lld %d is thinking\n", curr_time, philo->id);
	pthread_mutex_unlock(&p_lock);
}
