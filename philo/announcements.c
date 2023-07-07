/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   announcements.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/20 15:09:45 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/07/07 16:02:04 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks_up(t_philo *philo)
{
	fork_up(philo, philo->left_fork);
	fork_up(philo, philo->right_fork);
}

void	fork_up(t_philo *philo, pthread_mutex_t *fork)
{
	long long		curr_time;

	pthread_mutex_lock(fork);
	pthread_mutex_lock(&philo->info->p_lock);
	curr_time = time_diff(philo);
	print_message(philo, curr_time, "has taken a fork");
}

void	eat(t_philo *philo)
{
	long long		elapsed_time;

	pthread_mutex_lock(&philo->info->p_lock);
	elapsed_time = time_diff(philo);
	print_message(philo, elapsed_time, "is eating");
	pthread_mutex_lock(&philo->info->monitor_lock);
	philo->curr_time = time_diff(philo);
	pthread_mutex_unlock(&philo->info->monitor_lock);
	ft_usleep(philo->info->time_to_eat);
}

void	sleepy(t_philo *philo)
{
	long long		curr_time;

	pthread_mutex_lock(&philo->info->p_lock);
	curr_time = time_diff(philo);
	print_message(philo, curr_time, "is sleeping");
	ft_usleep(philo->info->time_to_sleep);
}

void	think(t_philo *philo)
{
	long long	curr_time;

	pthread_mutex_lock(&philo->info->p_lock);
	curr_time = time_diff(philo);
	print_message(philo, curr_time, "is thinking");
}
