#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"
#include "..\..\..\Kriterium.h"

namespace structures
{
	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class QuickSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
		template<typename H>
		void quickSort(UnsortedSequenceTable<K, T>& table, int min, int max, Kriterium<H, T>& k, bool vzostupne);
		template<typename H>
		void quickSortMagic(UnsortedSequenceTable<K, T>& table, Kriterium<H, T>& k, bool vzostupne);

	};

	template<typename K, typename T>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		throw std::logic_error("Not implemented yet!");
	}
	template <typename K, typename T>
	template <typename H>
	void QuickSort<K, T>::quickSort(UnsortedSequenceTable<K, T>& table, int min, int max, Kriterium<H, T>& k, bool vzostupne)
	{
		//table item
		T obj = table.getItemAtIndex((min + max) / 2).accessData();
		//prvok podla coho
		H pivot = k.evaluate(obj);
		//lavy zaciatok pravy koniec
		int left = min;
		int right = max;
		if (vzostupne) {
			do
			{
				
				while (k.evaluate(table.getItemAtIndex(left).accessData()) < pivot)
				{
					left++;

				}
				while (k.evaluate(table.getItemAtIndex(right).accessData()) > pivot)
				{
					right--;

				}
				if (left <= right)
				{
					table.swap(left, right);
					left++;
					right--;
				}
			} while (left <= right);

			if (min < right)
			{
				quickSort(table, min, right, k, vzostupne);
			}
			if (left < max)
			{
				quickSort(table, left, max, k, vzostupne);
			}
		}
		else
		{
			do
			{
				while (k.evaluate(table.getItemAtIndex(left).accessData()) > pivot)
				{
					left++;

				}
				while (k.evaluate(table.getItemAtIndex(right).accessData()) < pivot)
				{
					right--;

				}
				if (left <= right)
				{
					table.swap(left, right);
					left++;
					right--;
				}
			} while (left <= right);

			if (min < right)
			{
				quickSort(table, min, right, k, vzostupne);
			}
			if (left < max)
			{
				quickSort(table, left, max, k, vzostupne);
			}
		}
	}

	template <typename K, typename T>
	template <typename H>
	//metoda napriamo pre sortovanie tabulky
	void QuickSort<K, T>::quickSortMagic(UnsortedSequenceTable<K, T>& table, Kriterium<H, T>& k, bool vzostupne)
	{
		quickSort(table, 0, table.size() - 1, k, vzostupne);
	}

}