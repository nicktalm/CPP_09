/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:56:53 by ntalmon           #+#    #+#             */
/*   Updated: 2025/02/19 16:38:21 by ntalmon          ###   ########.fr       */
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
	bool odd = this->_deque_data.size() % 2;
	iteratorDeque it_d_begin = this->_deque_data.begin();
	iteratorDeque it_d_end = this->_deque_data.end();
	iteratorVector it_v_begin = this->_data_vector.begin();
	iteratorVector it_v_end = this->_data_vector.end();

	if (odd)
	{
		it_d_end = std::prev(it_d_end);
		it_v_end = std::prev(it_v_end);
	}
	fjmi_sort_vec(it_v_begin, it_v_end, size_pair);
	insert_vector(it_v_begin, it_v_end, size_pair);
	fjmi_sort_deq(it_d_begin, it_d_end, size_pair);
	printVector();
}

void PmergeMe::printVector(void)
{
	std::cout << "\033[34mVector:\033[0m" << std::endl;
	for (iteratorVector it = this->_data_vector.begin(); it != this->_data_vector.end(); ++it)
		std::cout << "\033[34m" << *it << " \033[0m";
	std::cout << std::endl;
}

void PmergeMe::printDeque(void)
{
	std::cout << "\033[32mDeque:\033[0m" << std::endl;
	for (iteratorDeque it = this->_deque_data.begin(); it != this->_deque_data.end(); ++it)
		std::cout << "\033[32m" << *it << " \033[0m";
	std::cout << std::endl;
}

void PmergeMe::insert_vector(iteratorVector it_begin, iteratorVector it_end, int size_pair)
{
	if (std::distance(it_begin, it_end) < size_pair * 2)
		return;

	std::vector<iteratorVector> b_pairs; // Container für B-Paare
	bool toggle = false; 
	bool first_b_skipped = false;

	std::cout << "Gesamter Vektor: ";
	for (iteratorVector it = it_begin; it != it_end; ++it)
		std::cout << *it << " ";
	std::cout << "\n\n";

	int pairIndexA = 1;
	int pairIndexB = 1;

	for (iteratorVector it = it_begin; it != it_end; it = std::next(it, size_pair))
	{
		std::cout << (toggle ? "A-Paar " : "B-Paar ") << (toggle ? pairIndexA++ : pairIndexB++) << ": ";

		for (iteratorVector pairIt = it; pairIt != std::next(it, size_pair) && pairIt != it_end; ++pairIt)
		{
			std::cout << *pairIt << " ";
		}

		if (!toggle) // B-Paar
		{
			if (first_b_skipped)
			{
				b_pairs.push_back(it);
				std::cout << "(wird gespeichert)";
			}
			else
			{
				std::cout << "(bleibt als erstes B-Paar)";
				first_b_skipped = true;
			}
		}
		std::cout << std::endl;

		toggle = !toggle;
	}

	std::cout << "\nGespeicherte B-Paare (außer das erste):\n";
	for (size_t i = 0; i < b_pairs.size(); i++)
	{
		std::cout << "B-Paar " << (i + 2) << ": ";
		for (iteratorVector pairIt = b_pairs[i]; pairIt != std::next(b_pairs[i], size_pair) && pairIt != it_end; ++pairIt)
		{
			std::cout << *pairIt << " ";
		}
		std::cout << std::endl;
	}
}

void PmergeMe::fjmi_sort_vec(iteratorVector it_begin, iteratorVector it_end, int size_pair)
{
	if (size_pair == std::distance(it_begin, it_end))
		return;
	while (std::distance(it_begin, it_end) % (size_pair * 2) != 0)
		it_end = std::prev(it_end);
	merge_vector(it_begin, it_end, size_pair);
	std::cout << "pairSize = " << size_pair << " distance = " << std::distance(it_begin, it_end) << std::endl;
	this->printVector();
	size_pair *= 2;
	this->fjmi_sort_vec(it_begin, it_end, size_pair);
	insert_vector(it_begin, it_end, size_pair);
	// std::cout << "pairSize = " << size_pair << " distance = " << std::distance(it_begin, it_end) << std::endl;
}

void PmergeMe::fjmi_sort_deq(iteratorDeque it_begin, iteratorDeque it_end, int size_pair)
{
	if (size_pair == std::distance(it_begin, it_end))
		return;
	while (std::distance(it_begin, it_end) % (size_pair * 2) != 0)
		it_end = std::prev(it_end);
	merge_deque(it_begin, it_end, size_pair);
	// this->printDeque();
	size_pair *= 2;
	// std::cout << "pairSize = " << size_pair << " distance = " << std::distance(it_begin, it_end) << std::endl;
	this->fjmi_sort_deq(it_begin, it_end, size_pair);
	//INSERT
	// std::cout << "pairSize = " << size_pair << " distance = " << std::distance(it_begin, it_end) << std::endl;
}

void PmergeMe::merge_vector(iteratorVector it_begin, iteratorVector it_end, int pairSize)
{
	if (std::distance(it_begin, it_end) < pairSize * 2)
		return;

	std::pair<iteratorVector, iteratorVector> firstPair;
	std::pair<iteratorVector, iteratorVector> secondPair;

	while (it_begin != it_end)
	{
		iteratorVector firstPairEnd = std::next(it_begin, pairSize);
		iteratorVector secondPairEnd = std::next(firstPairEnd, pairSize);
		iteratorVector lastElement = std::prev(secondPairEnd);

		firstPair.first = it_begin;
		firstPair.second = std::prev(firstPairEnd);
		secondPair.first = std::prev(lastElement, pairSize - 1);
		secondPair.second = lastElement;
		
		if (*firstPair.second > *secondPair.second)
		{
			while (firstPair.first <= firstPair.second)
			{
				std::swap(*firstPair.first, *secondPair.first);
				firstPair.first++;
				secondPair.first++;
			}
		}
		it_begin = std::next(it_begin, pairSize * 2);
	}
}

void PmergeMe::merge_deque(iteratorDeque it_begin, iteratorDeque it_end, int pairSize)
{
	if (std::distance(it_begin, it_end) < pairSize * 2)
		return;

	std::pair<iteratorDeque, iteratorDeque> firstPair;
	std::pair<iteratorDeque, iteratorDeque> secondPair;

	while (it_begin != it_end)
	{
		iteratorDeque firstPairEnd = std::next(it_begin, pairSize);
		iteratorDeque secondPairEnd = std::next(firstPairEnd, pairSize);
		iteratorDeque lastElement = std::prev(secondPairEnd);

		firstPair.first = it_begin;
		firstPair.second = std::prev(firstPairEnd);
		secondPair.first = std::prev(lastElement, pairSize - 1);
		secondPair.second = lastElement;
		
		if (*firstPair.second > *secondPair.second)
		{
			while (firstPair.first <= firstPair.second)
			{
				std::swap(*firstPair.first, *secondPair.first);
				firstPair.first++;
				secondPair.first++;
			}
		}
		it_begin = std::next(it_begin, pairSize * 2);
	}
}
