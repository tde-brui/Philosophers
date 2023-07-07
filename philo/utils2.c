/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 19:55:03 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/07/07 17:01:04 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	compare_meals(t_philo *philo)
{
	pthread_mutex_lock (&philo->info->monitor_lock);
	if ((philo->num_meals != philo->info->max_meals))
	{
		pthread_mutex_unlock(&philo->info->monitor_lock);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->info->monitor_lock);
	return (EXIT_SUCCESS);
}

int	compare_eat_times(t_philo *philo, long long death_time, int i)
{
	pthread_mutex_lock(&philo->info->monitor_lock);
	if ((death_time - philo[i].curr_time) > philo->info->time_to_die)
	{
		pthread_mutex_unlock(&philo->info->monitor_lock);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->info->monitor_lock);
	return (EXIT_SUCCESS);
}

int	compare_eat_num(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->monitor_lock);
	if (philo->num_meals > 0)
	{
		pthread_mutex_unlock(&philo->info->monitor_lock);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->info->monitor_lock);
	return (EXIT_SUCCESS);
}

bool	has_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death_lock);
	if (philo->info->died)
	{
		pthread_mutex_unlock(&philo->info->death_lock);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->info->death_lock);
	return (EXIT_SUCCESS);
}

void	add_to_finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->monitor_lock);
	philo->info->finished++;
	pthread_mutex_unlock(&philo->info->monitor_lock);
}
