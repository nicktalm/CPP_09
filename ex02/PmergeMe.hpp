/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:57:05 by ntalmon           #+#    #+#             */
/*   Updated: 2025/03/06 15:42:31 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <chrono>
#include "PmergeMe.tpp"

class PmergeMe
{
	private:
		std::deque<int>		data_deque;
		std::vector<int>	data_vector;
	public:
		using	IteratorDeque = std::deque<int>::iterator;
		using	IteratorVector = std::vector<int>::iterator;

		PmergeMe(void);
		PmergeMe(int ac, char **av);
		PmergeMe(const PmergeMe &cpy);
		PmergeMe	&operator= (const PmergeMe &cpy);
		~PmergeMe(void);
		
		void		sortNumbers(void);
		void		printResult(double diffDq, double diffVec);
		static bool	isPositiveInteger(const std::string &str);

		void		sort_deque(IteratorDeque ItEnd, int size_pair);
		void		merge_deque(IteratorDeque ItEnd, int size_pair);
		void		insert_deque(IteratorDeque end, int size_pair);

		void		sort_vec(IteratorVector ItEnd, int size_pair);
		void		merge_vec(IteratorVector ItEnd, int size_pair);
		void		insert_vec(IteratorVector ItEnd, int size_pair);
};

void	nextJacobsthal(size_t &prevJ, size_t &currJ);

template <typename T>
void	createPairs(T &mainIndex, T &pendIndex, int size_pair, size_t containerSize);

template <typename T>
int		binarySearch(T &container, T mainIndex, int targetIndex, int endIndex);

template <typename T>
void	insertPair(T &container, T &mainIndex, T &pendIndex, int indexMain, int indexPend, int size_pair);
