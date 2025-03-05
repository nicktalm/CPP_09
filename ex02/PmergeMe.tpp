/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:58:21 by ntalmon           #+#    #+#             */
/*   Updated: 2025/03/05 11:29:17 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename T>
void createPairs(T &mainIndex, T &pendIndex, int size_pair, size_t size)
{
	bool odd = true;

	mainIndex.push_back(size_pair);
	pendIndex.push_back(size_pair * 2);
	for (size_t s = size_pair * 3; s <= size; s += size_pair)
	{
		if (odd)
			pendIndex.push_back(s);
		else
			mainIndex.push_back(s);
		odd = !odd;
	}
}

template <typename T>
int BinarySearch(T &container, T main, int target, int end)
{
	int low = 0, mid, high = end;
	int value = container[target];

	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (static_cast<size_t>(mid) == main.size())
			return mid;
		if (container[main[mid] - 1] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return low;
}

template <typename T>
void insertPair(T &container, T &main, T &pend, int index, int pendIndex, int size_pair)
{
	int startI;
	int startE = pendIndex - size_pair;
	T input;

	if (main.begin() + index != main.end())
		startI = main[index] - size_pair;
	else
		startI = main[index - 1] + size_pair;
	if (startI != pendIndex)
	{
		std::copy(container.begin() + startE, container.begin() + pendIndex, std::back_inserter(input));
		container.insert(container.begin() + startI, input.begin(), input.end());
		typename T::iterator erase;
		if (startI < startE)
			erase = container.erase(container.begin() + startE + size_pair, container.begin() + pendIndex + size_pair);
		else
			erase = container.erase(container.begin() + startE, container.begin() + pendIndex);
		int tmp;
		if (startI < pendIndex)
			tmp = main[index];
		else
			tmp = std::distance(container.begin(), erase) + size_pair;
		for (typename T::iterator it = main.begin(); it != main.end(); ++it)
		{
			if (*it > startI && *it < pendIndex)
				*it += size_pair;
		}
		for (typename T::iterator it = pend.begin(); it != pend.end(); ++it)
		{
			if (*it > startI && *it < pendIndex)
				*it += size_pair;
		}
		typename T::iterator pos = std::lower_bound(main.begin(), main.end(), tmp);
		int find = std::distance(main.begin(), pos);
		main.insert(main.begin() + find, tmp);
	}
	else
		main.insert(main.begin() + index, pendIndex);
}
