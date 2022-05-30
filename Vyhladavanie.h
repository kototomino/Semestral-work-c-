#pragma once
#include "UzemnaJednotka.h"
#include <iostream>
#include "Kriterium.h"
#include "Filter.h"
#include "structures/table/unsorted_sequence_table.h"
#include "structures/table/sorting/quick_sort.h"

using namespace std;
class Vyhladavanie {
private:
	int volba;
	int sortVolba = 0;
	string strasnePeknyRamik = "************************************";
	int iterator = 0;
	int iteratorOkresov = 0;
	int iteratorObcii = 0;
	int counterPreSkipnutieSlovenska = 0;
	int vybrateKriteriumPreFilter = 0;
	int alpha = 0;
	int beta = 0;
	int indexVzdelaniaPocet = 0;
	int indexVzdelaniaPodiel = 0;
	int counterPreVypisovanieFiltrov = 0;
	string vybranyKraj = "";
	string vybranyOkres = "";
	string vybranaObec = "";
	string vyber = "";
	string cakamKlavesu = "CAKAM KLAVESU >>> ";
	int cislo = 0;
	bool opakuj = true;
	//arrayList filtrov pre prechadzanie a kontrolu bool splnaFilter
	ArrayList <PredokFiltrov<UzemnaJednotka*>*>* listFiltrov = new ArrayList<PredokFiltrov<UzemnaJednotka*>*>();
	//vystupna tabulka ktora sa bude sortovat
	UnsortedSequenceTable<std::string, UzemnaJednotka*>* vystupnaTabulka;
	int pocetFiltrov = 0;
	//KRITERIA
	KriteriumNazov* kriteriumNazov = new KriteriumNazov();
	KriteriumUJVzdelaniePocet* kriteriumUJVZPocet = new KriteriumUJVzdelaniePocet(0);
	KriteriumUJVzdelaniePodiel* kriteriumUJVZPodiel = new KriteriumUJVzdelaniePodiel(0);
	KriteriumUJTyp* kriteriumUJTyp = new KriteriumUJTyp();
	KriteriumUJNadradena* kriteriumUJNadradena = new KriteriumUJNadradena();
	KriteriumUJPrislusnost* kriteriumUJPrislusnost = new KriteriumUJPrislusnost(nullptr);
	KriteriumUJVekPocet* kriteriumUJVekPocet = new KriteriumUJVekPocet(0);
	KriteriumUJVekPodiel* kriteriumUJVekPodiel = new KriteriumUJVekPodiel(0);
	KriteriumUJVekovaSkupinaPocet* kriteriumUJVekovaSkupinaPocet = new KriteriumUJVekovaSkupinaPocet(0);
	KriteriumUJVekovaSkupinaPodiel* kriteriumUJVekovaSkupinaPodiel = new KriteriumUJVekovaSkupinaPodiel(0);
	//FILTRE fi
	Filter_fi<std::string, UzemnaJednotka*>* filterNazov = new Filter_fi<std::string, UzemnaJednotka*>(kriteriumNazov);
	Filter_fi<Typ, UzemnaJednotka*>* filterUJTyp = new Filter_fi<Typ, UzemnaJednotka*>(kriteriumUJTyp);
	Filter_fi<bool, UzemnaJednotka*>* filterUJPrislusnost = new Filter_fi<bool, UzemnaJednotka*>(kriteriumUJPrislusnost);
	//FILTRE FI
	Filter_FI<int, UzemnaJednotka*>* filterVzdelaniePocet = new Filter_FI<int, UzemnaJednotka*>(kriteriumUJVZPocet);
	Filter_FI<double, UzemnaJednotka*>* filterVzdelaniePodiel = new Filter_FI<double, UzemnaJednotka*>(kriteriumUJVZPodiel);
	Filter_FI<int, UzemnaJednotka*>* filterVekPocet = new Filter_FI<int, UzemnaJednotka*>(kriteriumUJVekPocet);
	Filter_FI<double, UzemnaJednotka*>* filterVekPodiel = new Filter_FI<double, UzemnaJednotka*>(kriteriumUJVekPodiel);
	Filter_FI<int, UzemnaJednotka*>* filterVekovaSkupinaPocet = new Filter_FI<int, UzemnaJednotka*>(kriteriumUJVekovaSkupinaPocet);
	Filter_FI<double, UzemnaJednotka*>* filterVekovaSkupinaPodiel = new Filter_FI<double, UzemnaJednotka*>(kriteriumUJVekovaSkupinaPodiel);





public:

