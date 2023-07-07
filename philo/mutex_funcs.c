/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_funcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tijmendebruine <tijmendebruine@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 20:24:46 by tijmendebru   #+#    #+#                 */
/*   Updated: 2023/07/07 15:29:49 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(pthread_mutex_t *forks, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

int	detach_threads(int i, pthread_t *threads)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_detach(threads[j]);
		j++;
	}
	free(threads);
	return (1);
}

void	destroy_mutexes(t_philo *philo, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_destroy(philo->left_fork);
		i++;
	}
	pthread_mutex_destroy(&philo->info->p_lock);
}

void	forks_down(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	add_to_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->monitor_lock);
	philo->num_meals++;
	pthread_mutex_unlock(&philo->info->monitor_lock);
}
