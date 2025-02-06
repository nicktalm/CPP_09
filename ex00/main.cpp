/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:43:58 by ntalmon           #+#    #+#             */
/*   Updated: 2025/02/06 11:46:45 by ntalmon          ###   ########.fr       */
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
			BitcoinExchange exchange(av[1]);
			// exchange.checkPrice();
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