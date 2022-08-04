/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 03:53:33 by tliot             #+#    #+#             */
/*   Updated: 2022/08/04 09:48:14 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <inttypes.h>
# include <sys/time.h>
# include <time.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	int				count_miam_miam;
	bool			done;
	int				left_fourch_id;
	int				right_fourch_id;
	uint64_t		last_time_miam_miam;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int					nbr_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	uint64_t			time_start;
	int					nbr_eat;
	int					count_done;
	bool				running;
	pthread_mutex_t		m_time_miam_miam;
	pthread_mutex_t		m_done;
	pthread_mutex_t		m_done_count;
	pthread_mutex_t		m_running;
	pthread_mutex_t		*fourch;
	t_philo				*philo;
}						t_data;

/// FT_ACTION.C ///

void		philo_miam_miam(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
int			take_fourch(t_philo *philo);
void		drop_fourch(t_philo *philo);


/// MAIN.C
int mutex_check_running(t_philo *philo);

/// FT_FREE.C ///

void		fr_all(t_data *data);

/// FT_INIT.C ///

int			init_arg(t_data *data, char **argv);
int			init_philo(t_data *data);
int			init_mutex(t_data *data);

/// FT_UTILS.C ///

uint64_t	ft_time_ms(void);
void		slipe(uint64_t sleep_ms, t_philo *philo);
void		print_philo(t_philo *philo, char *str);
int			ft_atoi(const char *str);
int			ft_verif_argument(char *str);

#endif