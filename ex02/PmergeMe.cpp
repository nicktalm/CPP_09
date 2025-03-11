/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:56:53 by ntalmon           #+#    #+#             */
/*   Updated: 2025/03/11 09:34:21 by ntalmon          ###   ########.fr       */
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
			data_vector.push_back(std::stoi(av[i]));
			data_deque.push_back(std::stoi(av[i]));
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
	std::cout << "Before: ";
	for (int num : data_vector)
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
		data_vector = src.data_vector;
		data_deque = src.data_deque;
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

void	PmergeMe::sortNumbers(void)
{
	int						size_pair = 1;
	bool					odd = this->data_deque.size() > 1 && this->data_deque.size() % 2;
	IteratorVector			endVector = this->data_vector.end();
	IteratorDeque			endDeque = this->data_deque.end();

	std::chrono::time_point	start = std::chrono::high_resolution_clock::now();
	
	if (odd)
		endVector = std::prev(endVector);
	this->sort_vec(endVector, size_pair);
	this->insert_vec(size_pair);

	std::chrono::time_point	end = std::chrono::high_resolution_clock::now();
	double	diffVec = std::chrono::duration<double, std::micro>(end - start).count();
	start = std::chrono::high_resolution_clock::now();
	
	if (odd)
		endDeque = std::prev(endDeque);
	this->sort_deque(endDeque, size_pair);
	this->insert_deque(size_pair);
	
	end = std::chrono::high_resolution_clock::now();

	double	diffDq = std::chrono::duration<double, std::micro>(end - start).count();
	bool	sort_deq = std::is_sorted(this->data_deque.begin(), this->data_deque.end());
	bool	sort_vec = std::is_sorted(this->data_vector.begin(), this->data_vector.end());
	if (sort_vec && sort_deq)
		this->printResult(diffVec, diffDq);
	else
		std::cerr << "numbers not sorted" << std::endl;
}

// Vector

void	PmergeMe::sort_vec(IteratorVector ItEnd, int size_pair)
{
	// Abbruchbedingung: Falls die Größe des Paares der Distanz entspricht
	if (size_pair == std::distance(this->data_vector.begin(), ItEnd))
		return ;
	// Anpassung des End-Iterators an die Blockgröße
	while (std::distance(this->data_vector.begin(), ItEnd) % (size_pair * 2) != 0)
		ItEnd = std::prev(ItEnd);
	merge_vec(ItEnd, size_pair);
	size_pair *= 2;
	this->sort_vec(ItEnd, size_pair);
	this->insert_vec(size_pair);
}
void PmergeMe::merge_vec(IteratorVector ItEnd, int size_pair)
{
	std::pair<IteratorVector, IteratorVector> iteratorPair1, iteratorPair2;

	// Iteriert über die Vektor-Elemente in Blöcken der Größe size_pair * 2
	for (IteratorVector start = data_vector.begin(); start != ItEnd; std::advance(start, size_pair * 2))
	{
		iteratorPair1 = {start, std::next(start, size_pair)};
		iteratorPair2 = {std::next(start, size_pair), std::next(start, size_pair * 2)};
		// Falls das letzte Element des ersten Blocks größer ist als das letzte des zweiten Blocks, wird rotiert
		if (*std::prev(iteratorPair1.second) > *std::prev(iteratorPair2.second))
			std::rotate(iteratorPair1.first, iteratorPair2.first, iteratorPair2.second);
	}
}

