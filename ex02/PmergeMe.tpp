/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:58:21 by ntalmon           #+#    #+#             */
/*   Updated: 2025/03/10 16:00:00 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename T>
void	createPairs(T &Index_main, T &Index_pend, int size_pair, size_t containerSize)
{
	bool	odd = true;

	Index_main.push_back(size_pair);
	Index_main.push_back(size_pair * 2);
	for (size_t size = size_pair * 3; size <= containerSize; size += size_pair)
	{
		if (odd)
			Index_pend.push_back(size);
		else
			Index_main.push_back(size);
		odd = !odd;
	}
}

template <typename T>
int	binarySearch(T &container, T Index_main, int targetIndex, int endIndex)
{
	int	low = 0, mid, high = endIndex;
	int	value = container[targetIndex];

	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (static_cast<size_t>(mid) == Index_main.size())
			return (mid) ;
		if (container[Index_main[mid] - 1] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (low);
}

template <typename T>
void	insertPair(T &container, T &Index_main, T &Index_pend, int indexMain, int indexPend, int size_pair)
{
	int	startI;
	int	startE = indexPend - size_pair;
	T	input;

	if (Index_main.begin() + indexMain != Index_main.end())
		startI = Index_main[indexMain] - size_pair;
	else
		startI = Index_main[indexMain - 1] + size_pair;
	if (startI != indexPend)
	{
		std::copy(container.begin() + startE, container.begin() + indexPend, std::back_inserter(input));
		container.insert(container.begin() + startI, input.begin(), input.end());
		typename T::iterator	erase;
		if (startI < startE)
			erase = container.erase(container.begin() + startE + size_pair, container.begin() + indexPend + size_pair);
		else
			erase = container.erase(container.begin() + startE, container.begin() + indexPend);
		int	tmp;
		if (startI < indexPend)
			tmp = Index_main[indexMain];
		else
			tmp = std::distance(container.begin(), erase) + size_pair;
		for (typename T::iterator it = Index_main.begin(); it != Index_main.end(); ++it)
		{
			if (*it > startI && *it < indexPend)
				*it += size_pair;
		}
		for (typename T::iterator it = Index_pend.begin(); it != Index_pend.end(); ++it)
		{
			if (*it > startI && *it < indexPend)
				*it += size_pair;
		}
		typename T::iterator	pos = std::lower_bound(Index_main.begin(), Index_main.end(), tmp);
		int		find = std::distance(Index_main.begin(), pos);
		Index_main.insert(Index_main.begin() + find, tmp);
	}
	else
		Index_main.insert(Index_main.begin() + indexMain, indexPend);
}
