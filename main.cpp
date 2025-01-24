/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:58:59 by smoroz            #+#    #+#             */
/*   Updated: 2025/01/22 09:33:15 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	main(int argc, char **argv)
{

	if (argc != 3)
	{
		std::cout << "Not all required parameter are provided" << std::endl;
		Server::usage();
		return (0);
	}

	Server	server;

	std::cout << "---- SERVER ----" << std::endl;
	try
	{
		server.init();
	}
	catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << "The Server Closed!" << std::endl;
}
