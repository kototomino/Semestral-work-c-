#pragma once
#include "UzemnaJednotka.h"
#include <string>
#include "Enums.h"
//podla seminaru a prirucky
template <typename ResultType, typename ObjectType>
class Kriterium {
public:
	Kriterium() = default;
	virtual ResultType evaluate(const ObjectType object) = 0;

};
template <typename ResultType>
class KriteriumUJ : public Kriterium<ResultType, UzemnaJednotka*> {


};

class KriteriumNazov : public KriteriumUJ<std::string> {

public:
	KriteriumNazov() {};
	std::string evaluate(UzemnaJednotka* uj) {
		return uj->getNazov();
	}
};

class KriteriumUJTyp : public KriteriumUJ<Typ> {
public:
	KriteriumUJTyp() {};
	Typ evaluate(UzemnaJednotka* uj) {
		switch (uj->getTyp()) {
		case Typ::STAT:
			cout << " STAT";
			break;
		case Typ::KRAJ:
			cout << " KRAJ";
			break;
		case Typ::OKRES:
			cout << " OKRES";
			break;
		case Typ::OBEC:
			cout << " OBEC";
			break;
		default:
			break;
		}
		return uj->getTyp();
	}
};

class KriteriumUJPrislusnost : public KriteriumUJ<bool> {
private:
	UzemnaJednotka* prislusnostUJ_ = nullptr;
public:
	KriteriumUJPrislusnost(UzemnaJednotka* prislusnost) {
		prislusnostUJ_ = prislusnost;
	}
	bool evaluate(UzemnaJednotka* uj) {
		if (uj->getTyp() == Typ::OBEC) {
			if (uj->getMojeZaclenenie()->getMojeZaclenenie() == prislusnostUJ_) {
				return true;

			}
			else {
				return false;
			}
		} if (uj->getTyp() == Typ::OKRES) {
			if (uj->getMojeZaclenenie() == prislusnostUJ_) {
				return true;

			}
			else {
				return false;
			}
		}
		
		
	}
	void setPrislusnostUJ(UzemnaJednotka* uj) {
		prislusnostUJ_ = uj;
	}
};

class KriteriumUJVzdelaniePocet : public KriteriumUJ<int> {
private:
	int vzdelanieIndex_;
public:
	KriteriumUJVzdelaniePocet(int indexVzdelania) {
		vzdelanieIndex_ = indexVzdelania;
	}
	int evaluate(UzemnaJednotka* uj) {
		
		return uj->getVzdelanieAtIndex(vzdelanieIndex_);
	}
	void setVzdelaniePocetIndex(int index) {
		vzdelanieIndex_ = index;
	}
};

class KriteriumUJVzdelaniePodiel : public KriteriumUJ<double> {
private:
	int vzdelanieIndex_;
public:
	KriteriumUJVzdelaniePodiel(int indexVzdelania) {
		vzdelanieIndex_ = indexVzdelania;
	}
	double evaluate(UzemnaJednotka* uj){
		double vz = (double)uj->getVzdelanieAtIndex(vzdelanieIndex_);
		double po = (double)uj->getPocetObyvatelov();
		double percento = 100;
		if (po == 0) {
			return 0;
		}
		double vypocet = (vz) / (po);
		if (vypocet * percento <= 0) {
			return 0; 
		}
		else {
			return (vypocet) * (percento);
		}
		
	}
	void setVzdelaniePodielIndex(int index) {
		vzdelanieIndex_ = index;
	}
};

class KriteriumUJVekPocet : public KriteriumUJ<int> {
private:
	int vekIndex_;
	int odkial_;
	int pokial_;
	int pocet_;
public:
	KriteriumUJVekPocet(int indexVek) {
		vekIndex_ = indexVek;
		pocet_ = 0;
		odkial_ = 0;
		pokial_ = 0;

	}
	
