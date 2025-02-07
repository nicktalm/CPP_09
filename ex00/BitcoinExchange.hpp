/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:44:50 by ntalmon           #+#    #+#             */
/*   Updated: 2025/02/07 11:17:17 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <regex>

class BitcoinExchange
{
	public:
		BitcoinExchange(void);
		BitcoinExchange(std::string file);
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange &operator=(const BitcoinExchange &src);
		~BitcoinExchange();
		void checkPrice(void) const;
	private:
		std::multimap<std::string, std::string> data;
		std::multimap<std::string, std::string> input;
};

bool checkDate(std::string date);
bool checkNumberData(std::string nbr);
bool checkNumberInput(std::string nbr);
void trim(std::string &str);
std::multimap<std::string, std::string> readFile(std::ifstream &input, char seperator);