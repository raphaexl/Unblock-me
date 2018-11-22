/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 09:43:45 by ebatchas          #+#    #+#             */
/*   Updated: 2018/11/22 14:07:40 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unblock.hpp"

SDL_Texture		*ft_get_block_surf(int id, int len, char direction, SDL_Renderer *renderer)
{
	SDL_Surface		*surf;
	SDL_Texture		*img;

	if (id == 1)
	{
		surf = SDL_LoadBMP("Ablock.bmp");
		img = SDL_CreateTextureFromSurface(renderer,surf);
		SDL_FreeSurface(surf), surf = nullptr;
		return (img);
	}
	else
	{
		if (direction == HORIZONTAL && len == 3)
		{
			surf = SDL_LoadBMP("1x3H.bmp");
			img = SDL_CreateTextureFromSurface(renderer,surf);
			SDL_FreeSurface(surf), surf = nullptr;
			return (img);

		}
		if (direction == HORIZONTAL && len == 2)
		{
			surf = SDL_LoadBMP("1x2H.bmp");
			img = SDL_CreateTextureFromSurface(renderer,surf);
			SDL_FreeSurface(surf), surf = nullptr;
			return (img);
		}
		if (direction == VERTICAL && len == 3)
		{
			surf = SDL_LoadBMP("3x1V.bmp");
			img = SDL_CreateTextureFromSurface(renderer,surf);
			SDL_FreeSurface(surf), surf = nullptr;
			return (img);
		}
		if (direction == VERTICAL && len == 2)
		{
			surf = SDL_LoadBMP("2x1V.bmp");
			img = SDL_CreateTextureFromSurface(renderer,surf);
			SDL_FreeSurface(surf), surf = nullptr;
			return (img);
		}
	}
	return (NULL);
}

SDL_Texture		*ft_get_render_text(const std::string &message, const std::string &font_file, SDL_Color color, int font_size, SDL_Renderer * renderer)
{
	TTF_Font 		*font = TTF_OpenFont(font_file.c_str(), font_size);
	SDL_Surface		*surface = TTF_RenderText_Blended(font, message.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!font)
		std::cout<<TTF_GetError()<<std::endl;
	TTF_CloseFont(font);
	return texture;
}

void			ft_render_draw_img(SDL_Renderer	*renderer, SDL_Texture *img, int x, int y, SDL_Rect	*pos)
{
	SDL_Rect	src = {x, y, pos->w, pos->h};
	if (renderer && img)
		ERR_CHECK(SDL_RenderCopy(renderer, img, &src, pos), "");
}

