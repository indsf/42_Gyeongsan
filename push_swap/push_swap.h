/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:24:24 by inhlee            #+#    #+#             */
/*   Updated: 2025/07/20 03:42:30 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack_state
{
	int			*stack_a;
	int			*stack_b;
	int			*tail_a;
	int			*tail_b;
}				t_stack_state;

typedef struct s_chunk_info
{
	int			min;
	int			max;
	int			mid;

}				t_chunk_info;

typedef struct s_chunk_size
{
	int			size;
	int			chunk_size;
	int			chunk;
}				t_chunk_size;

int				ft_atoi_check(const char *str);
int				ft_split_size(char *str);
void			ft_free_split(char **split_arr);
char			**ft_split_all(int ac, char **str);
int			ft_double_check(int *arr, int size);
int				*ft_parse_input(int ac, char **av, int *size_out);
int				ft_isspace(char str);
int				ft_print_error(int num);
void			ft_free_split(char **split_arr);
int				ft_empty_check(char **arr);
int				ft_count_total_words(int ac, char **str);
void			quick_sort(int *stack_a, int start, int end);
void			ft_swap(int *a, int *b);
int				ft_chunk_size(t_stack_state *s);
int				*ft_sorted(int *stack_a, int *tail_a);
t_chunk_info	ft_get_value(int *sort, int size, int start, int chunk_size);
void			ft_stack_b_move(int *stack_a, int *stack_b, int *tail_a,
					int *tail_b);
int				ft_value_in_range(int *stack_a, int size, int min, int max);
void			ft_excute(t_stack_state *stack_info, t_chunk_info info);
void			chunk_sort(t_stack_state *stack_info);
void			ft_exe_rb(int index, int *stack_b, int *tail_b);
void			ft_exe_rrb(int index, int *stack_b, int *tail_b);
void			sa(int *stack_a, int *tail_a);
void			sb(int *stack_b, int *tail_b);
void			ss(int *stack_a, int *stack_b, int *tail_a, int *tail_b);
void			pa(int *stack_a, int *stack_b, int *tail_a, int *tail_b);
void			pb(int *stack_a, int *stack_b, int *tail_a, int *tail_b);
void			ra(int *stack_a, int *tail_a);
void			rb(int *stack_b, int *tail_b);
void			rr(int *stack_a, int *stack_b, int *tail_a, int *tail_b);
void			rra(int *stack_a, int *tail_a);
void			rrb(int *stack_b, int *tail_b);
void			rrr(int *stack_a, int *stack_b, int *tail_a, int *tail_b);
int				is_sort(int *stack_a, int *stack_b, int tail_a);
void			ft_sort_2(int *stack_a, int *tail_a);
void			ft_sort_3(int *stack_a, int *tail_a);
void			ft_sort_5(int *stack_a, int *stack_b, int *tail_a, int *tail_b);
int				find_min(int *stack, int size);
void			ft_min_max_check(int sign, long long result);
#endif