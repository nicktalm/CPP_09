/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:44:41 by ntalmon           #+#    #+#             */
/*   Updated: 2025/02/06 14:05:17 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void){}

BitcoinExchange::BitcoinExchange(std::string file)
{
	std::ifstream input, data;

	input.open(file);
	data.open("data.csv");
	this->data = readFile(data, ',');
	this->input = readFile(input, '|');
	for (const auto &entry : this->data)
	{
		if (!checkDate(entry.first))
		{
			std::cerr << "Invalid date: " << entry.first << std::endl;
			continue;
		}
		if (!checkNumberData(entry.second))
		{
			std::cerr << "Invalid number: " << entry.second << std::endl;
			continue;
		}
	}
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

// Trim-Funktion entfernt alle Leerzeichen aus einem String
void trim(std::string &str) {
	str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
}

std::multimap<std::string, std::string> readFile(std::ifstream &input, char delimiter)
{
	std::multimap<std::string, std::string> map;
	std::string line;

	std::getline(input, line); // Erste Zeile (Header) ignorieren
	while (std::getline(input, line))
	{
		size_t sep = line.find(delimiter);
		if (sep != std::string::npos)
		{
			std::string date = line.substr(0, sep);
			std::string nbr  = line.substr(sep + 1);
			trim(date);
			trim(nbr);
			map.emplace(date, nbr);
		}
		else
		{
			map.emplace(line, "");
		}
	}
	return map;
}

bool checkDate(std::string date)
{
	std::regex datePattern("^\\d{4}-\\d{2}-\\d{2}$");
	int year = std::stoi(date.substr(0, 4));
	int month = std::stoi(date.substr(5, 2));
	int day = std::stoi(date.substr(8, 2));
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (std::regex_match(date, datePattern))
	{
		if (day < 1 || day > daysInMonth[month - 1])
			return false;
		if (month < 1 || month > 12)
			return false;
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			daysInMonth[1] = 29;
		return true;
	}
	return false;
}

bool checkNumberData(std::string nbr)
{
	std::regex pattern("^\\d+(\\.\\d+)?$");  // Erlaubt beliebig viele Ziffern (ganzzahl oder Fließkommazahl)
	
	// Prüfe, ob die Zahl positiv ist und entweder Integer oder Float ist
	if (std::regex_match(nbr, pattern)) 
	{
		return true;
	}
	// std::cerr << "Error: Invalid or negative number: " << nbr << std::endl;
	return false;
}

bool checkNumberInput(std::string nbr)
{
	std::regex pattern("^\\d{1,4}(\\.\\d+)?$");

	if (std::regex_match(nbr, pattern)) 
	{
		float value = std::stof(nbr);
		if (value < 0)
		{
			// std::cerr << "Error: Number is negative: " << nbr << std::endl;
			return false;
		}
		if (value > 1000)
		{
			// std::cerr << "Error: Number is too big: " << nbr << std::endl;
			return false;
		}
		return true;
	}
	// std::cerr << "Error: Invalid number: " << nbr << std::endl;
	return false;
}

