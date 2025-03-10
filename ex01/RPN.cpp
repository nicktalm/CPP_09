/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:17:56 by ntalmon           #+#    #+#             */
/*   Updated: 2025/03/10 16:51:14 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void)
{
}

RPN::RPN(std::string input) : _input(input)
{
}

RPN::RPN(RPN const &src)
{
	*this = src;
}

RPN &RPN::operator=(RPN const &src)
{
	if (this != &src)
	{
		_stack = src._stack;
		_input = src._input;
	}
	return *this;
}

RPN::~RPN(void)
{
}

// Überprüft, ob die Eingabe nur erlaubte Zeichen enthält (Ziffern und Operatoren).
bool RPN::checkInput() const
{
	for (char c : _input)
	{
		// Zulässige Zeichen: Ziffern, Leerzeichen und Operatoren.
		if (!std::isdigit(c) && c != ' ' && c != '+' && c != '-' && c != '/' && c != '*')
		{
			return false;  // Ungültiges Zeichen gefunden.
		}
	}
	return true;  // Alle Zeichen sind gültig.
}

// Zerlegt die Eingabezeichenkette in Tokens und verarbeitet sie.
void RPN::parseInput()
{
	std::istringstream stream(_input);  // Einlesestream für die Eingabe.
	std::string element;

	while (stream >> element)  // Liest jedes Element (Zahl oder Operator).
	{
		// Wenn es ein Operator ist, wird die Berechnung durchgeführt.
		if (element == "+" || element == "-" || element == "*" || element == "/")
		{
			if (_stack.size() < 2)  // Überprüft, ob mindestens zwei Zahlen im Stack sind.
				throw CalculationException();  // Fehler, wenn nicht genug Operanden vorhanden sind.
			calcResult(element);  // Berechnet das Ergebnis der Operation.
		}
		// Wenn es eine Ziffer ist, wird sie als Zahl auf den Stack geschoben.
		else if (element.size() == 1 && std::isdigit(element[0]))
		{
			_stack.push(element[0] - '0');  // Umwandlung von Zeichen in Integer.
		}
		else
		{
			throw InputException();  // Fehler, wenn das Token ungültig ist.
		}
	}
	if (_stack.size() != 1)  // Am Ende sollte genau ein Ergebnis im Stack bleiben.
		throw CalculationException();  // Fehler, wenn mehr oder weniger Ergebnisse vorhanden sind.
	std::cout << "\033[32m\033[1mRESULT:\033[0m \033[32m" << _stack.top() << "\033[0m" << std::endl;
}

// Führt eine mathematische Berechnung auf den beiden obersten Zahlen im Stack durch.
void RPN::calcResult(std::string s)
{
	if (_stack.size() < 2)  // Überprüft, ob mindestens zwei Operanden vorhanden sind.
		throw CalculationException();  // Fehler, wenn nicht genug Operanden vorhanden sind.
	int one = _stack.top();  // Holt den ersten Wert (oberster Wert).
	_stack.pop();  // Entfernt den Wert vom Stack.
	int two = _stack.top();  // Holt den zweiten Wert.
	_stack.pop();  // Entfernt auch diesen Wert.
	long long result;  // Ergebnis der Berechnung (long long für Überlaufkontrolle).
	
	// Berechnung je nach Operator.
	if (s == "+")
		result = static_cast<long long>(two) + static_cast<long long>(one);
	else if (s == "-")
		result = static_cast<long long>(two) - static_cast<long long>(one);
	else if (s == "*")
		result = static_cast<long long>(two) * static_cast<long long>(one);
	else if (s == "/")
	{
		if (one == 0)  // Überprüft Division durch null.
			throw DivisionByZeroError();
		result = two / one;
	}
	else
		throw CalculationException();  // Fehler, wenn ein unbekannter Operator verwendet wird.

	// Überprüft, ob das Ergebnis im Bereich der Integer-Zahlen liegt.
	if (result > std::numeric_limits<int>::max() || result < std::numeric_limits<int>::min())
		throw OverflowException();  // Fehler bei Überlauf.
	_stack.push(static_cast<int>(result));  // Das Ergebnis wird wieder auf den Stack geschoben.
}

// Ausnahmebehandlung für Berechnungsfehler.
const char *RPN::CalculationException::what() const throw()
{
	return "Calculation error";  // Standardfehlermeldung für Berechnungsfehler.
}

// Ausnahmebehandlung für ungültige Eingaben.
const char *RPN::InputException::what() const throw()
{
	return "Invalid token";  // Fehler, wenn ein ungültiges Token gefunden wird.
}

// Ausnahmebehandlung für Division durch Null.
const char *RPN::DivisionByZeroError::what() const throw()
{
	return "Division by zero";  // Fehlermeldung für Division durch null.
}

// Ausnahmebehandlung für Überlauffehler (wenn das Ergebnis zu groß oder zu klein ist).
const char *RPN::OverflowException::what() const throw()
{
	return "Overflow error";  // Fehlermeldung für Überlauf.
}