	int evaluate(UzemnaJednotka* uj) {
		pocet_ = 0;
		for (int i = odkial_; i <= pokial_; i++)
		{
			pocet_ += uj->getVekAtIndex(i);
		}
		
		return pocet_;
	}
	void setVekPocetIndex(int index) {
		vekIndex_ = index;
	}
	void setVekPocetOdkial(int spodnaHranica) {
		odkial_ = spodnaHranica;
	}
	void setVekPocetPokial(int hornaHranica) {
		pokial_ = hornaHranica;
	}
	void setPocet_(int cislo) {
		pocet_ = cislo;
	}
	int getIndex() {
		return vekIndex_;
	}
	
};

class KriteriumUJVekPodiel : public KriteriumUJ<double> {
private:
	int vekIndex_;
	int odkial_;
	int pokial_;
	double podiel_;
	double pomocna_;
	double vypocet_;
public:
	KriteriumUJVekPodiel(int indexVek) {
		vekIndex_ = indexVek;
		odkial_ = 0;
		pokial_ = 0;
		podiel_ = 0;
		pomocna_ = 0;
		vypocet_ = 0;
	}
	double evaluate(UzemnaJednotka* uj) {
		
		double hranice = 0;
		double percento = 100;
		podiel_ = 0;
		vypocet_ = 0;
		pomocna_ = 0;
		for (int i = odkial_; i <= pokial_; i++)
		{
			pomocna_ += (double)uj->getVekAtIndex(i);
		}
		hranice = (double)pokial_ - (double)odkial_;
		if (pomocna_ <= 0) {
			return 0;
		}
		vypocet_ = pomocna_ / (double)uj->getPocetObyvatelov();
		if (vypocet_ <= 0) {
			return 0;
		}
		if (vypocet_ * percento <= 0) {
			return 0;
		}
		else {
			podiel_ = vypocet_ * percento;
			return podiel_;
		}
		
	}
	void setVekPodielIndex(int index) {
		vekIndex_ = index;
	}
	void setVekPodielOdkial(int spodnaHranica) {
		odkial_ = spodnaHranica;
	}
	void setVekPodielPokial(int hornaHranica) {
		pokial_ = hornaHranica;
	}
	void setPodiel_(int cislo) {
		podiel_ = cislo;
		pomocna_ = cislo;
		vypocet_ = 0;
	}
};

class KriteriumUJVekovaSkupinaPocet : public KriteriumUJ<int> {
private:
	int evsIndex_;
public:
	KriteriumUJVekovaSkupinaPocet(int indexEVS) {
		evsIndex_ = indexEVS;
	}
	int evaluate(UzemnaJednotka* uj) {
		return uj->getEvsAtIndex(evsIndex_);
	}
	void setEVSPocetIndex(int index) {
		evsIndex_ = index;
	}
};

class KriteriumUJVekovaSkupinaPodiel : public KriteriumUJ<double> {
private:
	int evsIndex_;
public:
	KriteriumUJVekovaSkupinaPodiel(int indexEVS) {
		evsIndex_ = indexEVS;
	}
	double evaluate(UzemnaJednotka* uj) {
		double vypocet = (double)uj->getEvsAtIndex(evsIndex_) / (double)uj->getPocetObyvatelov();
		return vypocet * 100;
	}
	void setEVSPodielIndex(int index) {
		evsIndex_ = index;
	}
};

class KriteriumUJNadradena : public KriteriumUJ<UzemnaJednotka*> {
public:
	KriteriumUJNadradena(){}
	UzemnaJednotka* evaluate(UzemnaJednotka* uj) {
		switch (uj->getMojeZaclenenie()->getTyp()) {
		case Typ::STAT:
			cout << " STAT / ";
			break;
		case Typ::KRAJ:
			cout << " KRAJ / ";
			break;
		case Typ::OKRES:
			cout << " OKRES / ";
			break;
		case Typ::OBEC:
			cout << " OBEC / ";
			break;
		default:
			break;


		}
		std::cout << uj->getMojeZaclenenie()->getNazov();
		return uj->getMojeZaclenenie();
	}
};