	Vyhladavanie(SortedSequenceTable<std::string, UzemnaJednotka*>* krajeParam,
		SortedSequenceTable<std::string, UzemnaJednotka*>* okresyParam,
		SortedSequenceTable<std::string, UzemnaJednotka*>* obceParam);
	~Vyhladavanie();
	void hodnotyKriterii(TableItem<std::string, UzemnaJednotka*>* item);
	void vypisKriteriaNazov(UzemnaJednotka* uj);
	void vypisKriteriaUJTyp(UzemnaJednotka* uj);
	void vypisKriteriaUJPrislusnost(UzemnaJednotka* uj);
	void vypisKriteriaNadradena(UzemnaJednotka* uj);
	void vypisKriteriaUJVzdelaniePocet(UzemnaJednotka* uj, int indexVzdelania);
	void vypisKriteriaUJVzdelaniePodiel(UzemnaJednotka* uj, int indexVzdelania);
	void vypisKriteriaUJVekPocet(UzemnaJednotka* uj, int indexVzdelania);
	void vypisKriteriaUJVekPodiel(UzemnaJednotka* uj, int indexVzdelania);
	void vypisKriteriaUJVekovaSkupinaPocet(UzemnaJednotka* uj, int evsIndex);
	void vypisKriteriaUJVekovaSkupinaPodiel(UzemnaJednotka* uj, int evsIndex);
	void vypisFilter(std::string zvolenaUJ, int mozem, SortedSequenceTable<std::string, UzemnaJednotka*>* zvolenaTabulka, SortedSequenceTable<std::string, UzemnaJednotka*>* prislusnost);
	void zaznamenajHraniceFiltrov(int volba, std::string nazov, UzemnaJednotka* uj, int spodnaHranica, int hornaHranica);
	void pridajDoListuFiltrov(int volbaPodla);
	void sortOtazky();
	void sortujNeutriedenuTabulku(UnsortedSequenceTable<std::string, UzemnaJednotka*>* neutriedena, int podlaCoho, bool vzostupne,bool prazdna);



};
inline Vyhladavanie::Vyhladavanie(SortedSequenceTable<std::string, UzemnaJednotka*>* obceParam,
	SortedSequenceTable<std::string, UzemnaJednotka*>* okresyParam,
	SortedSequenceTable<std::string, UzemnaJednotka*>* krajeParam) {

	
	while (opakuj) {
		// inicializovanie parametrov
		//nastavujem na nulu kvoli opatovnej iteracii cyklu
		SortedSequenceTable<std::string, UzemnaJednotka*>* obce = obceParam;
		SortedSequenceTable<std::string, UzemnaJednotka*>* okresy = okresyParam;
		SortedSequenceTable<std::string, UzemnaJednotka*>* kraje = krajeParam;
		vystupnaTabulka = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
		Array<UzemnaJednotka*>* arrayKrajovychVolieb = new Array<UzemnaJednotka*>(kraje->size());
		Array<UzemnaJednotka*>* arrayOkresovychVolieb = new Array<UzemnaJednotka*>(okresy->size());
		Array<UzemnaJednotka*>* arrayObciVolieb = new Array<UzemnaJednotka*>(obce->size());
		

		delete listFiltrov;
		listFiltrov = new ArrayList<PredokFiltrov<UzemnaJednotka*>*>();
		pocetFiltrov = 0;
		counterPreVypisovanieFiltrov = 0;
		iterator = 0;
		iteratorOkresov = 0;
		iteratorObcii = 0;
		counterPreSkipnutieSlovenska = 0;
		vybrateKriteriumPreFilter = 0;
		alpha = 0;
		beta = 0;
		volba = 0;
		cislo = 0;
		indexVzdelaniaPocet = 0;
		indexVzdelaniaPodiel = 0;
		//PRVOTNY VYPIS
		std::cout << "TOTO JE MENU STLAC KLAVESU" << std::endl << strasnePeknyRamik << endl;
		std::cout << "*1*	BODOVE VYHLADAVANIE " << endl;
		std::cout << "*2*	FILTROVANIE " << endl;
		std::cout << "*3*	UKONCENIE PROGRAMU " << endl;
		std::cout << strasnePeknyRamik << endl;
		std::cout << cakamKlavesu;
		cin >> volba;

		

		//SWITCH CASE NA VYBER  1 bodove vyhladavanie 2 filtrovanie 3 ukoncenie
		switch (volba) {
		case 1:
			system("CLS");
			//najprv najdem slovensko vypisem
			for (auto kraj : *kraje) {
				if (kraj->accessData()->getTyp() == Typ::STAT) {
					hodnotyKriterii(kraj);
					cout << endl;
					break;
				}
			}

			//najdem kraje vypisem nazvy z ktorych si moze uzivatel vybrat slovensko skipujem lebo uz bolo zobrazene
			cout << strasnePeknyRamik << endl;
			cout << "TOTO SU KRAJE" << endl;
			cout << "ZADAJ KRAJ" << endl;
			cout << strasnePeknyRamik << endl;
			for (auto kraj : *kraje) {
				if (counterPreSkipnutieSlovenska == 5) {
					counterPreSkipnutieSlovenska++;

				}
				else {
					cout << "*" << cislo << "* ";
					vypisKriteriaNazov(kraj->accessData());
					cout << endl;
					cislo++;
					counterPreSkipnutieSlovenska++;
				}

			}
			cout << "*-1* SPAT DO MENU" << endl;
			std::cout << strasnePeknyRamik << endl;
			std::cout << cakamKlavesu;
			cin >> volba;
			//ak zadam viac ako je krajov tak naspat
			if (volba > 7) {
				opakuj = true;

			}
			else {
				cislo = 0;
				counterPreSkipnutieSlovenska = 0;
				for (auto kraj : *kraje) {
					if (counterPreSkipnutieSlovenska == 5) {
						counterPreSkipnutieSlovenska++;

					}
					else {
						arrayKrajovychVolieb->at(iterator) = kraj->accessData();
						iterator++;
						counterPreSkipnutieSlovenska++;

					}


				}
				if (volba == -1) {
					system("CLS");

					break;
				}
				//ak som si vybral tak ukazem co som si vybral
				for (int i = 0; i < arrayKrajovychVolieb->size(); i++) {
					if (volba == i) {
						vybranyKraj = arrayKrajovychVolieb->at(volba)->getNazov();
						cout << "VYBRAL SI SI " << vybranyKraj << endl;
						cout << strasnePeknyRamik << endl;
						for (auto kraj : *kraje) {
							if (arrayKrajovychVolieb->at(i) == kraj->accessData()) {
								cout << endl;
								hodnotyKriterii(kraj);
								cout << endl;
							}
						}

						cout << strasnePeknyRamik << endl;
						cout << "PRE ZVOLENY KRAJ SU NASLEDOVNE OKRESY " << endl;
						cout << "ZADAJ OKRES" << endl;
						cout << strasnePeknyRamik << endl;
						//vypisem okresy prisluchajuce k zvolenemu kraju
						for (auto okres : *okresy) {
							if (arrayKrajovychVolieb->at(i) == okres->accessData()->getMojeZaclenenie()) {
								cout << "*" << cislo << "* ";
								vypisKriteriaNazov(okres->accessData());
								cout << endl;
								cislo++;
							}

						}
					}
				}
				std::cout << strasnePeknyRamik << endl;
				std::cout << cakamKlavesu;


				cin >> volba;
				cislo = 0;

				for (auto okres : *okresy) {
					if (vybranyKraj == okres->accessData()->getMojeZaclenenie()->getNazov()) {
						arrayOkresovychVolieb->at(iteratorOkresov) = okres->accessData();
						iteratorOkresov++;
					}


				}

				for (int i = 0; i < arrayOkresovychVolieb->size(); i++) {
					if (volba == i) {
						vybranyOkres = arrayOkresovychVolieb->at(volba)->getNazov();
						cout << "VYBRAL SI SI " << vybranyOkres << endl;
						cout << strasnePeknyRamik << endl;
						for (auto okres : *okresy) {
							if (arrayOkresovychVolieb->at(i) == okres->accessData()) {
								cout << endl;
								hodnotyKriterii(okres);
								cout << endl;
							}
						}
						//napokon obce
						cout << strasnePeknyRamik << endl;
						cout << "PRE ZVOLENY OKRES SU NASLEDOVNE OBCE " << endl;
						cout << "ZADAJ OBEC " << endl;
						cout << strasnePeknyRamik << endl;
						for (auto obec : *obce) {
							if (arrayOkresovychVolieb->at(i) == obec->accessData()->getMojeZaclenenie()) {
								cout << "*" << cislo << "* ";
								vypisKriteriaNazov(obec->accessData());
								cout << endl;
								cislo++;
							}

						}
					}
				}
				std::cout << strasnePeknyRamik << endl;
				std::cout << cakamKlavesu;
				cin >> volba;
				cislo = 0;
				for (auto obec : *obce) {
					if (vybranyOkres == obec->accessData()->getMojeZaclenenie()->getNazov()) {
						arrayObciVolieb->at(iteratorObcii) = obec->accessData();
						iteratorObcii++;
					}
				}
				//vypisem hodnoty zvolenej obce
				for (int i = 0; i < arrayObciVolieb->size(); i++) {
					if (volba == i) {
						vybranaObec = arrayObciVolieb->at(volba)->getNazov();
						cout << "VYBRAL SI SI " << vybranaObec << endl;
						cout << strasnePeknyRamik << endl;
						for (auto obec : *obce) {
							if (arrayObciVolieb->at(i) == obec->accessData()) {
								cout << endl;
								hodnotyKriterii(obec);

							}
						}
					}
				}
			}
			cout << strasnePeknyRamik << endl;
			// ak 1 tak odznova ak 0 alebo else tak ukonci
			cout << "AK SA CHCES VRATIT NA ZACIATOK STLAC 1 AK UKONCIT STLAC 0" << endl;
			cout << cakamKlavesu;
			cin >> volba;
			if (volba == 1) {
				system("CLS");
				opakuj = true;

			}
			else {
				system("CLS");
				break;
			}
			break;
		case 2:
			//*********************FILTROVANIE***********************************
			system("CLS");
			cout << strasnePeknyRamik << endl;
			//vyber z filtrovanych mnozin 
			cout << "TOTO JE FILTROVANIE ZADAJ UZEMNU JEDNOTKU KTORU CHCES FILTORVAT" << endl;
			cout << "*0*	KRAJ" << endl;
			cout << "*1*	OKRES" << endl;
			cout << "*2*	OBEC" << endl;
			cout << "*-1*	SPAT DO MENU" << endl;
			cout << strasnePeknyRamik << endl;
			cout << cakamKlavesu;
			cin >> volba;
			if (volba == 0) {
				system("CLS");

				cout << "VYBRAL SI SI FILTROVANIE KRAJOV" << endl;
				cout << strasnePeknyRamik << endl;
				cout << "ZADAJ KOLKO FILTROV CHCES POUZIT" << endl;
				cout << cakamKlavesu;
				cin >> pocetFiltrov;
				// ak zada 0 filtrov tak prejde na triedenie vsetkeho z mnoziny

				if (pocetFiltrov == 0) {
					for (auto kraj : *kraje) {
						vystupnaTabulka->insert(kraj->accessData()->getNazov(), kraj->accessData());
					}
					cout << strasnePeknyRamik << endl;
					for (auto item : *vystupnaTabulka) {
						vypisKriteriaNazov(item->accessData());
						
						cout << endl;
					}
				}
				else {
					//vypisanie moznosti filtrovania
					//zopakuje sa tolko krat kolko chce uzivatel filtrov
					system("CLS");
					for (int i = 0; i < pocetFiltrov; i++)
					{
						cout << strasnePeknyRamik << endl;
						cout << "ZADAJ SI FILTER" << endl;
						cout << "*0*	UJ NAZOV" << endl;
						cout << "*1*	UJ PRISLUSNOST" << endl;
						cout << "*2*	VZDELANIE POCET" << endl;
						cout << "*3*	VZDELANIE PODIEL" << endl;
						cout << "*4*	VEK POCET" << endl;
						cout << "*5*	VEK PODIEL" << endl;
						cout << "*6*	EKONOMICKA VEKOVA SKUPINA POCET" << endl;
						cout << "*7*	EKONOMICKA VEKOVA SKUPINA PODIEL" << endl;
						cout << strasnePeknyRamik << endl;
						cout << cakamKlavesu;
						cin >> vybrateKriteriumPreFilter;
						//co zadam to mi prida do listu
						pridajDoListuFiltrov(vybrateKriteriumPreFilter);
						//tu posielam posledne kraje vzdy lebo to je pred prislusnost
						vypisFilter("KRAJE", pocetFiltrov, kraje, kraje);

					}
				}
				//vysledny pocet uj
				cout << "PRE MNOZINU " << "KRAJE" << " SA VYFILTROVALO " << vystupnaTabulka->size() << " UZEMNYCH JEDNOTIEK " << endl;
				//prechadzam na sort
				sortOtazky();
				//tabulku vycistim aby pre dalsi cyklus tam nebolo nic
				vystupnaTabulka->clear();
				cout << strasnePeknyRamik << endl;
				//vetva spat a von

				cout << "AK SA CHCES VRATIT NA ZACIATOK STLAC 1 AK UKONCIT STLAC 0" << endl;
				cout << cakamKlavesu;
				cin >> volba;
				if (volba == 1) {
					system("CLS");
					opakuj = true;
					break;
				}
				else {
					opakuj = false;
					break;
				}


			}
			else if (volba == 1) {
				//to iste co pre kraj
				system("CLS");
				cout << "VYBRAL SI SI FILTROVANIE OKRESOV" << endl;
				cout << strasnePeknyRamik << endl;
				cout << "ZADAJ KOLKO FILTROV CHCES POUZIT" << endl;
				cout << cakamKlavesu;
				cin >> pocetFiltrov;
				if (pocetFiltrov == 0) {
					for (auto okres : *okresy) {
						vystupnaTabulka->insert(okres->accessData()->getNazov(), okres->accessData());
					}
					cout << strasnePeknyRamik << endl;
					for (auto item : *vystupnaTabulka) {
						vypisKriteriaNazov(item->accessData());
						cout << endl;
					}
				}
				else {
					system("CLS");
					for (int i = 0; i < pocetFiltrov; i++)
					{
						cout << strasnePeknyRamik << endl;
						cout << "ZADAJ SI FILTER" << endl;
						cout << "*0*	UJ NAZOV" << endl;
						cout << "*1*	UJ PRISLUSNOST" << endl;
						cout << "*2*	VZDELANIE POCET" << endl;
						cout << "*3*	VZDELANIE PODIEL" << endl;
						cout << "*4*	VEK POCET" << endl;
						cout << "*5*	VEK PODIEL" << endl;
						cout << "*6*	EKONOMICKA VEKOVA SKUPINA POCET" << endl;
						cout << "*7*	EKONOMICKA VEKOVA SKUPINA PODIEL" << endl;
						cout << strasnePeknyRamik << endl;
						cout << cakamKlavesu;
						cin >> vybrateKriteriumPreFilter;
						pridajDoListuFiltrov(vybrateKriteriumPreFilter);
						vypisFilter("OKRESY", pocetFiltrov, okresy, kraje);

					}
				}
				cout << "PRE MNOZINU " << "OKRESY" << " SA VYFILTROVALO " << vystupnaTabulka->size() << " UZEMNYCH JEDNOTIEK " << endl;
				sortOtazky();
				vystupnaTabulka->clear();
				cout << strasnePeknyRamik << endl;
				cout << "AK SA CHCES VRATIT NA ZACIATOK STLAC 1 AK UKONCIT STLAC 0" << endl;
				cout << cakamKlavesu;
				cin >> volba;
				if (volba == 1) {
					system("CLS");
					opakuj = true;
					break;
				}
				else {
					opakuj = false;
		
				}
			}
			else if (volba == 2) {
				system("CLS");
				//to iste co pre okres a kraj
				cout << "VYBRAL SI SI FILTROVANIE OBCI" << endl;
				cout << strasnePeknyRamik << endl;
				cout << "ZADAJ KOLKO FILTROV CHCES POUZIT" << endl;
				cout << cakamKlavesu;
				cin >> pocetFiltrov;
				system("CLS");
				if (pocetFiltrov == 0) {
					for (auto obec : *obce) {
						vystupnaTabulka->insert(obec->accessData()->getNazov(), obec->accessData());
					}
					cout << strasnePeknyRamik << endl;
					for (auto item : *vystupnaTabulka) {
						vypisKriteriaNazov(item->accessData());
						cout << endl;
					}
				}
				else {
					for (int i = 0; i < pocetFiltrov; i++)
					{
						cout << strasnePeknyRamik << endl;
						cout << "ZADAJ SI FILTER" << endl;
						cout << "*0*	UJ NAZOV" << endl;
						cout << "*1*	UJ PRISLUSNOST" << endl;
						cout << "*2*	VZDELANIE POCET" << endl;
						cout << "*3*	VZDELANIE PODIEL" << endl;
						cout << "*4*	VEK POCET" << endl;
						cout << "*5*	VEK PODIEL" << endl;
						cout << "*6*	EKONOMICKA VEKOVA SKUPINA POCET" << endl;
						cout << "*7*	EKONOMICKA VEKOVA SKUPINA PODIEL" << endl;
						cout << strasnePeknyRamik << endl;
						cout << cakamKlavesu;
						cin >> vybrateKriteriumPreFilter;
	
						pridajDoListuFiltrov(vybrateKriteriumPreFilter);
						vypisFilter("OBCE", pocetFiltrov, obce, kraje);

					}
				}

				cout << "PRE MNOZINU " << "OBCE" << " SA VYFILTROVALO " << vystupnaTabulka->size() << " UZEMNYCH JEDNOTIEK " << endl;
				sortOtazky();
				vystupnaTabulka->clear();
				cout << strasnePeknyRamik << endl;
				cout << "AK SA CHCES VRATIT NA ZACIATOK STLAC 1 AK UKONCIT STLAC 0" << endl;
				cout << cakamKlavesu;
				cin >> volba;
				if (volba == 1) {
					system("CLS");
					opakuj = true;
					break;
				}
				else {
					system("CLS");
					opakuj = false;

				}

			}
			else {
				system("CLS");
				opakuj = true;
				break;
			}
			

		case 3:
			system("CLS");

			cout << "AUS SEM TOMAS KOTRIK";
			opakuj = false;
			break;
		default:
			system("CLS");
			opakuj = true;
			break;
		}
		//delete vsetkych dostupnych moznosti cez ktore uzivatel prechadzal
		delete arrayKrajovychVolieb;
		delete arrayObciVolieb;
		delete arrayOkresovychVolieb;
		delete vystupnaTabulka;
	}



}

