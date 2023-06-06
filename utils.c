/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 09:57:40 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/06/06 14:41:40 by tde-brui      ########   odam.nl         */
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

int	input_val(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc != 6)
	{
		printf("This program takes 5 arguments\n");
		return (EXIT_FAILURE);
	}
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Arguments can only consist of digits\n");
				return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

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

void	print_message(t_philo *philo, long long time, char *msg)
{
	pthread_mutex_lock(&philo->info->p_lock);
	printf("%lld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->info->p_lock);
}
