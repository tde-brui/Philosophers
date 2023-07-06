/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 15:17:09 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/07/06 20:28:02 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_finished(t_philo *philo, unsigned	int i)
{
	pthread_mutex_lock(&philo->info->monitor_lock);
	if (philo[i].num_meals == philo->info->max_meals - 1)
	{
		philo[i].num_meals++;
		philo->info->finished++;
	}
	pthread_mutex_unlock(&philo->info->monitor_lock);
}

int	check_died(t_philo *philo, int i)
{
	long long	death_time;

	death_time = time_diff(philo);
	if (compare_eat_times(philo, death_time, i))
	{
		pthread_mutex_lock(&philo->info->p_lock);
		print_message(philo, death_time, "has died");
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
		check_finished(philo, i);
		if (philo->info->finished == num_of_philos)
			break ;
		if (check_died(philo, i))
			break ;
		i++;
		if (i >= num_of_philos)
			i = 0;
	}
}
