/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/20 15:25:06 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/06/02 17:03:54 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_diff(long long tv1)
{
	struct timeval	tv;
	long long		curr_time;

	gettimeofday(&tv, NULL);
	curr_time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000) - tv1;
	return (curr_time);
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
		usleep(75);
	}
}
