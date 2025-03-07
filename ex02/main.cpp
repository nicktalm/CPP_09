/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:57:06 by ntalmon           #+#    #+#             */
/*   Updated: 2025/03/06 11:30:35 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	try
	{
		if (ac < 2)
			throw std::runtime_error("Usage: ./PergeMe <numbers>");

		for (int i = 1; i < ac; ++i)
		{
			if (!PmergeMe::isPositiveInteger(av[i]))
				throw std::runtime_error("Error: " + std::string(av[i]) + " is not a positive integer");
		}
		
		PmergeMe pmergeMe(ac, av);
		pmergeMe.sortNumbers();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}
