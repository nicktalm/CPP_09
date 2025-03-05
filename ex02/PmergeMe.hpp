/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:57:05 by ntalmon           #+#    #+#             */
/*   Updated: 2025/03/04 15:45:58 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <exception>
#include <stdexcept>

#include "PmergeMe.tpp"

class PmergeMe
{
	private:

		//vector
		std::vector<int> _data_vector;

		//deque
		std::deque<int> _deque_data;
	public:
		PmergeMe();
		PmergeMe(int ac, char **av);
		PmergeMe(const PmergeMe &src);
		PmergeMe &operator=(const PmergeMe &src);
		~PmergeMe();

		using iteratorDeque = std::deque<int>::iterator;
		using iteratorVector = std::vector<int>::iterator;
		
		static bool isPositiveInteger(const std::string& str);
		void fjmi_sort(void);
		void fjmi_sort_vec(iteratorVector it_end, int size_pair);
		void fjmi_sort_deq(iteratorDeque it_end, int size_pair);
		void merge_vector(iteratorVector it_end, int size_pair);
		void merge_deque(iteratorDeque it_begin, iteratorDeque it_end, int size_pair);
		void printVector(void);
		void printDeque(void);
		void insert_vector(iteratorVector it_end, int size_pair);
		void insert_deque(iteratorDeque it_end, int size_pair);
};

void nextJacobsthal(size_t &prevJ, size_t &currentJ);

template <typename T>
void createPairs(T &mainIndex, T &pendIndex, int size_pair, size_t size);

template <typename T>
int BinarySearch(T &contaienr, T main, int target, int end);

template <typename T>
void insertPair(T &container, T &mainIndex, T &pendIndex, int index, int target, int size_pair);