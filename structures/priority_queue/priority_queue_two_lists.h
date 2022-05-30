#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include <cmath>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();

		PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T& peek() override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		int peekPriority() override;
	private:
		void handleLists();

	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;
		//size_t shortListSize_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;
		//size_t longListSize_;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		assign(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		clear();

	}

	template<typename T>
	Structure& PriorityQueueTwoLists<T>::assign(Structure& other)
	{
		if (this == &other) 
		{
			return *this;
		}

		PriorityQueueTwoLists& otherQueue = dynamic_cast<PriorityQueueTwoLists&>(other);
		shortList_->clear();
		shortList_->assign(*otherQueue.shortList_);
		longList_->clear();

		for (auto item : *otherQueue.longList_) 
		{
			longList_->add(new PriorityQueueItem<T>(*item));
		}

		return *this;
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size()
	{
		return shortList_->size() + longList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
		delete shortList_;
		shortList_ = nullptr;

		for (auto item : *longList_) {
			delete item;
		}
		delete longList_;
		longList_ = nullptr;


	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(int priority, const T& data)
	{
		if (shortList_->getCapacity() != shortList_->size()) 
		{
			shortList_->push(priority, data);
		}
		else if (longList_->size() == 0 || priority < shortList_->minPriority()) 
		{

			PriorityQueueItem<T>* removedItem = shortList_->pushAndRemove(priority, data);
			longList_->add(removedItem);

		}
		else 
		{
			PriorityQueueItem<T>* removedItem = new PriorityQueueItem<T>(priority, data);
			longList_->add(removedItem);

		}
		
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
		auto removedItem = shortList_->pop();
		
		if (shortList_->size() == 0 && longList_->size() != 0) {

			if (sqrt(longList_->size()) > 2) 
			{
				shortList_->trySetCapacity(sqrt(longList_->size()));
			}
			else 
			{
				shortList_->trySetCapacity(2); 
			}
			handleLists();
			
		}
		return removedItem;

	}

	template<typename T>
	T& PriorityQueueTwoLists<T>::peek()
	{
		if (longList_ - size() != 0 && shortList_->size() == 0)
		{
			this->handleLists();
		}
		return shortList_->peek();

	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority()
	{
		if (longList_ - size() != 0 && shortList_->size() == 0)
		{
			this->handleLists();
		}
		return shortList_->peekPriority();
	}


	//privatna metoda handleLists na usmernenie a rozdelenie danych listov
	template<typename T>
	inline void PriorityQueueTwoLists<T>::handleLists()
	{
		LinkedList<PriorityQueueItem<T>*>* copyList = new LinkedList<PriorityQueueItem<T>*>();

		while (longList_->size() != 0)
		{
			PriorityQueueItem<T>* item = longList_->removeAt(0);
			PriorityQueueItem<T>* removedItem = shortList_->pushAndRemove(item->getPriority(), item->accessData());
			delete item;
			if (removedItem != nullptr)
			{
				copyList->add(removedItem);
			}

		}
		longList_->clear();
		longList_->assign(*copyList);
		delete copyList;
	}
}