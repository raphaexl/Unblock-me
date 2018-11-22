/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 11:55:35 by ebatchas          #+#    #+#             */
/*   Updated: 2018/11/22 14:08:44 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unblock.hpp"

void	ft_error_output(std::string error_msg = "");

int		main(int argc, char *argv[])
{
	int		algo;
	std::ifstream input_file;
	std::ofstream output_file;

	if (argc != 4)
	{
		ft_error_output();
		return (0);
	}
	srand(time(nullptr));
	if (!strcmp(argv[1], "dfs"))
		algo = DFS;
	else if (!strcmp(argv[1], "bfs"))
		algo = BFS;
	else
	{
		ft_error_output();
		return (0);
	}
	input_file.open(argv[2]);
	if (!input_file.is_open())
	{
		ft_error_output("There was a problem opening that input file");
		return (-1);
	}
	output_file.open(argv[3]);
	if (!output_file.is_open())
	{
		ft_error_output("Therer was a problem opening that output file");
		return (-1);
	}
	try
	{
		Unblock un(&input_file,&output_file, algo);

		ft_print_separator();
		un.ft_exec();
		return (0);
	}
	catch (std::string err_msg)
	{
		std::cerr << err_msg << std::endl;
		return (-1);
	}
}

void	ft_error_output(std::string err_msg)
{
		std::cerr << std::endl <<std::endl<<"=============================================================="<<std::endl;
		if (err_msg.compare("") == 0)
		{
			std::cerr<< " Error : You di something wrong (dfs or bfs) input_file out_put_file"<<std::endl<< std::endl;
		}
		else
			std::cerr << err_msg << std::endl;
		std::cerr<<"================================================================="<<std::endl;
}

