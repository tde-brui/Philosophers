/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/20 15:25:06 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/05/20 16:01:02 by tde-brui      ########   odam.nl         */
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
