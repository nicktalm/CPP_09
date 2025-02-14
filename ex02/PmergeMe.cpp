/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:56:53 by ntalmon           #+#    #+#             */
/*   Updated: 2025/02/14 18:23:40 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(int ac, char **av)
{
	for (int i = 1; i < ac; ++i)
	{
		try
		{
			_data_vector.push_back(std::stoi(av[i]));
		}
		catch (const std::invalid_argument &)
		{
			throw std::runtime_error("Error: Invalid number format in argument " + std::string(av[i]));
		}
		catch (const std::out_of_range &)
		{
			throw std::runtime_error("Error: Number out of range in argument " + std::string(av[i]));
		}
	}

	_deque_data = std::deque<int>(_data_vector.begin(), _data_vector.end());

	std::cout << "Before: ";
	for (int num : _data_vector)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &src)
{
	*this = src;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
	if (this != &src)
	{
		_data_vector = src._data_vector;
		_deque_data = src._deque_data;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{
}

bool PmergeMe::isPositiveInteger(const std::string& str)
{
	return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit) && (str.size() == 1 || str[0] != '0');
}

void PmergeMe::fjmi_sort_vec(void)
{
	std::vector<int> arr = _data_vector;
}

void PmergeMe::fjmi_sort_deq(void)
{
	int size_pair = 1;
	bool odd = this->_deque_data.size() % 2;
	iteratorDeque it_begin = this->_deque_data.begin();
	iteratorDeque it_end = this->_deque_data.end();
	std::deque<int> arr = _deque_data;
	if (odd)
		it_end = std::prev(it_end);
}

void PmergeMe::merge_deque(iteratorDeque it_begin, iteratorDeque it_end, int size_pair)
{
}