inline Vyhladavanie::~Vyhladavanie()
{
	//KRITERIA
	delete kriteriumNazov;
	delete kriteriumUJVZPocet;
	delete kriteriumUJVZPodiel;
	delete kriteriumUJTyp;
	delete kriteriumUJNadradena;
	delete kriteriumUJPrislusnost;
	delete kriteriumUJVekPocet;
	delete kriteriumUJVekPodiel;
	delete kriteriumUJVekovaSkupinaPocet;
	delete kriteriumUJVekovaSkupinaPodiel;
	//FILTRE fi
	delete filterNazov;
	delete filterUJTyp;
	delete filterUJPrislusnost;
	//FILTRE FI
	delete filterVzdelaniePocet;
	delete filterVzdelaniePodiel;
	delete filterVekPocet;
	delete filterVekPodiel;
	delete filterVekovaSkupinaPocet;
	delete filterVekovaSkupinaPodiel;
	//array
	delete listFiltrov;
	//delete vystupnaTabulka;
	//delete quickSort;
}


inline void Vyhladavanie::hodnotyKriterii(TableItem<std::string, UzemnaJednotka*>* item)
{
	//vypis pre bodove vyhladavanie
	cout << strasnePeknyRamik << endl;
	cout << "KRITERIUM UJ NAZOV = ";
	vypisKriteriaNazov(item->accessData());
	cout << endl;
	cout << "KRITERIUM UJ TYP = ";
	vypisKriteriaUJTyp(item->accessData());
	cout << endl;
	cout << "POCET OBYVATELOV = ";
	cout << item->accessData()->getPocetObyvatelov() << endl;
	cout << "TOTO JE MOJA NADRADENA UJ TYP / NAZOV ";
	vypisKriteriaNadradena(item->accessData());
	cout << endl;
	cout << strasnePeknyRamik << endl;
	cout << "KRITERIUM VEKOVA SKUPINA POCET" << endl << endl;
	for (int i = 0; i < 3; i++)
	{
		vypisKriteriaUJVekovaSkupinaPocet(item->accessData(), i);
	}
	cout << strasnePeknyRamik << endl;
	std::cout << "KRITERIUM VZDELANIE POCET" << endl << endl;
	for (int i = 0; i < 8; i++)
	{
		vypisKriteriaUJVzdelaniePocet(item->accessData(), i);
	}
	cout << strasnePeknyRamik << endl;
	std::cout << "KRITERIUM VZDELANIE PODIEL" << endl << endl;
	for (int i = 0; i < 8; i++)
	{
		vypisKriteriaUJVzdelaniePodiel(item->accessData(), i);
	}
}

