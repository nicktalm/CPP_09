/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:58:21 by ntalmon           #+#    #+#             */
/*   Updated: 2025/03/11 09:45:35 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename T>
void createPairs(T &Index_main, T &Index_pend, int size_pair, size_t containerSize)
{
	bool odd = true; // Flag zum abwechselnden Einfügen in Index_main und Index_pend

	Index_main.push_back(size_pair);
	Index_main.push_back(size_pair * 2);
	for (size_t size = size_pair * 3; size <= containerSize; size += size_pair)
	{
		if (odd)
			Index_pend.push_back(size); // Jeder zweite Eintrag geht in Index_pend
		else
			Index_main.push_back(size);
		odd = !odd; // Umschalten der Flag
	}
}

template <typename T>
int binarySearch(T &container, T Index_main, int targetIndex, int endIndex)
{
	int low = 0, mid, high = endIndex;
	int value = container[targetIndex]; // Wert an der gesuchten Position

	while (low <= high)
	{
		mid = low + (high - low) / 2; // Berechnung der Mitte
		if (static_cast<size_t>(mid) == Index_main.size())
			return mid; // Falls die Mitte außerhalb des Index_main liegt, abbrechen
		
		if (container[Index_main[mid] - 1] < value)
			low = mid + 1; // Suche im oberen Bereich fortsetzen
		else
			high = mid - 1; // Suche im unteren Bereich fortsetzen
	}
	return low; // Rückgabe der Position, an der der Wert eingefügt werden könnte
}

template <typename T>
void insertPair(T &container, T &Index_main, T &Index_pend, int indexMain, int indexPend, int size_pair)
{
	int startI;
	int startE = indexPend - size_pair;
	T input;

	// Bestimmen der Startposition für die Einfügung
	if (Index_main.begin() + indexMain != Index_main.end())
		startI = Index_main[indexMain] - size_pair;
	else
		startI = Index_main[indexMain - 1] + size_pair;

	// Falls die Position nicht bereits an der richtigen Stelle ist, wird verschoben
	if (startI != indexPend)
	{
		// Kopiere die relevanten Elemente in einen temporären Container
		std::copy(container.begin() + startE, container.begin() + indexPend, std::back_inserter(input));
		
		// Füge die Elemente an die neue Position ein
		container.insert(container.begin() + startI, input.begin(), input.end());

		// Entferne die alten Elemente an ihrer bisherigen Position
		typename T::iterator erase;
		if (startI < startE)
			erase = container.erase(container.begin() + startE + size_pair, container.begin() + indexPend + size_pair);
		else
			erase = container.erase(container.begin() + startE, container.begin() + indexPend);

		int tmp;
		if (startI < indexPend)
			tmp = Index_main[indexMain];
		else
			tmp = std::distance(container.begin(), erase) + size_pair;

		// Aktualisieren der Index-Werte in Index_main
		for (typename T::iterator it = Index_main.begin(); it != Index_main.end(); ++it)
		{
			if (*it > startI && *it < indexPend)
				*it += size_pair;
		}

		// Aktualisieren der Index-Werte in Index_pend
		for (typename T::iterator it = Index_pend.begin(); it != Index_pend.end(); ++it)
		{
			if (*it > startI && *it < indexPend)
				*it += size_pair;
		}

		// Finde die korrekte Position zum Einfügen in Index_main
		typename T::iterator pos = std::lower_bound(Index_main.begin(), Index_main.end(), tmp);
		int find = std::distance(Index_main.begin(), pos);
		Index_main.insert(Index_main.begin() + find, tmp);
	}
	else
	{
		// Falls die Position bereits korrekt ist, einfach hinzufügen
		Index_main.insert(Index_main.begin() + indexMain, indexPend);
	}
}