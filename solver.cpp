/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 20:10:47 by fel-hita          #+#    #+#             */
/*   Updated: 2018/11/22 14:07:29 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.hpp"

Solver::Solver(Board board)
{
	this->boards.push_back(board);
}

Solver::Solver(){}

void	Solver::ft_construct_solution_steps(Board board)
{
	this->boards.clear();

	std::string last_reference = board.referrer;
	this->steps.push_back(board);

	while (last_reference.length())
	{
		this->steps.push_back(this->past_steps[last_reference]);
		last_reference = this->past_steps[last_reference].referrer;
	}
	this->number_of_nodes = this->past_steps.size();
	this->steps.push_back((this->past_steps.begin())->second);
	this->past_steps.clear();
	return;
}

Board	Solver::ft_create_moved_instance(Board board, int block_index, int direction)
{
	Board 	temp_board;

	temp_board = board;
	temp_board.identifier = board.ft_get_hash();
	temp_board.referrer = board.identifier;

	temp_board.ft_move_block(block_index, direction);
	return (temp_board);
}

void	Solver::ft_solve(int algorithm)
{
	Board board;

	while (!this->boards.empty())
	{
		board = this->boards.front();
		this->boards.pop_front();

		if (board.ft_is_completed())
		{
			this->boards.clear();
			this->ft_construct_solution_steps(board);
			return;
		}
		else
		{
			Board temp_board;
			for (size_t i = 0; i < board.blocks.size(); ++i)
			{
				if (board.blocks[i].ft_is_horizontal())
				{
					for (int j = LEFT; j <= RIGHT; ++j)
					{
						if (board.ft_can_move(board.blocks[i], j))
						{
							temp_board = this->ft_create_moved_instance(board, i, j);
							if (this->past_steps.find(temp_board.identifier) == this->past_steps.end())
							{
								if (algorithm == BFS)
									this->boards.push_back(temp_board);
								else
									this->boards.push_front(temp_board);
							}
						}
					}
				}
				else
				{
					for (int j = UP; j <= DOWN; ++j)
					{
						if (board.ft_can_move(board.blocks[i], j))
						{
							temp_board = this->ft_create_moved_instance(board, i, j);
							if (this->past_steps.find(temp_board.identifier) == this->past_steps.end())
							{
								if (algorithm == BFS)
									this->boards.push_back(temp_board);
								else
									this->boards.push_front(temp_board);
							}
						}
					}
				}
			}
		}
	this->past_steps[board.identifier] = board;
	}
}
