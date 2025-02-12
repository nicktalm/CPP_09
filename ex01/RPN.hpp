/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:18:09 by ntalmon           #+#    #+#             */
/*   Updated: 2025/02/12 15:42:50 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <regex>
#include <sstream>
#include <fstream>
#include <limits>

class RPN
{
	private:
		std::stack<int> _stack;
		std::string _input;
	public:
		RPN(void);
		RPN(std::string input);
		RPN(RPN const &src);
		RPN &operator=(RPN const &src);
		~RPN(void);
		bool checkInput(void) const;
		void parseInput(void);
		void calculate(std::string s);
		class CalculationException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class InputException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class DivisionByZeroError : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class OverflowException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};