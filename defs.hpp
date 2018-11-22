/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:24:40 by ebatchas          #+#    #+#             */
/*   Updated: 2018/11/22 14:09:12 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <fstream>
# include <deque>
# include <map>
# include <vector>
# include <cstring>
# include <ctime>
# include <string>

# include <SDL2/SDL.h>
# include <SDL2/SDL_mixer.h>
# include <SDL2/SDL_ttf.h>

# define BOARD_SIZE 6
# define HORIZONTAL 0
# define VERTICAL 1
# define WIN_WIDTH 700
# define WIN_HEIGHT 1000

# define pp(x) std::cout<<x<<std::endl;
# define pp2(x, y) std::cout<<x<<' '<<y<<std::endl;
# define ERR_CHECK(cond,msg) if (!(cond)) std::cout <<msg<<SDL_GetError()

typedef	enum		e_keys
{
	LEFT, RIGHT, UP, DOWN
}					t_keys;

typedef enum		e_algorithm
{
	DFS, BFS
}					t_algorithm;

typedef struct		s_input
{
  SDL_bool key[SDL_NUM_SCANCODES];
  SDL_bool mouse[6];
  SDL_bool quit;
  int mousex,mousey;
  int mousexrel,mouseyrel;	
  int xwheel, ywheel;
}					t_input;


inline	void		ft_print_separator(void)
{
	std::cout<<std::endl<<"============================================="<<std::endl<<std::endl;
}

inline void			ft_throw_error(const char *err_msg, int	blocked_id = -1)
{
	std::string		error_str(err_msg);
	std::string		separator("\n\n=============================================\n\n");

	error_str = separator + error_str;
	if (blocked_id == -1)
	{
		std::string blocked_msg("Block ID: ");
		error_str = error_str + blocked_msg + std::to_string(blocked_id);
	}
	error_str += separator;
	throw error_str;
}

void			ft_update_event(t_input *in);
SDL_Texture		*ft_get_block_surf(int id, int len, char direction, SDL_Renderer *renderer);
SDL_Texture		*ft_get_render_text(const std::string &message, const std::string &font_file, SDL_Color color, int font_size, SDL_Renderer * renderer);
void			ft_render_draw_img(SDL_Renderer	*renderer, SDL_Texture *img, int x, int y, SDL_Rect	*pos);
