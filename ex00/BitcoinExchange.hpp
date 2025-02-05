/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicktalmon <nicktalmon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:44:50 by ntalmon           #+#    #+#             */
/*   Updated: 2025/02/05 17:21:11 by nicktalmon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>

class BitcoinExchange
{
	public:
		BitcoinExchange(void);
		BitcoinExchange(std::string data, std::string input);
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange &operator=(const BitcoinExchange &src);
		~BitcoinExchange();
		void checkPrice(void) const;
	private:
		std::multimap<std::string, std::string> data;
		std::multimap<std::string, std::string> input;
};

bool checkDate(std::string date);
bool checkNumber(std::string nbr);
std::multimap<std::string, std::string> readFile(std::ifstream &input, char seperator);