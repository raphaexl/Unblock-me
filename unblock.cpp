/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unblock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:57:27 by ebatchas          #+#    #+#             */
/*   Updated: 2018/11/22 21:22:44 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unblock.hpp"

Unblock::Unblock(std::ifstream *input_file, std::ofstream *output_file, int	algo)
{
	this->algo = algo;
	this->input_file = input_file;
	this->output_file = output_file;
	this->board.ft_fill_board(*input_file);
	this->solution = this->board;
	clock_t start, finish;
	start = clock();
	solution.ft_solve(this->algo);
	finish = clock();
	this->running_time = ((double)(finish - start))/CLOCKS_PER_SEC;
	ERR_CHECK(SDL_Init(SDL_INIT_VIDEO) == 0, "Error Init");
	ERR_CHECK(TTF_Init() == 0, "Error TTF_Init()");
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	ERR_CHECK(window = SDL_CreateWindow("Press A To Visualize", SDL_WINDOWPOS_UNDEFINED, \
				SDL_WINDOWPOS_UNDEFINED,WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL),\
			"Error SDL_CreateWindow()");
	ERR_CHECK(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | \
				SDL_RENDERER_PRESENTVSYNC), "Error SDL_CreateRenderer()");
		this->ticks = SDL_GetTicks();
	memset(&this->input, SDL_FALSE, sizeof(t_input));
	this->step = nullptr;
	Mix_AllocateChannels(32);
	this->board.ft_init(renderer);
	this->s1 = Mix_LoadWAV("s1.wav");
	this->s2 = Mix_LoadWAV("s2.wav");
	this->alg = ft_get_render_text( (algo == BFS) ? "BFS" : "DFS", "angelina.TTF", color[1], 64, renderer);
	SDL_QueryTexture(this->alg, nullptr, nullptr, &pos[1].w, &pos[1].h);
	pos[1].x = 60;
	pos[1].y = 920;
	ERR_CHECK(this->alg, "Error Font !!!!");
	this->time = ft_get_render_text( std::to_string(running_time) + "sec", "angelina.TTF", color[2], 42, renderer);
	SDL_QueryTexture(this->time, nullptr, nullptr, &pos[2].w, &pos[2].h);
	pos[2].x = 255;
	pos[2].y = 935;
	ERR_CHECK(this->time, "Error Font !!!!");
}

int		Unblock::ft_exec(void)
{	
	while (!this->input.quit)
	{
		ft_update_event(&this->input);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
		SDL_RenderClear(renderer);
		ft_draw();
		SDL_Delay(10);
	}
	return (0);
}

bool 	Unblock::ft_ticks(void)
{
	SDL_Delay(10);
	return (true);
}

void	Unblock::ft_draw(void)
{
	Uint32	new_ticks;
	int		i(0);	
	
	if (this->input.key[SDL_SCANCODE_A])
	{
		for (std::vector<Board>::reverse_iterator it = solution.steps.rbegin() ; it != solution.steps.rend() && (!input.quit); ++it)
		{
			this->step = ft_get_render_text(std::to_string(i), "angelina.TTF", color[0], 64, renderer);
			SDL_QueryTexture(this->step, nullptr, nullptr, &pos[0].w, &pos[0].h);
			ERR_CHECK(this->step, "Error Font !!!!");
			new_ticks = SDL_GetTicks();
			if (new_ticks - ticks > 50 )
			{
				ticks = new_ticks;
				it->ft_draw(renderer);
				pos[0].x = 615 - std::to_string(i).length()*10;
				pos[0].y = 920;
				ft_render_draw_img(renderer, this->step, 0, 0, &pos[0]);
				ft_render_draw_img(renderer, this->alg, 0, 0, &pos[1]);
				ft_render_draw_img(renderer, this->time, 0, 0, &pos[2]);
				SDL_RenderPresent(renderer);
			}
			else
				SDL_Delay(50 - (new_ticks - ticks));
			SDL_Delay(800);
			Mix_PlayChannel(0, this->s2, 0);
			i++;
		ft_update_event(&this->input);
		}
		Mix_PlayChannel(0, this->s1, 0);
	}
}

SDL_Window		 *Unblock::ft_get_window(void)
{
	return (this->window);
}

SDL_Renderer	*Unblock::ft_get_renderer(void)
{
	return (this->renderer);
}

Unblock::~Unblock()
{	
	ft_print_separator();
	pp("Puzzlw was successfully solved.");
	pp2("Number of steps just : ", solution.steps.size());
	ft_print_separator();
	int i = 0;
	for (std::vector<Board>::reverse_iterator it = solution.steps.rbegin(); it != solution.steps.rend(); ++it)
	{
		it->ft_print("Step "+ std::to_string(i) + "\n");
		it->ft_export_board(*output_file);
		(*output_file)<< std::endl << std::endl;
		i++;
	}
	ft_print_separator();
	pp("Puzzlw was successfully solved.");
	pp2("The Total number of seconds the algo took to solve it :  ", running_time);
	pp2("The Total number of board seen to find the solution including the initial state is : ", solution.number_of_nodes);
	pp("\n The Bolck with 1s represents the Block wich is asked to be rescued  :)");
	pp("The output states are written to the output file you provided");
	ft_print_separator();
	input_file->close();
	output_file->close();
	Mix_FreeChunk(s1), s1 = nullptr;
	Mix_FreeChunk(s2), s2 = nullptr;
	if (renderer)
		SDL_DestroyRenderer(renderer), renderer = nullptr;
	if (window)
		SDL_DestroyWindow(window), window = nullptr;
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}