inline void Vyhladavanie::vypisKriteriaNazov(UzemnaJednotka* uj)
{

	std::cout << kriteriumNazov->evaluate(uj);

}

inline void Vyhladavanie::vypisKriteriaUJTyp(UzemnaJednotka* uj)
{

	kriteriumUJTyp->evaluate(uj);

}

inline void Vyhladavanie::vypisKriteriaUJPrislusnost(UzemnaJednotka* uj)
{
	kriteriumUJPrislusnost->evaluate(uj);

}

inline void Vyhladavanie::vypisKriteriaNadradena(UzemnaJednotka* uj)
{
	kriteriumUJNadradena->evaluate(uj);
}

inline void Vyhladavanie::vypisKriteriaUJVzdelaniePocet(UzemnaJednotka* uj, int indexVzdelania)
{


	//mapovanie indexov
	switch (indexVzdelania) {
	case 0:
		cout << "BEZ UKONCENEHO VZDELANIA = ";
		break;
	case 1:
		cout << "ZAKLADNE VZDELANIE = ";
		break;
	case 2:
		cout << "UCNOVSKE VZDELANIE = ";
		break;
	case 3:
		cout << "STREDNE VZDELANIE = ";
		break;
	case 4:
		cout << "VYSSIE VZDELANIE = ";
		break;
	case 5:
		cout << "VYSOKOSKOLSKE VZDELANIE = ";
		break;
	case 6:
		cout << "BEZ VZDELANIA = ";
		break;
	case 7:
		cout << "NEZISTENE VZDELANIE = ";
		break;
	default:
		break;
	}

	//kriteriumUJVzdelaniePocet->setIndex(indexVzdelania);
	kriteriumUJVZPocet->setVzdelaniePocetIndex(indexVzdelania);
	std::cout << kriteriumUJVZPocet->evaluate(uj) << std::endl;


}
inline void Vyhladavanie::vypisKriteriaUJVzdelaniePodiel(UzemnaJednotka* uj, int indexVzdelania)
{

	//mapovanie indexov
	switch (indexVzdelania) {
	case 0:
		cout << "BEZ UKONCENEHO VZDELANIA = ";
		break;
	case 1:
		cout << "ZAKLADNE VZDELANIE = ";
		break;
	case 2:
		cout << "UCNOVSKE VZDELANIE = ";
		break;
	case 3:
		cout << "STREDNE VZDELANIE = ";
		break;
	case 4:
		cout << "VYSSIE VZDELANIE = ";
		break;
	case 5:
		cout << "VYSOKOSKOLSKE VZDELANIE = ";
		break;
	case 6:
		cout << "BEZ VZDELANIA = ";
		break;
	case 7:
		cout << "NEZISTENE VZDELANIE = ";
		break;
	default:
		break;
	}

	kriteriumUJVZPodiel->setVzdelaniePodielIndex(indexVzdelania);
	std::cout << kriteriumUJVZPodiel->evaluate(uj) << " %" << std::endl;

}

