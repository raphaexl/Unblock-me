/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unblock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:20:51 by ebatchas          #+#    #+#             */
/*   Updated: 2018/11/22 12:38:59 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "solver.hpp"


class Unblock
{
	public:
		Board			board;
		Solver	solution;
		Unblock(std::ifstream *input_file, std::ofstream *output_file, int algo);
		~Unblock();
		int				ft_exec(void);
		bool			ft_ticks(void);
		void			ft_draw(void);
		SDL_Window		*ft_get_window(void);
		SDL_Renderer	*ft_get_renderer(void);
		int				algo;
		unsigned int	ticks;
		std::ifstream	*input_file;
		std::ofstream	*output_file;
		double 			running_time;
		t_input			input;
		SDL_Color		color[3] = {{255, 0, 0, 255},{0,255,0,255},{12,112,155,255}};
		SDL_Rect		pos[3];
		
	private:
		SDL_Window		*window;
		SDL_Renderer	*renderer;
		SDL_Texture		*step;
		SDL_Texture		*alg;
		SDL_Texture		*time;
		Mix_Chunk		*s1, *s2;
};
