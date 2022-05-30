#pragma once

#include "matrix.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Implementacia matice v suvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class CoherentMatrix
		: public Matrix<T>
	{
	private:
		Array<T>* array_;
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
		CoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		CoherentMatrix(CoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~CoherentMatrix();

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
	inline CoherentMatrix<T>::CoherentMatrix(size_t rowCount, size_t columnCount)
	{
		this->row = rowCount;
		this->col = columnCount;
		this->size_ = row * col;

		this->array_ = new Array<T>(row * col);
	
	}

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(CoherentMatrix& other)
	{
		other.row = this->getRowCount();
		other.col = this->getColumnCount();
		other.size_ = this->size();

		other.array_ = new Array<T>(other.row * other.col);
	}

	template<typename T>
	inline CoherentMatrix<T>::~CoherentMatrix()
	{
		delete array_;
		array_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	inline Structure& CoherentMatrix<T>::assign(Structure& other)
	{
		if (this == &other) {
			return *this;
		}
		CoherentMatrix<T>& otherMatrix = dynamic_cast<CoherentMatrix<T>&>(other);
		if (row == otherMatrix.row && col == otherMatrix.col) {
			array_->assign(*otherMatrix.array_);
		}
		return *this;
	}

	template<typename T>
	inline bool CoherentMatrix<T>::equals(Structure& other)
	{
		if (this == &other) {
			return true;
		}
		CoherentMatrix<T>* otherMatrix = dynamic_cast<CoherentMatrix<T>*>(&other);
		if (row != otherMatrix->row && col != otherMatrix->col) { //porovnat cez riadky a stlpce
			return false;
		}
		if (otherMatrix != nullptr)
		{
			if (array_->equals(*otherMatrix->array_))
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::size()
	{
		return this->size_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getRowCount()
	{
		return this->row;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getColumnCount()
	{
		return this->col;
	}

	template<typename T>
	inline T& CoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		//size_t columnT = static_cast<size_t>(columnIndex);
		return (*array_).at((rowIndex * columnIndex)+ columnIndex);
	}
}