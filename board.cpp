/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:31:07 by fel-hita          #+#    #+#             */
/*   Updated: 2018/11/22 18:50:39 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "board.hpp"

Board::Board(const Board &board)
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			this->cells[i][j] = board.cells[i][j];
	this->identifier = board.identifier;
	this->referrer = board.referrer;
	this->blocks = board.blocks;
}

Board::Board()
{
	this->identifier = std::string();
	this->referrer = std::string();
}

void	Board::ft_init(SDL_Renderer *renderer)
{
	this->pos.x = 0;
	this->pos.y = 0;
	SDL_Surface *surf = SDL_LoadBMP("boardd.bmp");
   	this->img = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_QueryTexture(this->img, nullptr, nullptr, &this->pos.w, &this->pos.h);
	SDL_FreeSurface(surf),surf = nullptr;
	for (std::vector<Block>::iterator it = blocks.begin(); it != blocks.end(); it++)
	{
		it->ft_init(renderer);
	}
}

void	Board::ft_fill_board(std::ifstream &file)
{
	int		row, column, length;
	int		id = 1;
	char 	direction;
	Block	temp_block;
	while (file >> row >> column >> length >> direction)
	{
		temp_block = Block(id++, row - 1, column - 1, length, direction);
		this->blocks.push_back(temp_block);
		this->ft_insert(temp_block);
	}
}

void	Board::ft_print(const std::string mes)
{
	ft_print_separator();
	pp(mes);
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			std::cout<<cells[i][j]<<' ';
		}
		std::cout<<std::endl;
	}
	ft_print_separator();
}

void	Board::ft_draw(SDL_Renderer *renderer)
{
	SDL_Rect src = {0, 0, 700, 1000};
	if (!this->img || pos.x != pos.y || pos.w != 700 || pos.h != 1000)
		ft_init(renderer);
	ft_render_draw_img(renderer, this->img, 0, 0, &src);
	for (std::vector<Block>::iterator it = blocks.begin(); it != blocks.end(); it++)
	{
		it->ft_draw(renderer);
	}
}

bool	Board::ft_can_move(Block block, int direction)
{
	bool		can_move = false;
	int		 	row = block.row;
	int			col = block.col;
	int			len = block.len;

	if (block.ft_is_horizontal())
	{
		switch(direction)
		{
			case LEFT:
				if (ft_is_movable(row, col - 1))
					can_move = true;
				break;
			case RIGHT:
				if (ft_is_movable(row, col + len))
					can_move = true;
				break;
			default:
				break;
		}
	}
	else
	{
		switch(direction)
		{
			case UP:
				if (ft_is_movable(row - len, col))
					can_move = true;
				break;
			case DOWN:
				if (ft_is_movable(row + 1, col))
					can_move = true;
				break;
			default:
				break;
		}
	}
	return (can_move);
}

void	Board::ft_move_block(int index, int direction)
{
	this->ft_insert(this->blocks[index], 0);
	this->blocks[index].ft_move(direction);
	this->ft_insert(this->blocks[index]);
}

bool	Board::ft_is_completed(void)
{
	Block block_to_save = this->ft_get_target_block();
	int	  hero_index;
	hero_index = block_to_save.col + block_to_save.len;
	for (int i = hero_index; i < BOARD_SIZE; ++i)
	{
		if (!this->ft_is_empty(block_to_save.row, i))
			return (false);
	}
	return (true);
}

Block	Board::ft_get_target_block(void)
{
	return (this->blocks.front());
}

bool	Board::ft_is_movable(int row, int col)
{
	return (this->ft_is_empty(row, col) && this->ft_is_on_board(row, col));
}

bool	Board::ft_is_empty(int row, int col)
{
	return (this->cells[row][col] == 0);
}

bool	Board::ft_is_on_board(int row, int col)
{
	return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
}

void	Board::ft_export_board(std::ofstream &file)
{
	char	direction;

	for (std::vector<Block>::iterator it = this->blocks.begin(); it != this->blocks.end(); it++)
	{
		if (it->direction == HORIZONTAL)
			direction = 'h';
		else
			direction = 'v';
		file<<it->row + 1 << " " << it->col << " " << it->len <<" "<< direction<<std::endl;

	}
}

std::string	Board::ft_get_hash(void)
{
	std::string hash = std::string();

	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			hash  = hash + std::to_string(this->cells[i][j]);
	return (hash);
}

void	Board::ft_insert(Block block, int id_to_insert)
{
	if (id_to_insert == -1)
		id_to_insert = block.id;
	if (block.ft_is_horizontal())
	{
		for (int i = block.col; i < block.col + block.len; ++i)
			this->cells[block.row][i] = id_to_insert;	
	}
	else
	{
		for (int i = block.row; i > block.row - block.len; --i)
				this->cells[i][block.col] = id_to_insert;
	}
}

Board::~Board()
{
}
