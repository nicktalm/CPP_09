/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:57:05 by ntalmon           #+#    #+#             */
/*   Updated: 2025/02/14 18:25:36 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <exception>
#include <stdexcept>

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
		
		static bool isPositiveInteger(const std::string& str);
		void fjmi_sort_vec(void);
		void fjmi_sort_deq(void);
		void merge_deque(iteratorDeque it_begin, iteratorDeque it_end, int size_pair);
};