inline void Vyhladavanie::vypisKriteriaUJVekPocet(UzemnaJednotka* uj, int indexVek)
{
	//mapovanie indexov
	if (indexVek == 0) {
		cout << "MUZI = ";
	}
	else {
		cout << "ZENY = ";
	}

	std::cout << kriteriumUJVekPocet->evaluate(uj) << std::endl;
	kriteriumUJVekPocet->setPocet_(0);

}

inline void Vyhladavanie::vypisKriteriaUJVekPodiel(UzemnaJednotka* uj, int indexVek)
{	//mapovanie indexov
	if (indexVek == 0) {
		cout << "MUZI = ";
	}
	else {
		cout << "ZENY = ";
	}

	std::cout << kriteriumUJVekPodiel->evaluate(uj) << " %" << std::endl;
	kriteriumUJVekPodiel->setPodiel_(0);

}

inline void Vyhladavanie::vypisKriteriaUJVekovaSkupinaPocet(UzemnaJednotka* uj, int evsIndex)
{
	//mapovanie indexov
	switch (evsIndex) {
	case 0:
		std::cout << "POCET PREDPRODUKTIVNYCH = ";
		break;
	case 1:
		std::cout << "POCET PRODUKTIVNYCH = ";
		break;
	case 2:
		std::cout << "POCET POPRODUKTIVNYCH = ";
		break;
	default:
		break;
	}
	kriteriumUJVekovaSkupinaPocet->setEVSPocetIndex(evsIndex);
	std::cout << kriteriumUJVekovaSkupinaPocet->evaluate(uj) << std::endl;

}

inline void Vyhladavanie::vypisKriteriaUJVekovaSkupinaPodiel(UzemnaJednotka* uj, int evsIndex)
{
	//mapovanie indexov
	switch (evsIndex) {
	case 0:
		std::cout << "PODIEL PREDPRODUKTIVNYCH = ";
		break;
	case 1:
		std::cout << "PODIEL PRODUKTIVNYCH = ";
		break;
	case 2:
		std::cout << "PODIEL POPRODUKTIVNYCH = ";
		break;
	default:
		break;
	}
	kriteriumUJVekovaSkupinaPodiel->setEVSPodielIndex(evsIndex);
	std::cout << kriteriumUJVekovaSkupinaPodiel->evaluate(uj) << " %" << std::endl;
}

