/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_funcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tijmendebruine <tijmendebruine@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 20:24:46 by tijmendebru   #+#    #+#                 */
/*   Updated: 2023/05/20 17:22:58 by tde-brui      ########   odam.nl         */
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

void	destroy_forks(pthread_mutex_t *forks, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
	}
}
