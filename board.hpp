/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 17:52:53 by fel-hita          #+#    #+#             */
/*   Updated: 2018/11/22 14:07:03 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "defs.hpp"
# include "block.hpp"

class Board
{
	public:
		int		cells[BOARD_SIZE][BOARD_SIZE] = {{0}};
		std::string identifier;
		std::string referrer;
		std::vector<Block> blocks;
		Board();
		~Board();
		Board(const Board &board);
		SDL_Rect		pos;
		SDL_Texture		*img;
		void			ft_fill_board(std::ifstream &file);
		void			ft_export_board(std::ofstream &file);
		std::string		ft_get_hash(void);
		void			ft_init(SDL_Renderer *renderer);
		void			ft_print(const std::string message = "");
		void			ft_draw(SDL_Renderer *renderer);
		bool			ft_can_move(Block block, int direction);
		void			ft_move_block(int index, int direction);
		bool			ft_is_completed(void);
		bool			operator<(const Board &board) const { \
			return (bool) (identifier.compare(board.identifier));
		}

	private:
		void			ft_insert(Block block, int id_to_insert = -1);
		Block			ft_get_target_block(void);
		bool			ft_is_movable(int row, int column);
		bool			ft_is_on_board(int row, int column);
		bool			ft_is_empty(int row, int column);
};
