#pragma once



#include "matrix.h"
#include <stdexcept>;

namespace structures
{
	/// <summary> Implementacia matice v nesuvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class IncoherentMatrix
		: public Matrix<T>
	{
	private:
		Array<Array<T>*>* array_;
		size_t row;
		size_t col;
		size_t size_;
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		IncoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		IncoherentMatrix(IncoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~IncoherentMatrix();

		/// <summary>
		/// Ak je to mozne (parametrom je matica, ktora ma rovnake rozmery ako ako aktualna matica),
		/// tak skopiruje vlastnosti z matice odovzdanej ako parameter.
		/// Ak to nie je mozne, vyhodi sa vynimka.
		/// </summary>
		/// <param name = "other"> Odkaz na strukturu, z ktorej maju prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary>
		/// Ak je parametrom matica a obsah porovnavanych matic je rovnaky,
		/// tak vrati hodnotu true. V opacnom pripade vrati hodnotu false.
		/// </summary>
		/// <param name="other"> Odkaz na strukturu, s ktorou sa ma tato matica porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Pocet vsetkych prvkov v matici. </summary>
		/// <returns> Pocet prvkov v matici. </returns>
		size_t size() override;

		/// <summary> Vrati pocet riadkov v matici. </summary>
		/// <returns> Pocet riadkov matice. </returns>
		size_t getRowCount() override;

		/// <summary> Vrati pocet stlpcov matice. </summary>
		/// <returns> Pocet stlpcov matice. </returns>
		size_t getColumnCount() override;


		/// <summary> Vrati odkaz na prvok v danom riadku a stlpci. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// <returns> Odkaz na prvok na danych indexoch. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		T& at(int rowIndex, int columnIndex) override;

	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(size_t rowCount, size_t columnCount)
	{
		this->row = rowCount;
		this->col = columnCount;
		this->size_ = row * col;
		array_ = new Array<Array<T>*>(row);
		for (int i = 0; i < row; i++) {
			array_->at(i) = new Array<T>(col);

		}

	}

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(IncoherentMatrix& other)
	{
		size_t otherRow = other.getRowCount();
		size_t otherCol = other.getColumnCount();
		other = new Array<Array<T>*>(otherRow);

		for (int i = 0; i < otherRow; i++) {
			other.at(i) = new Array<T>(otherCol);

		}

	}

	template<typename T>
	inline IncoherentMatrix<T>::~IncoherentMatrix()
	{
		for (int i = 0; i < row; i++) {
			delete array_->at(i);
		}
		delete array_;
		array_ = nullptr;
	}

	template<typename T>
	inline Structure& IncoherentMatrix<T>::assign(Structure& other)
	{
		if (this == &other) {
			return *this;
		}
		IncoherentMatrix<T>& otherIncoherentMatrix = dynamic_cast<IncoherentMatrix<T>&>(other);
		if (this->row == otherIncoherentMatrix.getRowCount() && this->col == otherIncoherentMatrix.getColumnCount()) {
			for (int i; i < row; i++) {
				//Array<T> otherArray =  *otherIncoherentMatrix.array_->at(i);
				array_->at(i)->assign(*otherIncoherentMatrix.array_->at(i));

			}
			
		}
		return *this;
	}

	template<typename T>
	inline bool IncoherentMatrix<T>::equals(Structure& other)
	{
		if (this == &other) 
		{
			return true;
		}
		else 
		{
			IncoherentMatrix<T>* otherMatrix = dynamic_cast<IncoherentMatrix<T>*>(&other);
			if (otherMatrix != nullptr)
			{
				if (row == otherMatrix->getRowCount() && col == otherMatrix->getColumnCount()) 
				{
					for (int i; i < row; i++) 
					{
						
						if (!array_->at(i)->equals(*otherMatrix->array_->at(i))) 
						{
							return false;
						}
					}
					return true;
				}
			}
			return false;

		}
	}



	template<typename T>
	inline size_t IncoherentMatrix<T>::size()
	{
		return this->size_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getRowCount()
	{
		return this->row;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getColumnCount()
	{
		return this->col;
	}


	template<typename T>
	inline T& IncoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		//size_t columnT = static_cast<size_t>(columnIndex);
		return (*array_->at(rowIndex)).at((columnIndex));
	}
}
