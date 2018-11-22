/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:55:41 by ebatchas          #+#    #+#             */
/*   Updated: 2018/11/22 09:11:20 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "defs.hpp"

class Block
{
	public:
		Block(int id, int row, int col, int len, char direction);
		Block();
		~Block();
		bool			ft_is_horizontal(void);
		void			ft_init(SDL_Renderer *renderer);
		void			ft_print(void);
		void			ft_move(int direction);
		void			ft_draw(SDL_Renderer *renderer);
		int				ft_randint(int min, int max);

		SDL_Texture		*img;
		SDL_Rect		pos;
		int				id;
		int				row;
		int				col;
		int				len;
		int				direction;
};
