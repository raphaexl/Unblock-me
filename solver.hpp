/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:24:23 by fel-hita          #+#    #+#             */
/*   Updated: 2018/11/20 12:22:49 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "defs.hpp"
# include "board.hpp"

class Solver
{
	public:
		Solver();
		Solver(const Board board);

		unsigned long number_of_nodes = 0;
		std::map<std::string, Board> past_steps;
		std::deque<Board> boards;
		std::vector<Board> steps;

		void	ft_solve(int algorithm);

	private:
		void	ft_construct_solution_steps(Board board);

		Board ft_create_moved_instance(Board board, int block_index, int direction);
};