inline void Vyhladavanie::vypisFilter(std::string zvolenaUJ, int mozem, SortedSequenceTable<std::string, UzemnaJednotka*>* zvolenaTabulka, SortedSequenceTable<std::string, UzemnaJednotka*>* prislusnost)
{

	int vek = 0;
	int vekMuzi = 0;
	int vekZeny = 0;
	int	vekPod = 0;
	int vekZenyPod = 0;
	int vekMuziPod = 0;
	int cisloEVSPocet = 0;
	int cisloEVSPodiel = 0;
	bool otoc = true;
	//zaznamenam volby do prislusnosti
	Array<UzemnaJednotka*>* arrayKrajov = new Array<UzemnaJednotka*>(prislusnost->size());
	switch (vybrateKriteriumPreFilter) {
	case 0:
		//Filter pre najdenie Nazvu mnoziny
		system("CLS");
		cout << strasnePeknyRamik << endl;
		cout << "FILTROVANIE NAZVU " << zvolenaUJ << endl;
		cout << strasnePeknyRamik << endl;
		cout << "ZADAJ NAZOV PRE FILTER" << endl;
		cout << cakamKlavesu;
		cin >> vyber;
		//zaznamenam alfu ostatne ma nezaujima
		zaznamenajHraniceFiltrov(0, vyber, nullptr, 0, 0);
		counterPreVypisovanieFiltrov++;

		break;

	case 1:

		while (otoc) {
			//filter prislusnosti len z krajov podla zadania
			system("CLS");
			cout << strasnePeknyRamik << endl;
			cout << "FILTROVANIE PRISLUSNOSTI " << zvolenaUJ << endl;
			cout << strasnePeknyRamik << endl;
			cout << "ZADAJ PRISLUSNOST PRE FILTER" << endl;
			cout << "MOZNOSTI : KRAJ" << endl;
			cout << cakamKlavesu;

			cin >> vyber;
			//vypisem moznosti krajov a klasicky skipnem slovensko
			if (vyber._Equal("KRAJ")) {
				cout << strasnePeknyRamik << endl;
				cout << "TOTO SU KRAJE" << endl;
				for (auto kraj : *prislusnost) {
					if (counterPreSkipnutieSlovenska == 5) {
						counterPreSkipnutieSlovenska++;

					}
					else {
						cout << "*" << cislo << "* ";
						vypisKriteriaNazov(kraj->accessData());
						cout << endl;
						cislo++;
						counterPreSkipnutieSlovenska++;
					}

				}
				iterator = 0;
				counterPreSkipnutieSlovenska = 0;
				for (auto kraj : *prislusnost) {
					if (counterPreSkipnutieSlovenska == 5) {
						counterPreSkipnutieSlovenska++;

					}
					else {
						arrayKrajov->at(iterator) = kraj->accessData();
						iterator++;
						counterPreSkipnutieSlovenska++;

					}


				}
				cout << cakamKlavesu;
				cin >> volba;
				//ak netrafim kraj tak repete
				if (volba > 7) {
					otoc = true;
					cout << "ZLE ZADANY VSTUP ";
				}
				else {
					for (int i = 0; i < arrayKrajov->size(); i++) {
						if (volba == i) {
							vybranyKraj = arrayKrajov->at(volba)->getNazov();
							cout << "VYBRAL SI SI " << vybranyKraj << endl;
							for (auto item : *prislusnost) {
								if (item->accessData()->getNazov() == vybranyKraj) {
									kriteriumUJPrislusnost->setPrislusnostUJ(item->accessData());
									//item mi vrati prislusnost a zaznamena
									zaznamenajHraniceFiltrov(1, vyber, item->accessData(), 0, 0);
								}
							}


							counterPreVypisovanieFiltrov++;
							otoc = false;
						}

					}

				}
			}
			else {
				otoc = true;
				cout << "ZLE ZADANY VSTUP ";
			}
		}

		break;

	case 2:
		//vzdelanie je na indexe arrayu 0 - 7
		while (otoc) {
			system("CLS");
			cout << strasnePeknyRamik << endl;
			cout << "FILTROVANIE VZDELANIA PODLA POCTU" << endl;
			cout << strasnePeknyRamik << endl;
			cout << "ZADAJ VZDELANIE" << endl;
			cout << strasnePeknyRamik << endl;
			cout << "*0*\tBEZ UKONC VZDELANIA\n*1*\tZAKLADNE VZDELANIE\n*2*\tUCNOVSKE VZDELANIE\n*3*\tSTREDNE VZDELANIE\n*4*\tVYSSIE VZDELANIE\n*5*\tVYSOKOSKOLSKE VZDELANIE\n*6*\tBEZ VZDELANIA\n*7*\tNEZISTENE VZDELANIE" << endl;
			cout << strasnePeknyRamik << endl;
			cout << cakamKlavesu;
			cin >> cislo;
			if (cislo > 7) {
				cout << "ZLE ZADANY VSTUP ";
				otoc = true;
			}
			else {
				indexVzdelaniaPocet = cislo;
				cout << "ZADAJ SPODNU HRANICU" << endl;
				cout << cakamKlavesu;
				cin >> alpha;
				cout << endl << "ZADAJ VRCHNU HRANICU" << endl;
				cout << cakamKlavesu;
				cin >> beta;
				kriteriumUJVZPocet->setVzdelaniePocetIndex(cislo);
				//nacitam mapovanie a alfu betu
				zaznamenajHraniceFiltrov(2, "", nullptr, alpha, beta);
				counterPreVypisovanieFiltrov++;

				otoc = false;
			}
		}
		break;

	case 3:
		while (otoc) {
			//zas indexy 0-7
			system("CLS");
			cout << strasnePeknyRamik << endl;
			cout << "FILTROVANIE VZDELANIA PODLA PODIELU" << endl;
			cout << strasnePeknyRamik << endl;
			cout << "ZADAJ VZDELANIE" << endl;
			cout << strasnePeknyRamik << endl;
			cout << "*0*\tBEZ UKONC VZDELANIA\n*1*\tZAKLADNE VZDELANIE\n*2*\tUCNOVSKE VZDELANIE\n*3*\tSTREDNE VZDELANIE\n*4*\tVYSSIE VZDELANIE\n*5*\tVYSOKOSKOLSKE VZDELANIE\n*6*\tBEZ VZDELANIA\n*7*\tNEZISTENE VZDELANIE" << endl;
			cout << strasnePeknyRamik << endl;
			cout << cakamKlavesu;
			cin >> cislo;
			if (cislo > 7) {
				cout << "ZLE ZADANY VSTUP ";
				otoc = true;
			}
			else {
				indexVzdelaniaPodiel = cislo;
				cout << "ZADAJ SPODNU HRANICU %" << endl;
				cout << cakamKlavesu;
				cin >> alpha;
				cout << endl << "ZADAJ VRCHNU HRANICU %" << endl;
				cout << cakamKlavesu;
				cin >> beta;
				//mapovanie alfa beta
				kriteriumUJVZPodiel->setVzdelaniePodielIndex(cislo);
				zaznamenajHraniceFiltrov(3, "", nullptr, alpha, beta);
				counterPreVypisovanieFiltrov++;
				otoc = false;
			}
		}
		break;
	case 4:
		vek = 0;
		vekZeny = 0;
		vekMuzi = 0;
		system("CLS");
		while (otoc) {
			//vek pocet
			cout << strasnePeknyRamik << endl;
			cout << "FILTROVANIE VEKU PODLA POCTU" << endl;
			cout << strasnePeknyRamik << endl;
			cout << "*0* MUZI " << endl;
			cout << "*1* ZENY " << endl;
			cout << cakamKlavesu;
			cin >> vek;
			//ak zadal muz tak 0 ak zeny tak 1
			if (vek == 0) {
				vekMuzi = vek;
			}

			if (vek == 1) {
				vekZeny = vek + 100;

			}
			if (vek < 2) { //nastavenie dalsich hodnot
				cout << "ZADAJ VEK" << endl;
				cout << strasnePeknyRamik << endl;
				cout << "ZADAJ OD ROKOV" << endl;
				cout << cakamKlavesu;
				if (vek == 0) {
					cin >> vekMuzi;
					//interval spodk
					kriteriumUJVekPocet->setVekPocetOdkial(vekMuzi);
				} if (vek == 1) {
					cin >> vekZeny;

					kriteriumUJVekPocet->setVekPocetOdkial(vekZeny);
				}
				cout << "ZADAJ DO ROKOV" << endl;
				cout << cakamKlavesu;
				if (vek == 0) {
					cin >> vekMuzi;
					//interval vrch
					kriteriumUJVekPocet->setVekPocetPokial(vekMuzi);
				} if (vek == 1) {
					cin >> vekZeny;

					kriteriumUJVekPocet->setVekPocetPokial(vekZeny);
				}
				//alpha / beta pre filter
				cout << "ZADAJ SPODNU HRANICU" << endl;
				cout << cakamKlavesu;
				cin >> alpha;
				cout << endl << "ZADAJ VRCHNU HRANICU" << endl;
				cout << cakamKlavesu;
				cin >> beta;
				//mapovanie a alfa /beta
				zaznamenajHraniceFiltrov(4, "", nullptr, alpha, beta);
				counterPreVypisovanieFiltrov++;

				otoc = false;
			}
			else {
				cout << "ZLE ZADANY VSTUP ";
				system("CLS");
				otoc = true;
			}
		}
		break;
	case 5:
		vekPod = 0;
		vekZenyPod = 0;
		vekMuziPod = 0;
		system("CLS");
		while (otoc) {
			//podiel tak isto ako pocet
			cout << strasnePeknyRamik << endl;
			cout << "FILTROVANIE VEKU PODLA PODIELU" << endl;
			cout << strasnePeknyRamik << endl;
			cout << "*0* MUZI " << endl;
			cout << "*1* ZENY " << endl;
			cout << cakamKlavesu;
			cin >> vekPod;
			if (vekPod == 0) {
				vekMuziPod = vekPod;
			}

			if (vekPod == 1) {
				vekZenyPod = vekPod + 100;

			}
			if (vekPod < 2) {
				cout << "ZADAJ VEK" << endl;
				cout << strasnePeknyRamik << endl;
				cout << "ZADAJ OD ROKOV" << endl;
				cout << cakamKlavesu;
				if (vekPod == 0) {
					cin >> vekMuziPod;
					kriteriumUJVekPodiel->setVekPodielOdkial(vekMuziPod);
				} if (vekPod == 1) {
					cin >> vekZenyPod;
					kriteriumUJVekPodiel->setVekPodielOdkial(vekZenyPod);
				}
				cout << "ZADAJ DO ROKOV" << endl;
				cout << cakamKlavesu;
				if (vekPod == 0) {
					cin >> vekMuziPod;
					kriteriumUJVekPodiel->setVekPodielPokial(vekMuziPod);
				} if (vekPod == 1) {
					cin >> vekZenyPod;

					kriteriumUJVekPodiel->setVekPodielPokial(vekZenyPod);
				}
				cout << "ZADAJ SPODNU HRANICU %" << endl;
				cout << cakamKlavesu;
				cin >> alpha;
				cout << endl << "ZADAJ VRCHNU HRANICU %" << endl;
				cout << cakamKlavesu;
				cin >> beta;
				kriteriumUJVekPodiel->setPodiel_(0);
				zaznamenajHraniceFiltrov(5, "", nullptr, alpha, beta);
				counterPreVypisovanieFiltrov++;

				otoc = false;
			}
			else {
				cout << "ZLE ZADANY VSTUP ";
				system("CLS");
				otoc = true;
			}
		}
		break;
	case 6:
		while (otoc) {
			system("CLS");
			cout << strasnePeknyRamik << endl;
			cout << "FILTROVANIE EVS PODLA POCTU" << endl;
			cout << strasnePeknyRamik << endl;
			cout << "*0*\tPREDPRODUKTIVNI\n*1*\tPRODUKTIVNI\n*2*\tPOPRODUKTIVNI" << endl;
			cout << strasnePeknyRamik << endl;
			cout << cakamKlavesu;
			cin >> cislo;
			if (cislo > 2) {
				cout << "ZLE ZADANY V STUP ";
				otoc = true;

			}
			else {
				cisloEVSPocet = cislo;
				//alpha beta mapovanie 
				cout << "ZADAJ SPODNU HRANICU" << endl;
				cout << cakamKlavesu;
				cin >> alpha;
				cout << endl << "ZADAJ VRCHNU HRANICU" << endl;
				cout << cakamKlavesu;
				cin >> beta;
				kriteriumUJVekovaSkupinaPocet->setEVSPocetIndex(cislo);
				zaznamenajHraniceFiltrov(6, "", nullptr, alpha, beta);
				counterPreVypisovanieFiltrov++;
				otoc = false;
			}
		}
		break;
	case 7:
		while (otoc) {
			//alpha beta mapovanie 
			system("CLS");
			cout << strasnePeknyRamik << endl;
			cout << "FILTROVANIE EVS PODLA PODIELU" << endl;
			cout << strasnePeknyRamik << endl;
			cout << "*0*\tPREDPRODUKTIVNI\n*1*\tPRODUKTIVNI\n*2*\tPOPRODUKTIVNI" << endl;
			cout << strasnePeknyRamik << endl;
			cout << cakamKlavesu;
			cin >> cislo;
			if (cislo > 2) {
				cout << "ZLE ZADANY V STUP ";
				otoc = true;
			}
			else {
				cisloEVSPodiel = cislo;
				cout << "ZADAJ SPODNU HRANICU %" << endl;
				cout << cakamKlavesu;
				cin >> alpha;
				cout << endl << "ZADAJ VRCHNU HRANICU %" << endl;
				cout << cakamKlavesu;
				cin >> beta;
				kriteriumUJVekovaSkupinaPodiel->setEVSPodielIndex(cislo);
				zaznamenajHraniceFiltrov(7, "", nullptr, alpha, beta);
				counterPreVypisovanieFiltrov++;
				otoc = false;
			}
		}
		break;
	default:

		break;
	}
	//mozem znamena ci zaznamenal vsetky filtre ktore mu boli poslate counter ich pekne napocital
	if (counterPreVypisovanieFiltrov == mozem) {
		cout << strasnePeknyRamik << endl;
		bool passed;
		//nad poslanou mnozinou cize tabulka sa pytam cez list 
		//filtrov ci splna -> passed potom pridam do unsorted vystupnej ak nie tak false 

		for (auto uj : *zvolenaTabulka) {
			passed = true;
			UzemnaJednotka* vyslednaUJ = uj->accessData();
			for (int i = 0; i < listFiltrov->size(); i++)
			{

				if (!listFiltrov->at(i)->splnaFilter(uj->accessData())) {
					passed = false;
					break;
				}
			}
			if (passed) {
				vystupnaTabulka->insert(vyslednaUJ->getNazov(), vyslednaUJ);
			
			}

			//ak prejde prvym foreachom a splni tak povypisuje 
		}
		for (auto uj : *vystupnaTabulka) {
			//vsetky potrebne na zaciatok
			cout << "#" << endl;
			cout << "NAZOV UJ ";
			vypisKriteriaNazov(uj->accessData());
			cout << endl << "TYP UJ ";
			vypisKriteriaUJTyp(uj->accessData());
			if (uj->accessData()->getTyp() == Typ::OBEC) {
				cout << " PATRIM DO ";
				vypisKriteriaNazov(uj->accessData()->getMojeZaclenenie());
				cout << " PATRIM DO ";
				vypisKriteriaNazov(uj->accessData()->getMojeZaclenenie()->getMojeZaclenenie());
				cout << " PATRIM DO ";
				vypisKriteriaNazov(uj->accessData()->getMojeZaclenenie()->getMojeZaclenenie()->getMojeZaclenenie());
			} if (uj->accessData()->getTyp() == Typ::OKRES) {
				cout << " PATRIM DO ";
				vypisKriteriaNazov(uj->accessData()->getMojeZaclenenie());
				cout << " PATRIM DO ";
				vypisKriteriaNazov(uj->accessData()->getMojeZaclenenie()->getMojeZaclenenie());
			} if (uj->accessData()->getTyp() == Typ::KRAJ) {
				cout << " PATRIM DO ";
				vypisKriteriaNazov(uj->accessData()->getMojeZaclenenie());
			}
			cout << endl;

			//a tu uz tie ktore splnilo filter
			for (int i = 0; i < listFiltrov->size(); i++)
			{
				if (listFiltrov->at(i) == filterUJPrislusnost) {
					vypisKriteriaUJPrislusnost(uj->accessData());
				}
				else if (listFiltrov->at(i) == filterVzdelaniePocet) {
					cout << "VZDELANIE POCET ";
					vypisKriteriaUJVzdelaniePocet(uj->accessData(), indexVzdelaniaPocet);
				}
				else if (listFiltrov->at(i) == filterVzdelaniePodiel) {
					cout << "VZDELANIE PODIEL ";
					vypisKriteriaUJVzdelaniePodiel(uj->accessData(), indexVzdelaniaPodiel);
				}
				else if (listFiltrov->at(i) == filterVekPocet) {
					cout << "VEK POCET ";
					if (vekMuzi != 0) {

						vypisKriteriaUJVekPocet(uj->accessData(), 0);
					} if (vekZeny != 0) {

						vypisKriteriaUJVekPocet(uj->accessData(), 1);
					}

				}
				else if (listFiltrov->at(i) == filterVekPodiel) {
					cout << "VEK PODIEL ";
					if (vekMuziPod != 0) {

						vypisKriteriaUJVekPodiel(uj->accessData(), 0);
					} if (vekZenyPod != 0) {

						vypisKriteriaUJVekPodiel(uj->accessData(), 1);
					}
				}
				else if (listFiltrov->at(i) == filterVekovaSkupinaPocet) {
					cout << "EVS POCET ";
					vypisKriteriaUJVekovaSkupinaPocet(uj->accessData(), cisloEVSPocet);
				}
				else if (listFiltrov->at(i) == filterVekovaSkupinaPodiel) {
					cout << "EVS PODIEL ";
					vypisKriteriaUJVekovaSkupinaPodiel(uj->accessData(), cisloEVSPodiel);
				}

			}

		}

	}
	delete arrayKrajov;
}

