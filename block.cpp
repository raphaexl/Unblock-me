/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:49:18 by fel-hita          #+#    #+#             */
/*   Updated: 2018/11/22 20:44:37 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "block.hpp"

Block::Block(int id, int row, int col, int len, char direction) : row(row), col(col), len(len), direction(direction)
{
	
	this->id = id;
	this->row = row;
	this->col = col;
	this->len = len;

	if (direction == 'h')
		this->direction = HORIZONTAL;
	else
		this->direction = VERTICAL;
}

Block::Block() {}
int		Block::ft_randint(int min, int max)
{
	return (rand()%(max - min) + min);
}

void	Block::ft_init(SDL_Renderer *renderer)
{
	this->img = ft_get_block_surf(this->id, this->len, this->direction, renderer);
	SDL_QueryTexture(this->img, nullptr, nullptr, &this->pos.w, &this->pos.h);
}

void	Block::ft_print(void)
{
	std::cout << "id: " << this->id << " - row: " << this->row << " - column: " << this->col << " - length: " << this->len << " - direction: " << this->direction << std::endl;
}

void	Block::ft_draw(SDL_Renderer *renderer)
{
	this->pos.x = col*100 + 35 + col*6;
	if (direction == 'h' || direction == HORIZONTAL)
		this->pos.y = (row - len + 2)*100 + 250 + (row - len + 2) * 2;
	else
		this->pos.y = (row - len + 1)*100 + 250 + (row - len + 1) * 2;
	if (!this->img)
		ft_init(renderer);
	ft_render_draw_img(renderer,this->img, 0, 0, &this->pos);
}

bool	Block::ft_is_horizontal(void)
{
	return (this->direction == HORIZONTAL);
}

void	Block::ft_move(int direction)
{
	if (this->ft_is_horizontal())
	{
		if (direction == LEFT)
		{
			if (this->col == 0)
					ft_throw_error("Block cannot move to LEFT.", this->id);
			this->col--;
		}
		else if (direction == RIGHT)
		{
			if (this->col + this->len == BOARD_SIZE)
					ft_throw_error("Block cannot move to RIFGT.", this->id);
				this->col++;
		}
	}
	else
	{
		if (direction == UP)
		{
				if (this->row - this->len + 1 == 0)
					ft_throw_error("Block cannot move up.", this->id);
				this->row--;
		}
		else if (direction == DOWN)
		{
				if (this->row == BOARD_SIZE - 1)
					ft_throw_error("Block cannot move down.", this->id);
				this->row++;
		}
	}
}

Block::~Block()
{
}
