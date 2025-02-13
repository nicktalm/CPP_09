/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:17:56 by ntalmon           #+#    #+#             */
/*   Updated: 2025/02/13 14:54:22 by ntalmon          ###   ########.fr       */
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
	std::string element;

	while (stream >> element)
	{
		if (element == "+" || element == "-" || element == "*" || element == "/")
		{
			if (_stack.size() < 2)
				throw CalculationException();
			calcResult(element);
		}
		else if (element.size() == 1 && std::isdigit(element[0]))
		{
			_stack.push(element[0] - '0');
		}
		else
		{
			throw InputException();
		}
	}
	if (_stack.size() != 1)
		throw CalculationException();
	std::cout << "\033[32m\033[1mRESULT:\033[0m \033[32m" << _stack.top() << "\033[0m" << std::endl;
}

void RPN::calcResult(std::string s)
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