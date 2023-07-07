/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 15:17:09 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/07/07 17:36:50 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_died(t_philo *philo, int i)
{
	long long	death_time;

	death_time = time_diff(philo);
	if (compare_eat_times(philo, death_time, i))
	{
		pthread_mutex_lock(&philo->info->p_lock);
		if (!has_died(philo))
		{
			printf("%lld %d has died\n", death_time, philo[i].id);
			pthread_mutex_unlock(&philo->info->p_lock);
		}
		else
			pthread_mutex_unlock(&philo->info->p_lock);
		pthread_mutex_lock(&philo->info->death_lock);
		philo->info->died = true;
		pthread_mutex_unlock(&philo->info->death_lock);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	monitoring(t_philo *philo, int num_of_philos)
{
	int		i;

	i = 0;
	while (1)
	{
		if (philo->info->finished == num_of_philos)
			break ;
		if (check_died(philo, i))
			break ;
		i++;
		if (i >= num_of_philos)
			i = 0;
	}
}
