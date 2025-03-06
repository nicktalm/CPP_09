/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:44:41 by ntalmon           #+#    #+#             */
/*   Updated: 2025/03/05 14:50:45 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// Konstruktor, der eine Datei einliest und prüft, ob die angegebenen Dateien gültig sind.
BitcoinExchange::BitcoinExchange(void){}

// Konstruktor, der eine Datei einliest, die Daten überprüft und speichert.
BitcoinExchange::BitcoinExchange(std::string file)
{
	std::ifstream input, data;
	std::string dataFile = "data.csv";

	// Überprüft, ob die Eingabedatei gültig ist.
	if (file.c_str() == NULL || file.empty())
	{
		std::cerr << "Error: No file given" << std::endl;
		return;
	}
	// Überprüft, ob die Daten-Datei gültig ist.
	if (dataFile.c_str() == NULL || dataFile.empty())
	{
		std::cerr << "Error: No data file given" << std::endl;
		return;
	}
	std::ifstream testData(dataFile);
	// Überprüft, ob die Daten-Datei leer ist.
	if (testData.peek() == std::ifstream::traits_type::eof())
	{
		std::cerr << "Error: Data file is empty: " << dataFile << std::endl;
		return;
	}
	testData.close();
	
	// Öffnet die Eingabe- und Daten-Dateien.
	input.open(file);
	if (!input.is_open())
	{
		std::cerr << "Error: Could not open file: " << file << std::endl;
		return;
	}
	data.open(dataFile);
	if (!data.is_open())
	{
		std::cerr << "Error: Could not open file: " << dataFile << std::endl;
		return;
	}

	// Liest die Daten aus den Dateien und speichert sie.
	this->data = readFile(data, ',');
	this->input = readFile(input, '|');

	// Überprüft alle Dateneinträge auf Gültigkeit.
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

// Kopierkonstruktor: Erzeugt eine Kopie eines BitcoinExchange-Objekts.
BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	this->data = src.data;
	this->input = src.input;
}

// Zuweisungsoperator: Erlaubt das Zuweisen eines BitcoinExchange-Objekts an ein anderes.
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
	{
		this->data = src.data;
		this->input = src.input;
	}
	return *this;
}

// Destruktor: Wird aufgerufen, wenn das BitcoinExchange-Objekt zerstört wird.
BitcoinExchange::~BitcoinExchange(){}

// Entfernt führende und nachfolgende Leerzeichen aus einem gegebenen String.
void trim(std::string &str) {
	str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
}

// Liest eine Datei ein und gibt die Daten als std::multimap zurück.
std::multimap<std::string, std::string> readFile(std::ifstream &input, char delimiter)
{
	std::multimap<std::string, std::string> map;
	std::string line;

	// Liest die Datei Zeile für Zeile.
	std::getline(input, line);
	while (std::getline(input, line))
	{
		size_t sep = line.find(delimiter);
		if (sep != std::string::npos)
		{
			// Trennt das Datum und die Zahl anhand des Delimiters.
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

// Überprüft, ob das gegebene Datum im Format YYYY-MM-DD gültig ist.
bool checkDate(std::string date)
{
	std::regex datePattern("^\\d{4}-\\d{2}-\\d{2}$");
	int year = std::stoi(date.substr(0, 4));
	int month = std::stoi(date.substr(5, 2));
	int day = std::stoi(date.substr(8, 2));
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (std::regex_match(date, datePattern))
	{
		// Überprüft, ob der Tag innerhalb des Monatsbereichs liegt.
		if (day < 1 || day > daysInMonth[month - 1])
			return false;
		// Überprüft, ob der Monat gültig ist.
		if (month < 1 || month > 12)
			return false;
		// Überprüft, ob das Jahr ein Schaltjahr ist und passt den Februar an.
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			daysInMonth[1] = 29;
		return true;
	}
	return false;
}

// Überprüft, ob die gegebene Zahl entweder eine Ganzzahl oder eine Fließkommazahl ist und ob sie positiv ist.
bool checkNumberData(std::string nbr)
{
	std::regex pattern("^\\d+(\\.\\d+)?$");  // Erlaubt beliebig viele Ziffern (ganzzahl oder Fließkommazahl)
	
	if (std::regex_match(nbr, pattern)) 
	{
		return true;
	}
	return false;
}

// Überprüft, ob die gegebene Zahl eine gültige Zahl im Bereich 0 bis 1000 ist und keine negativen Werte enthält.
bool checkNumberInput(std::string nbr)
{
	std::regex pattern("^\\d{1,4}(\\.\\d+)?$");

	if (std::regex_match(nbr, pattern)) 
	{
		float value = std::stof(nbr);
		if (value < 0)
		{
			std::cerr << "Error: Number is negative: " << nbr << std::endl;
			return false;
		}
		if (value > 1000)
		{
			std::cerr << "Error: Number is too big: " << nbr << std::endl;
			return false;
		}
		return true;
	}
	std::cerr << "Error: Invalid number: " << nbr << std::endl;
	return false;
}

// Überprüft die Preise für die Eingaben und berechnet das Ergebnis.
void BitcoinExchange::checkPrice(void) const
{
	for (auto it = this->input.begin(); it != this->input.end(); ++it)
	{
		// Überprüft, ob das Datum gültig ist.
		if (!checkDate(it->first))
		{
			std::cerr << "Error: bad input => " + it->first << std::endl;
			continue; // Fehler schnell überspringen
		}
		// Sucht nach dem passenden Datum in den gespeicherten Daten.
		auto found = this->data.lower_bound(it->first);
		if (found == this->data.end() || found->first != it->first)
		{
			--found;  // Korrekte Position finden
		}
		// Überprüft, ob der Preis eine gültige Zahl ist.
		if (!checkNumberInput(it->second))
		{
			continue; // Ungültige Zahl überspringen
		}
		// Berechnet und gibt das Ergebnis aus.
		float inputPrice = std::stof(it->second);
		float dbPrice = std::stof(found->second);
		std::cout << it->first << " => " << it->second << " = " << inputPrice * dbPrice << std::endl;
	}
}
