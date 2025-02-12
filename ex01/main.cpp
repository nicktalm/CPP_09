/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:18:17 by ntalmon           #+#    #+#             */
/*   Updated: 2025/02/12 16:00:10 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char *ag[])
{
	if (ac != 2)
	{
		std::cerr << "Error: wrong number of arguments" << std::endl;
		return 1;
	}
	RPN stack(ag[1]);
	if (!stack.checkInput())
	{
		std::cerr << "Error: invalid input" << std::endl;
		return 1;
	}
	try
	{
		stack.parseInput();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
