/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   announcements.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/20 15:09:45 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/06/08 21:52:22 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_up(t_philo *philo, pthread_mutex_t *fork)
{
	long long		curr_time;

	pthread_mutex_lock(fork);
	pthread_mutex_lock(&philo->info->p_lock);
	curr_time = time_diff(philo->info->start_time);
	if (!philo->info->died)
		print_message(philo, curr_time, "has taken a fork");
}

int	eat(t_philo *philo)
{
	struct timeval	tv;
	long long		curr_time;
	long long		elapsed_time;

	pthread_mutex_lock(&philo->info->p_lock);
	if (philo->num_meals == 0)
		curr_time = time_diff(philo->info->start_time);
	else
		curr_time = time_diff(philo->curr_time);
	elapsed_time = time_diff(philo->info->start_time);
	if ((curr_time * 1000) > philo->info->time_to_die)
	{
		if (!philo->info->died)
			print_message(philo, elapsed_time, "has died");
		pthread_mutex_lock(&philo->info->death_lock);
		philo->info->died = true;
		pthread_mutex_unlock(&philo->info->death_lock);
		forks_down(philo);
		return (EXIT_FAILURE);
	}
	if (!philo->info->died)
		print_message(philo, elapsed_time, "is eating");
	gettimeofday(&tv, NULL);
	philo->curr_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	ft_usleep(philo->info->time_to_eat);
	return (EXIT_SUCCESS);
}

void	fork_down(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}

void	sleepy(t_philo *philo)
{
	long long		curr_time;

	pthread_mutex_lock(&philo->info->p_lock);
	curr_time = time_diff(philo->info->start_time);
	if (!philo->info->died)
		print_message(philo, curr_time, "is sleeping");
	ft_usleep(philo->info->time_to_sleep);
}

void	think(t_philo *philo)
{
	long long	curr_time;

	pthread_mutex_lock(&philo->info->p_lock);
	curr_time = time_diff(philo->info->start_time);
	if (!philo->info->died)
		print_message(philo, curr_time, "is thinking");
}
