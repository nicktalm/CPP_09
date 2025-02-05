/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicktalmon <nicktalmon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:44:41 by ntalmon           #+#    #+#             */
/*   Updated: 2025/02/05 17:28:34 by nicktalmon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void){}

BitcoinExchange::BitcoinExchange(std::string data, std::string input)
{
	
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	this->data = src.data;
	this->input = src.input;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
	{
		this->data = src.data;
		this->input = src.input;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange(){}