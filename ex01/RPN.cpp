/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:17:56 by ntalmon           #+#    #+#             */
/*   Updated: 2025/02/12 15:50:47 by ntalmon          ###   ########.fr       */
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

bool RPN::checkInput() const
{
	for (char c : _input)
	{
		if (!std::isdigit(c) && c != ' ' && c != '+' && c != '-' && c != '/' && c != '*')
		{
			return false;
		}
	}
	return true;
}

void RPN::parseInput()
{
	std::istringstream stream(_input);
	std::string token;

	while (stream >> token)
	{
		// Falls Token ein Operator ist, Berechnung durchführen
		if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (_stack.size() < 2)
				throw CalculationException(); // Mindestens zwei Zahlen erforderlich
			calculate(token);
		}
		// Falls Token eine Ziffer (0-9) ist, auf Stack legen
		else if (token.size() == 1 && std::isdigit(token[0]))
		{
			_stack.push(token[0] - '0'); // Char zu int konvertieren
		}
		// Falls Token ungültig ist, Fehler werfen
		else
		{
			throw InputException();
		}
	}
	// Nach der Verarbeitung muss genau ein Ergebnis auf dem Stack liegen
	if (_stack.size() != 1)
		throw CalculationException();
	std::cout << "\033[32m\033[1mRESULT:\033[0m \033[32m" << _stack.top() << "\033[0m" << std::endl;
}

void RPN::calculate(std::string s)
{
	if (_stack.size() < 2)
		throw CalculationException();
	int one = _stack.top();
	_stack.pop();
	int two = _stack.top();
	_stack.pop();
	long long result;
	if (s == "+")
		result = static_cast<long long>(two) + static_cast<long long>(one);
	else if (s == "-")
		result = static_cast<long long>(two) - static_cast<long long>(one);
	else if (s == "*")
		result = static_cast<long long>(two) * static_cast<long long>(one);
	else if (s == "/")
	{
		if (one == 0)
			throw DivisionByZeroError();
		result = two / one;
	}
	else
		throw CalculationException();
	if (result > std::numeric_limits<int>::max() || result < std::numeric_limits<int>::min())
		throw OverflowException();
	_stack.push(static_cast<int>(result));
}

const char *RPN::CalculationException::what() const throw()
{
	return "Calculation error";
}

const char *RPN::InputException::what() const throw()
{
	return "Invalid token";
}

const char *RPN::DivisionByZeroError::what() const throw()
{
	return "Division by zero";
}

const char *RPN::OverflowException::what() const throw()
{
	return "Overflow error";
}