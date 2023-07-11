/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 09:57:40 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/07/11 15:06:33 by tde-brui      ########   odam.nl         */
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

int	ft_strncmp(const char *str1, const char *str2, size_t size)
{
	unsigned long	i;
	unsigned char	*ptr;
	unsigned char	*ptr1;

	i = 0;
	ptr = (unsigned char *)str1;
	if (!ptr)
		return (0);
	ptr1 = (unsigned char *)str2;
	if (!ptr1)
		return (0);
	while (i < size)
	{
		if (ptr[i] != ptr1[i] || ptr[i] == '\0' || ptr1[i] == '\0')
			return (ptr[i] - ptr1[i]);
		i++;
	}
	return (0);
}

int	input_val(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc != 6 && argc != 5)
		return (EXIT_FAILURE);
	if (!ft_strncmp("0", argv[1], 3))
		return (EXIT_FAILURE);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	print_message(t_philo *philo, long long time, char *msg)
{
	if (!has_died(philo))
		printf("%lld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->info->p_lock);
}
