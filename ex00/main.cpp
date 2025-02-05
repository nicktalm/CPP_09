/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicktalmon <nicktalmon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:43:58 by ntalmon           #+#    #+#             */
/*   Updated: 2025/02/05 17:09:10 by nicktalmon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int ac, char **av)
{
	if (ac == 2)
	{
		try
		{
			
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " <<e.what() << std::endl;
		}
	}
	else
	{
		std::cerr << "Error: Wrong uber of arguments" << std::endl;
		std::cerr << "Usage: " << av[0] << " <filename>" << std::endl;
	}
	return 0;
}