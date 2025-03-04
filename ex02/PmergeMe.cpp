/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:56:53 by ntalmon           #+#    #+#             */
/*   Updated: 2025/03/04 14:56:24 by ntalmon          ###   ########.fr       */
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

void PmergeMe::fjmi_sort(void)
{
	int size_pair = 1;
	bool odd = this->_deque_data.size() % 2 && this->_deque_data.size() > 1;
	iteratorDeque it_d_end = this->_deque_data.end();
	iteratorVector it_v_end = this->_data_vector.end();
	std::deque<int> tmp;

	std::copy(this->_data_vector.begin(), this->_data_vector.end(), std::back_inserter(tmp));
	if (odd)
		it_v_end = std::prev(it_v_end);
	this->fjmi_sort_vec(this->_data_vector.end(), size_pair);
	this->insert_vector(it_v_end, size_pair);
}

// Vector

void PmergeMe::printVector(void)
{
	std::cout << "\033[34mVector:\033[0m" << std::endl;
	for (iteratorVector it = this->_data_vector.begin(); it != this->_data_vector.end(); ++it)
		std::cout << "\033[34m" << *it << " \033[0m";
	std::cout << std::endl;
}

void PmergeMe::fjmi_sort_vec(iteratorVector it_end, int size_pair)
{
	if (size_pair == std::distance(this->_data_vector.begin(), it_end))
		return;
	while (std::distance(this->_data_vector.begin(), it_end) % (size_pair * 2) != 0)
		it_end = std::prev(it_end);
	merge_vector(it_end, size_pair);
	size_pair *= 2;
	this->fjmi_sort_vec(it_end, size_pair);
	this->insert_vector(it_end, size_pair);
}

void PmergeMe::merge_vector(iteratorVector it_end, int size_pair)
{
	std::vector<std::pair<iteratorVector, iteratorVector> > arr(2);

	for (iteratorVector start = this->_data_vector.begin(); start != it_end; start = std::next(start, (size_pair * 2)))
	{
		arr[0] = std::pair<iteratorVector, iteratorVector>(start, start + size_pair);
		arr[1] = std::pair<iteratorVector, iteratorVector>(start + size_pair, start + (size_pair * 2));
		if (*std::prev(arr[0].second) > *std::prev(arr[1].second))
			std::rotate(arr[0].first, arr[1].first, arr[1].second);
	}
}

void PmergeMe::insert_vector(iteratorVector it_end, int size_pair)
{
	iteratorVector start = this->_data_vector.begin();

	if (size_pair == std::distance(start, it_end) || std::distance(start, it_end) == 2)
		return;
	std::vector<int> mainIndex;
	std::vector<int> pendIndex;
	size_t currentJ = 3;
	size_t prevJ = 1;
	int endJ = -1;
	int targetIndex;
	int endIndex;
}

// Deque

void PmergeMe::printDeque(void)
{
	std::cout << "\033[32mDeque:\033[0m" << std::endl;
	for (iteratorDeque it = this->_deque_data.begin(); it != this->_deque_data.end(); ++it)
		std::cout << "\033[32m" << *it << " \033[0m";
	std::cout << std::endl;
}

void PmergeMe::fjmi_sort_deq(iteratorDeque it_end, int size_pair)
{
}

void PmergeMe::insert_deque(iteratorDeque it_end, int size_pair)
{
}

void PmergeMe::merge_deque(iteratorDeque it_begin, iteratorDeque it_end, int pairSize)
{
}
