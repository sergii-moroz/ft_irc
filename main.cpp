/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:58:59 by smoroz            #+#    #+#             */
/*   Updated: 2025/02/15 16:14:43 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Utils.hpp"

int	main(int argc, char **argv)
{

	if (argc != 3)
	{
		std::cout << "Not all required parameter are provided" << std::endl;
		Server::usage();
		return (0);
	}

	int	port = Utils::validatePort(argv[1]);
	if (port == -1)
		return (0);

	std::string	pass = Utils::validatePass(argv[2]);
	if (pass.empty())
		return (0);

	Server		server(port, pass);

	signal(SIGINT, Server::signalHandler);
	signal(SIGQUIT, Server::signalHandler);

	std::cout << "---- SERVER ----" << std::endl;
	try
	{
		server.init();
		server.run();
	}
	catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << "The Server Closed!" << std::endl;
	return (0);
}