inline void Vyhladavanie::zaznamenajHraniceFiltrov(int volba, std::string nazov, UzemnaJednotka* uj, int spodnaHranica, int hornaHranica)
{
	//podla zadanych parametrov ponastavujem intervaly a hodnoty
	switch (volba) {
	case 0:
		filterNazov->setAlpha(nazov);
		break;
	case 1:
		filterUJPrislusnost->setAlpha(uj);
		break;
	case 2:
		filterVzdelaniePocet->setAlpha(spodnaHranica);
		filterVzdelaniePocet->setBeta(hornaHranica);
		break;
	case 3:
		filterVzdelaniePodiel->setAlpha(spodnaHranica);
		filterVzdelaniePodiel->setBeta(hornaHranica);
		break;
	case 4:
		filterVekPocet->setAlpha(spodnaHranica);
		filterVekPocet->setBeta(hornaHranica);
		break;
	case 5:
		filterVekPodiel->setAlpha(spodnaHranica);
		filterVekPodiel->setBeta(hornaHranica);
		break;
	case 6:
		filterVekovaSkupinaPocet->setAlpha(spodnaHranica);
		filterVekovaSkupinaPocet->setBeta(hornaHranica);
		break;
	case 7:
		filterVekovaSkupinaPodiel->setAlpha(spodnaHranica);
		filterVekovaSkupinaPodiel->setBeta(hornaHranica);
		break;
	default:
		break;
	}
}

