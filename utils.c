/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 09:57:40 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/05/20 17:19:06 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	minuscounter;
	int	result;

	i = 0;
	minuscounter = 0;
	result = 0;
	while ((str[i] < 14 && str[i] > 8) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			minuscounter++;
		i++;
	}
	while (str[i] < 58 && str[i] > 47)
	{
		result = (result * 10) + str[i] - 48;
		i++;
	}
	if (minuscounter % 2 == 1)
		result *= -1;
	return (result);
}

void	forks_up(pthread_mutex_t p_lock, t_philo *philo)
{
	fork_up(p_lock, philo, philo->left_fork);
	fork_up(p_lock, philo, philo->right_fork);
}

void	forks_down(t_philo *philo)
{
	fork_down(philo->left_fork);
	fork_down(philo->right_fork);
}
