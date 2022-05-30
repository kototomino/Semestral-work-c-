#pragma once
#include "Kriterium.h"
#include "UzemnaJednotka.h"
template <typename ObjectType>
//podla seminaru a prirucky
class PredokFiltrov {
	//vlastny predok aby som vedel nasledne lepsie pracovat v liste pri vyhladavani
public:
	virtual bool splnaFilter(ObjectType o) = 0;
};
template <typename ResultType, typename ObjectType>
class Filter : public PredokFiltrov<ObjectType> {

protected:
	Kriterium<ResultType, ObjectType>* kriterium;
public:
	
	Filter(Kriterium<ResultType, ObjectType>* kriterium) {
		this->kriterium = kriterium;
	}
	 bool splnaFilter(ObjectType o) = 0;
};
template <typename ResultType, typename ObjectType>
class Filter_fi : public Filter<ResultType, ObjectType> {
private:
	ResultType alpha;
public:
	Filter_fi(Kriterium<ResultType,ObjectType>* kriterium) : Filter<ResultType, ObjectType>(kriterium), alpha(ResultType()) {
	}

	bool splnaFilter(ObjectType o) override {
		return Filter<ResultType,ObjectType>::kriterium->evaluate(o) == alpha;
	}

	void setAlpha(ResultType alpha)
	{
		this->alpha = alpha;
	}
};
template <typename ResultType, typename ObjectType>
class Filter_FI : public Filter<ResultType, ObjectType> {
private:
	ResultType alpha;
	ResultType beta;
public:
	Filter_FI(Kriterium<ResultType, ObjectType>* kriterium) : Filter<ResultType, ObjectType>(kriterium), alpha(ResultType()), beta(ResultType()) {
	}

	bool splnaFilter(ObjectType o) override {
		ResultType vysledok = Filter<ResultType, ObjectType>::kriterium->evaluate(o);

		return ((vysledok >= alpha) && (vysledok <= beta));
	}

	void setAlpha(ResultType alpha)
	{
		this->alpha = alpha;
	}

	void setBeta(ResultType beta)
	{
		this->beta = beta;
	}
	
};