inline void Vyhladavanie::pridajDoListuFiltrov(int volbaPodla)
{
	// podla zadanej volby filtra pridam do listu filtrov
	switch (volbaPodla) {
	case 0:
		listFiltrov->add(filterNazov);
		break;
	case 1:
		listFiltrov->add(filterUJPrislusnost);
		break;
	case 2:
		listFiltrov->add(filterVzdelaniePocet);
		break;
	case 3:
		listFiltrov->add(filterVzdelaniePodiel);
		break;
	case 4:
		listFiltrov->add(filterVekPocet);
		break;
	case 5:
		listFiltrov->add(filterVekPodiel);
		break;
	case 6:
		listFiltrov->add(filterVekovaSkupinaPocet);
		break;
	case 7:
		listFiltrov->add(filterVekovaSkupinaPodiel);
		break;
	default:
		break;
	}
}

inline void Vyhladavanie::sortOtazky()
{
	if (vystupnaTabulka->size() <= 0) {

	}
	else {
		cout << strasnePeknyRamik << endl;
		cout << "CHCES TRIEDIT ?" << endl;
		cout << "*0* ANO\n*1* NIE" << endl;
		cout << cakamKlavesu;
		cin >> volba;
		cout << strasnePeknyRamik << endl;
		if (volba == 0) {
			cout << "PODLA COHO ?" << endl;
			cout << "*0* NAZOV\n*1* VZDELANIE POCET\n*2* VZDELANIE PODIEL" << endl;
			cout << cakamKlavesu;
			cin >> volba;
			cout << strasnePeknyRamik << endl;
			// ak vzostupne tak true ak zostupne tak false
			cout << "*0* VZOSTUPNE\n*1* ZOSTUPNE\n";
			cout << cakamKlavesu;
			cin >> sortVolba;
			cout << strasnePeknyRamik << endl;
			if (sortVolba == 0) {
				if (pocetFiltrov == 0) {
					sortujNeutriedenuTabulku(vystupnaTabulka, volba, true, true);
				}
				else {
					sortujNeutriedenuTabulku(vystupnaTabulka, volba, true, false);
				}
				
			}
			else {
				if (pocetFiltrov == 0) {
					sortujNeutriedenuTabulku(vystupnaTabulka, volba, false, true);
				}
				else {
					sortujNeutriedenuTabulku(vystupnaTabulka, volba, false, false);
				}
			}
		}
	}

}

inline void Vyhladavanie::sortujNeutriedenuTabulku(UnsortedSequenceTable<std::string, UzemnaJednotka*>* neutriedena, int podlaCoho, bool vzostupne, bool prazdna)
{

	QuickSort<string, UzemnaJednotka*>* quickSort = new QuickSort<string, UzemnaJednotka*>;
	int pocet = 0;
	double podiel = 0;
	switch (podlaCoho) {

		//podla nazvu
	case 0:
		if (vzostupne) {
			cout << "UTRIEDENE PODLA NAZVU VZOSTUPNE" << endl;
		}
		else {
			cout << "UTRIEDENE PODLA NAZVU ZOSTUPNE" << endl;
		}

		quickSort->quickSortMagic(*neutriedena, *kriteriumNazov, vzostupne);
		for (auto uj : *neutriedena) {
			vypisKriteriaNazov(uj->accessData());

			cout << endl;
		}
		break;
	case 1:
		//VZ POCET
		if (vzostupne) {
			cout << "UTRIEDENE PODLA VZDELANIA POCET VZOSTUPNE" << endl;
		}
		else {
			cout << "UTRIEDENE PODLA VZDELANIA POCET ZOSTUPNE" << endl;
		}
		
		quickSort->quickSortMagic(*neutriedena, *kriteriumUJVZPocet, vzostupne);
		for (auto uj : *neutriedena) {
			pocet = 0;
			if (prazdna) {
				for (int i = 0; i < 8; i++) {
					pocet += uj->accessData()->getVzdelanieAtIndex(i);
				}
				vypisKriteriaNazov(uj->accessData());
				cout << endl;
				cout << "POCET VSETKYCH VZDELANOSTI = " << pocet << endl;
				cout << endl;
			}
			else {
				vypisKriteriaNazov(uj->accessData());
				cout << endl;
				vypisKriteriaUJVzdelaniePocet(uj->accessData(), indexVzdelaniaPocet);
				cout << endl;
				
			}
			

		}
		break;
	case 2:
		//VZ PODIEL
		if (vzostupne) {
			cout << "UTRIEDENE PODLA VZDELANIA PODIEL VZOSTUPNE" << endl;
		}
		else {
			cout << "UTRIEDENE PODLA VZDELANIA PODIEL ZOSTUPNE" << endl;
		}

		quickSort->quickSortMagic(*neutriedena, *kriteriumUJVZPodiel, vzostupne);
		for (auto uj : *neutriedena) {
			podiel = 0;
			if (prazdna) {
				for (int i = 0; i < 8; i++) {
					podiel += uj->accessData()->getVzdelanieAtIndex(i);
				}
				vypisKriteriaNazov(uj->accessData());
				cout << endl;
				cout << "PODIEL VSETKYCH VZDELANOSTI = " << (podiel / uj->accessData()->getPocetObyvatelov()) * 100 << " %" << endl;
				cout << endl;
			}
			else {
				vypisKriteriaNazov(uj->accessData());
				cout << endl;
				vypisKriteriaUJVzdelaniePodiel(uj->accessData(), indexVzdelaniaPodiel);
				cout << endl;
				
			}
			
		}
		break;
	
	default:
		break;
	}
	delete quickSort;

}










