/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 15:05:51 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/07/11 16:16:55 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_everything(t_philo *philo, pthread_mutex_t *forks)
{
	free(philo->info);
	free(philo);
	free(forks);
}

void	free_philos_and_forks(t_philo *philo, pthread_mutex_t *forks)
{
	free(philo);
	free(forks);
}

void	*onephilo(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	fork_up(philo, philo->left_fork);
	usleep(philo->info->time_to_die);
	return (EXIT_SUCCESS);
}
