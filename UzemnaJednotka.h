#pragma once
#include "Enums.h"
#include <string>
#include "structures/table/sorted_sequence_table.h"
#include "structures/array/array.h"
using namespace structures;
class UzemnaJednotka {
private:
	int id_UJ; // id uzemnej jednotky
	int pocet_Obyvatelov; // pocet obyvatelov UJ
	std::string nazov; //nazov UJ
	Typ typ_UJ; // Typ z enumu ciye stat kraj okres obec
	UzemnaJednotka* moje_Zaclenenie; // zaclenujem sa k predkovi cize ak obec tak moje zaclenenie je v okrese
	std::string kodJednotky; //kod jednotky z csv
	structures::Array<int>* vek;  //hodnoty z csv vek
	structures::Array<int>* vzdelanie; //hodnoty z csv vzdelanie
	structures::Array<int>* evs; // ekonomicka vekova skupina
	
public:
	UzemnaJednotka(int id, std::string meno, Typ typ) {
		this->id_UJ = id;
		this->nazov = meno;
		this->typ_UJ = typ;
		this->moje_Zaclenenie = nullptr;
		
		this->evs = new Array<int>(3);
		for (int i = 0; i < this->evs->size(); i++)
		{
			this->evs->at(i) = 0;
		}
		this->pocet_Obyvatelov = 0;
	}
	~UzemnaJednotka() {

		
		delete vek;
		delete vzdelanie;
		delete evs;


	}
	inline int getId_UJ() {
		return this->id_UJ;
	}
	inline void setId_UJ(int id) {
		this->id_UJ = id;
	}
	inline std::string getNazov() {
		return this->nazov;
	}
	void setNazov(std::string nazov) {
		this->nazov = nazov;
	}
	inline Typ getTyp() {

		return this->typ_UJ;
	}
	void setTyp(Typ typ) {
		this->typ_UJ = typ;
	}
	UzemnaJednotka* getMojeZaclenenie() {
		return this->moje_Zaclenenie;
	}
	void setMojeZaclenenie(UzemnaJednotka* uj) {
		this->moje_Zaclenenie = uj;
	}
	inline std::string getKod() {
		return this->kodJednotky;
	}
	void setKod(std::string kod) {
		this->kodJednotky = kod;
	}
	inline structures::Array<int>* getVek() {
		return this->vek;
	}inline structures::Array<int>* getVzdelanie() {
		return this->vzdelanie;
	}inline structures::Array<int>* getEvs() {
		return this->evs;
	}
	//navysovanie EVS VZDELANIA VEKU OBYVATELOV PRE PREDKOV
	inline void zvysEVS(structures::Array<int>* arrEVS) {
		for (int i = 0; i < this->evs->size(); i++)
		{
			this->evs->at(i) += arrEVS->at(i);

		}
	}
	inline void zvysPocetObyvatelov(structures::Array<int>* arrEVS) {
		for (int i = 0; i < this->evs->size(); i++)
		{
			this->pocet_Obyvatelov += arrEVS->at(i);

		}
	}

	inline void zvysVzdelanie(structures::Array<int>* arrVZD) {
		if (this->vzdelanie == nullptr) {
			this->vzdelanie = new Array<int>(8);
		}
		for (int i = 0; i < this->vzdelanie->size(); i++)
		{
			this->vzdelanie->at(i) += arrVZD->at(i);
		}
	}
	inline void zvysVek(structures::Array<int>* arrVek) {
		if (this->vek == nullptr) {
			this->vek = new Array<int>(202);
		}
		for (int i = 0; i < this->vek->size(); i++)
		{
			this->vek->at(i) += arrVek->at(i);
		}
	}

	void setVek(SortedSequenceTable<std::string, Array<int>*>* parameter) {
		this->vek = parameter->remove(kodJednotky);
	}
	void setVzdelanie(SortedSequenceTable<std::string, Array<int>*>* parameter) {
		this->vzdelanie = parameter->remove(kodJednotky);
	}
	int getPocetObyvatelov() {
		return this->pocet_Obyvatelov;
	}
	int getEvsAtIndex(int index) {
		if (index < this->evs->size()) {
			return this->evs->at(index);
		}
		else {
			throw std::range_error("neplatny index");
		}

	}
	int getVzdelanieAtIndex(int index) {
		if (index < this->vzdelanie->size()) {
			return this->vzdelanie->at(index);
		}
		else {
			throw std::range_error("neplatny index");
		}

	}
	int getVekAtIndex(int index) {
		if (index < this->vek->size()) {
			return this->vek->at(index);
		}
		else {
			throw std::range_error("neplatny index");
		}

	}
	// EVS INDEX 0 - 14  / 15 - 64 / 65 - 100+
	void setEvsPreObec() {
		// 0 po halfsize
		for (int i = 0; i < this->vek->size() / 2; i++)
		{
			if (i < 15) {
				this->evs->at(0) += this->vek->at(i);
			}
			else if (i < 65) {
				this->evs->at(1) += this->vek->at(i);
			}
			else {
				this->evs->at(2) += this->vek->at(i);
			}
		}
		//halfsize po size
		for (int i = this->vek->size() / 2; i < this->vek->size(); i++)
		{
			if (i < 116) {
				this->evs->at(0) += this->vek->at(i);
			}
			else if (i < 166) {
				this->evs->at(1) += this->vek->at(i);
			}
			else {
				this->evs->at(2) += this->vek->at(i);
			}
		}
	}
	//ak potrebujem vratit seba v pripade slovenska
	UzemnaJednotka* mojUkazovatel() {
		return this;
	}

};