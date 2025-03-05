/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:56:53 by ntalmon           #+#    #+#             */
/*   Updated: 2025/03/05 12:12:15 by ntalmon          ###   ########.fr       */
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

	_data_deque = std::deque<int>(_data_vector.begin(), _data_vector.end());

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
		_data_deque = src._data_deque;
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
	bool odd = this->_data_deque.size() % 2 && this->_data_deque.size() > 1;
	iteratorDeque it_d_end = this->_data_deque.end();
	iteratorVector it_v_end = this->_data_vector.end();

	std::chrono::time_point	start = std::chrono::high_resolution_clock::now();
	if (odd)
		it_v_end = std::prev(it_v_end);
	this->fjmi_sort_vec(it_v_end, size_pair);
	this->insert_vector(this->_data_vector.end(), size_pair);
	std::chrono::time_point	end = std::chrono::high_resolution_clock::now();
	double	diffDq = std::chrono::duration<double, std::micro>(end - start).count();
	start = std::chrono::high_resolution_clock::now();
	if (odd)
		it_d_end = std::prev(it_d_end);
	this->fjmi_sort_deq(it_d_end, size_pair);
	this->insert_deque(this->_data_deque.end(), size_pair);
	end = std::chrono::high_resolution_clock::now();

	double	diffVec = std::chrono::duration<double, std::micro>(end - start).count();
	bool	sortVec = std::is_sorted(this->_data_vector.begin(), this->_data_vector.end());
	bool	sortDeq = std::is_sorted(this->_data_deque.begin(), this->_data_deque.end());
	if (sortVec && sortDeq)
	{
		this->printVector();
		std::cout << "Vector sorted in " << diffVec << " microseconds" << std::endl;
		this->printDeque();
		std::cout << "Deque sorted in " << diffDq << " microseconds" << std::endl;
	}
	else
		std::cerr << "numbers are not sorted" << std::endl;
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
	std::vector<std::pair<iteratorVector, iteratorVector> > iteratorPairs(2);

	for (iteratorVector start = this->_data_vector.begin(); start != it_end; start = std::next(start, (size_pair * 2)))
	{
		iteratorPairs[0] = std::pair<iteratorVector, iteratorVector>(start, start + size_pair);
		iteratorPairs[1] = std::pair<iteratorVector, iteratorVector>(start + size_pair, start + (size_pair * 2));
		if (*std::prev(iteratorPairs[0].second) > *std::prev(iteratorPairs[1].second))
			std::rotate(iteratorPairs[0].first, iteratorPairs[1].first, iteratorPairs[1].second);
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

	createPairs(mainIndex, pendIndex, size_pair, this->_data_vector.size());
	while (true)
	{
		int temp;

		if (pendIndex.size() > currentJ - 2)
		{
			targetIndex = currentJ - 2;
			endIndex = currentJ + prevJ - 1;
		}
		else
		{
			targetIndex = pendIndex.size() - 1;
			endIndex = mainIndex.size() -1;
		}
		temp = targetIndex;
		while (targetIndex > endJ)
		{
			int index = BinarySearch(this->_data_vector, mainIndex, pendIndex[targetIndex] - 1, endIndex);
			insertPair(this->_data_vector, mainIndex, pendIndex, index, pendIndex[targetIndex], size_pair);
			--targetIndex;
		}
		endJ = temp;
		if (static_cast<size_t>(endJ) == pendIndex.size() - 1)
			break;
		nextJacobsthal(prevJ, currentJ);
	}
}

// Deque

void PmergeMe::printDeque(void)
{
	std::cout << "\033[32mDeque:\033[0m" << std::endl;
	for (iteratorDeque it = this->_data_deque.begin(); it != this->_data_deque.end(); ++it)
		std::cout << "\033[32m" << *it << " \033[0m";
	std::cout << std::endl;
}

void PmergeMe::fjmi_sort_deq(iteratorDeque it_end, int size_pair)
{
	if (size_pair == std::distance(this->_data_deque.begin(), it_end))
		return;
	while (std::distance(this->_data_deque.begin(), it_end) % (size_pair * 2) != 0)
		it_end = std::prev(it_end);
	merge_deque(it_end, size_pair);
	size_pair *= 2;
	this->fjmi_sort_deq(it_end, size_pair);
	this->insert_deque(it_end, size_pair);
}

void PmergeMe::merge_deque(iteratorDeque it_end, int size_pair)
{
	std::deque<std::pair<iteratorDeque, iteratorDeque> > iteratorPairs(2);

	for (iteratorDeque start = this->_data_deque.begin(); start != it_end; start = std::next(start, (size_pair * 2)))
	{
		iteratorPairs[0] = std::pair<iteratorDeque, iteratorDeque>(start, start + size_pair);
		iteratorPairs[1] = std::pair<iteratorDeque, iteratorDeque>(start + size_pair, start + (size_pair * 2));
		if (*std::prev(iteratorPairs[0].second) > *std::prev(iteratorPairs[1].second))
			std::rotate(iteratorPairs[0].first, iteratorPairs[1].first, iteratorPairs[1].second);
	}
}

void PmergeMe::insert_deque(iteratorDeque it_end, int size_pair)
{
	iteratorDeque start = this->_data_deque.begin();

	if (size_pair == std::distance(start, it_end) || std::distance(start, it_end) == 2)
		return;
	std::deque<int> mainIndex;
	std::deque<int> pendIndex;
	size_t currentJ = 3;
	size_t prevJ = 1;
	int endJ = -1;
	int targetIndex;
	int endIndex;

	createPairs(mainIndex, pendIndex, size_pair, this->_data_deque.size());
	while (true)
	{
		int temp;

		if (pendIndex.size() > currentJ - 2)
		{
			targetIndex = currentJ - 2;
			endIndex = currentJ + prevJ - 1;
		}
		else
		{
			targetIndex = pendIndex.size() - 1;
			endIndex = mainIndex.size() -1;
		}
		temp = targetIndex;
		while (targetIndex > endJ)
		{
			int index = BinarySearch(this->_data_deque, mainIndex, pendIndex[targetIndex] - 1, endIndex);
			insertPair(this->_data_deque, mainIndex, pendIndex, index, pendIndex[targetIndex], size_pair);
			--targetIndex;
		}
		endJ = temp;
		if (static_cast<size_t>(endJ) == pendIndex.size() - 1)
			break;
		nextJacobsthal(prevJ, currentJ);
	}
}

// Utils

void nextJacobsthal(size_t &prevJ, size_t &currentJ)
{
	size_t nextJ = currentJ + 2 * prevJ;
	prevJ = currentJ;
	currentJ = nextJ;
}