void	PmergeMe::insert_vec(int size_pair)
{
	// Verwaltung der Haupt- und Nebenindizes für das Einfügen
	std::vector<int>	Index_main;
	std::vector<int>	Index_pend;
	int				endJ = -1;
	int				targetIndex;
	int				endIndex;
	size_t			currentJ = 3;
	size_t			previousJ = 1;

	createPairs(Index_main, Index_pend, size_pair, this->data_vector.size());
	while (true)
	{
		int	tmp;

		if (Index_pend.size() > currentJ - 2)
		{
			targetIndex = currentJ - 2;
			endIndex = currentJ + previousJ - 1;
		}
		else
		{
			targetIndex = Index_pend.size() - 1;
			endIndex = Index_main.size() - 1;
		}
		tmp = targetIndex;
		while (targetIndex > endJ)
		{
			int	index = binarySearch(this->data_vector, Index_main, Index_pend[targetIndex] - 1, endIndex);
			insertPair(this->data_vector, Index_main, Index_pend, index, Index_pend[targetIndex], size_pair);
			--targetIndex;
		}
		endJ = tmp;
		if (static_cast<size_t>(endJ) == Index_pend.size() - 1)
			break ;
		nextJacobsthal(previousJ, currentJ);
	}
}

// Deque

void	PmergeMe::sort_deque(IteratorDeque ItEnd, int size_pair)
{
	// Abbruchbedingung: Falls die Größe des Paares der Distanz entspricht
	if (size_pair == std::distance(this->data_deque.begin(), ItEnd))
		return ;
	// Anpassung des End-Iterators an die Blockgröße
	while (std::distance(this->data_deque.begin(), ItEnd) % (size_pair * 2) != 0)
		ItEnd = std::prev(ItEnd);
	merge_deque(ItEnd, size_pair);
	size_pair *= 2;
	this->sort_deque(ItEnd, size_pair);
	this->insert_deque(size_pair);
}

void PmergeMe::merge_deque(IteratorDeque ItEnd, int size_pair)
{
	std::pair<IteratorDeque, IteratorDeque> iteratorPair1, iteratorPair2;

	// Iteriert über die Vektor-Elemente in Blöcken der Größe size_pair * 2
	for (IteratorDeque start = data_deque.begin(); start != ItEnd; std::advance(start, size_pair * 2))
	{
		iteratorPair1 = {start, std::next(start, size_pair)};
		iteratorPair2 = {std::next(start, size_pair), std::next(start, size_pair * 2)};
		// Falls das letzte Element des ersten Blocks größer ist als das letzte des zweiten Blocks, wird rotiert
		if (*std::prev(iteratorPair1.second) > *std::prev(iteratorPair2.second))
			std::rotate(iteratorPair1.first, iteratorPair2.first, iteratorPair2.second);
	}
}

void	PmergeMe::insert_deque(int size_pair)
{
	// Verwaltung der Haupt- und Nebenindizes für das Einfügen
	std::deque<int>	Index_main;
	std::deque<int>	Index_pend;
	int				endJ = -1;
	int				targetIndex;
	int				endIndex;
	size_t			currentJ = 3;
	size_t			previousJ = 1;

	createPairs(Index_main, Index_pend, size_pair, this->data_deque.size());
	while (true)
	{
		int	tmp;

		if (Index_pend.size() > currentJ - 2)
		{
			targetIndex = currentJ - 2;
			endIndex = currentJ + previousJ - 1;
		}
		else
		{
			targetIndex = Index_pend.size() - 1;
			endIndex = Index_main.size() - 1;
		}
		tmp = targetIndex;
		while (targetIndex > endJ)
		{
			int	index = binarySearch(this->data_deque, Index_main, Index_pend[targetIndex] - 1, endIndex);
			insertPair(this->data_deque, Index_main, Index_pend, index, Index_pend[targetIndex], size_pair);
			--targetIndex;
		}
		endJ = tmp;
		if (static_cast<size_t>(endJ) == Index_pend.size() - 1)
			break ;
		nextJacobsthal(previousJ, currentJ);
	}
}

// Utils

void	nextJacobsthal(size_t &previousJ, size_t &currentJ)
{
	size_t	nextJ = currentJ + 2 * previousJ;
	previousJ = currentJ;
	currentJ = nextJ;
}

void PmergeMe::printResult(double diffVec, double diffDq)
{
	std::cout << "After: ";
	for (int num : data_vector)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << data_vector.size() << " elements with std::vector : ";
	std::cout << diffVec << " us" << std::endl;
	std::cout << "Time to process a range of " << data_deque.size() << " elements with std::deque : ";
	std::cout << diffDq << " us" << std::endl;
}