/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/20 15:25:06 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/07/06 19:55:56 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_diff(t_philo *philo)
{
	struct timeval	tv;
	long long		curr_t;

	gettimeofday(&tv, NULL);
	curr_t = (tv.tv_usec / 1000) + (tv.tv_sec * 1000) - philo->info->start_time;
	return (curr_t);
}

void	ft_usleep(int ms)
{
	struct timeval	tv_start;
	struct timeval	tv_curr;
	long long		s_time;
	long long		curr;

	gettimeofday(&tv_start, NULL);
	s_time = (tv_start.tv_sec * 1000) + (tv_start.tv_usec / 1000);
	curr = 0;
	while (curr * 1000 < ms)
	{
		gettimeofday(&tv_curr, NULL);
		curr = ((tv_curr.tv_sec * 1000) + (tv_curr.tv_usec / 1000)) - s_time;
		usleep(300);
	}
}
