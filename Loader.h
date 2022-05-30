#pragma once
#include <string>
#include "structures\list\linked_list.h"
#include <iostream>
#include <ios>
#include <fstream>
#include <sstream>
#include "structures/table/table.h"
#include "structures/table/sequence_table.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"

#include "UzemnaJednotka.h"

using namespace std;
using namespace structures;
class Loader {

public:

	void loadData(SortedSequenceTable<std::string, UzemnaJednotka*>* obce, SortedSequenceTable<std::string, UzemnaJednotka*>* okresy,
		SortedSequenceTable<std::string, UzemnaJednotka*>* kraje);
	SortedSequenceTable<std::string, Array<int>*>*  nacitajVek();
	SortedSequenceTable<std::string, Array<int>*>* nacitajVzdelanie();

};



inline void Loader::loadData( SortedSequenceTable<std::string, UzemnaJednotka*>* obce,
	SortedSequenceTable<std::string, UzemnaJednotka*>* okresy,
	SortedSequenceTable<std::string, UzemnaJednotka*>* kraje)
{
	string code;
	string offTitle;
	string medTitle;
	string shortTitle;
	string note;

	ifstream fileKraje("data\\kraje.csv");
	ifstream fileObce("data\\obce.csv");
	ifstream fileOkresy("data\\okresy.csv");


	
	UzemnaJednotka* slovensko = new UzemnaJednotka(100000,"Slovensko",Typ::STAT);
	slovensko->setMojeZaclenenie(slovensko);
	slovensko->setKod("100000");
	kraje->insert("Slovensko", slovensko);
	
	
	
	

	
	if (!fileKraje.is_open() || !fileObce.is_open() || !fileOkresy.is_open()) { std::cout << "ERROR" << endl; }

	//sortNumber;code;officialTitle;mediumTitle;shortTitle;note
	
	string line;
	getline(fileKraje, line);
	while ((fileKraje.peek() != EOF)) {

		getline(fileKraje, line, ';');
		getline(fileKraje, code, ';');

		getline(fileKraje, offTitle, ';');

		getline(fileKraje, line, ';');
		getline(fileKraje, line, ';');

		getline(fileKraje, note, '\n');
		//ak sa v kraji este nenachadza dana jednotka s klucom tak sa prida
		if (!kraje->containsKey(offTitle)) {

			UzemnaJednotka* tempUj = new UzemnaJednotka(stoi(code), offTitle, Typ::KRAJ);
			tempUj->setKod(code);
	
			tempUj->setMojeZaclenenie(slovensko);

			kraje->insert(offTitle, tempUj);
			
			
			
		}
		
	}
	
	fileKraje.close();
	

	getline(fileOkresy, line);
	while ((fileOkresy.peek() != EOF)) {
		getline(fileOkresy, line, ';');
		getline(fileOkresy, code, ';');
		string s = code.substr(3, 2);	//substring kodu kvoli zacleneniu okresu do kraja
		string sObce = code.substr(3, 3); // substring kodu aby som si vedel namapovat obec
		getline(fileOkresy, offTitle, ';');

		getline(fileOkresy, line, ';');
		getline(fileOkresy, line, ';');

		getline(fileOkresy, note, '\n');
		//ak sa nenachadza tak pridam
		if (!okresy->containsKey(offTitle)) {
			UzemnaJednotka* tempUj = new UzemnaJednotka(stoi(sObce), offTitle, Typ::OKRES);
			tempUj->setKod(code);
			//zaclenujem predka
			if (stoi(s) == 10) {

				tempUj->setMojeZaclenenie(kraje->find("Bratislavsky kraj"));
			}
			else if (stoi(s) == 21) {
				tempUj->setMojeZaclenenie(kraje->find("Trnavsky kraj"));
			}
			else if (stoi(s) == 22) {
				tempUj->setMojeZaclenenie(kraje->find("Trenciansky kraj"));
			}
			else if (stoi(s) == 23) {
				tempUj->setMojeZaclenenie(kraje->find("Nitriansky kraj"));
			}
			else if (stoi(s) == 31) {
				tempUj->setMojeZaclenenie(kraje->find("Zilinsky kraj"));
			}
			else if (stoi(s) == 32) {
				tempUj->setMojeZaclenenie(kraje->find("Banskobystricky kraj"));
			}
			else if (stoi(s) == 41) {
				tempUj->setMojeZaclenenie(kraje->find("Presovsky kraj"));
			}
			else if (stoi(s) == 42) {
				tempUj->setMojeZaclenenie(kraje->find("Kosicky kraj"));
			}
				


			okresy->insert(offTitle, tempUj);
			
			


		}

	}
	fileOkresy.close();

	int i = 0;
	int count = 0; //sortNumber;code;officialTitle;mediumTitle;shortTitle;note
	getline(fileObce, line);
	while ((fileObce.peek() != EOF)) {
		getline(fileObce, line, ';');
		if (code == "") {
			break;
		}
		getline(fileObce, code, ';');
		string s = code.substr(3, 3);
		string sSub = code.substr(0, 6); // 6 miestny kod obce
		
		getline(fileObce, offTitle, ';');

		getline(fileObce, line, ';');
		getline(fileObce, line, ';');

		getline(fileObce, note, '\n');

		if (obce->containsKey(offTitle) ) {
			
			++i;
			
			offTitle += " " + code;
			
		}
		if (!obce->containsKey(offTitle)) {
			//tu mi staci 3jmiestny pre obec
			UzemnaJednotka* tempUj = new UzemnaJednotka(stoi(s), offTitle, Typ::OBEC);
			for(TableItem<std::string, UzemnaJednotka*>* item : *okresy) {
				string x = item->accessData()->getKod();
				//ak sa rovna substringovany kod obce okresovemu tak priradi
				string xsub = x.substr(0, 6);
				if (xsub == sSub)  {
					count++;
					//priradi obci svoj okres
					tempUj->setMojeZaclenenie(okresy->find(item->getKey()));
					tempUj->setKod(code);
					obce->insert(offTitle, tempUj);
				}
				
			}
		}
		
	}
	fileObce.close();
	
}

inline SortedSequenceTable<std::string, Array<int>*>* Loader::nacitajVek()
{
	SortedSequenceTable<std::string, Array<int>*>* tabulkaVeku = new SortedSequenceTable<std::string, Array<int>*>();
	//Kod;Uzemna jednotka;muz (0);muz (1
	ifstream fileVek("data\\vek.csv");
	string line;
	string prazdny;
	string code;
	string offTitle;
	string vek;
	string key;
	int cislo;
	
	int counter = 0;
	//zobere prvy riadok
	getline(fileVek, prazdny);
	
	//iny pristup k filu
	while (fileVek) {
		getline(fileVek, line);
		int pocetSlov = 0;
		key = "";
		string word = "";
		//vytvori celu array pre vek 0 100 muzi 101 202 zeny
		Array<int>* arrayVeku = new Array<int>(202);
		for (int i = 0; i < line.length(); i++)
		{
			//ak sa nerovna delimiteru tak nacita do stringu cely riadok
			if (line.at(i) != ';') {
				word += line.at(i);

			}
			else {
				//nacita slovo
				if(pocetSlov == 0){
					key = word;
				} else if (pocetSlov != 1) {
					//nacita napokon cislo
					cislo = stoi(word);
					// - 2 lebo najprv zobere kod potom nazov obce az napokon cisla
					arrayVeku->at(pocetSlov - 2) = cislo;
				}
				//vyprazdnim pre dalsi cyklus a iterujem
				word = "";
				pocetSlov++;
			}
		}
		if (word.length() != 0) {
			// zoberem int hodnotu zo slova
			cislo = stoi(word);
			arrayVeku->at(pocetSlov - 2) = cislo;
			// pridam
			tabulkaVeku->insert(key, arrayVeku);
		}
		else {
			
			delete arrayVeku;
		}
		
		

		
	}
	 
	
	return tabulkaVeku;
	

}

inline SortedSequenceTable<std::string, Array<int>*>* Loader::nacitajVzdelanie()
{
	SortedSequenceTable<std::string, Array<int>*>* tabulkaVzdelania = new SortedSequenceTable<std::string, Array<int>*>();
	
	ifstream fileVek("data\\vzdelanie.csv");
	string line;
	string prazdny;
	string code;
	string offTitle;
	string vek;
	string key;
	int cislo;

	int counter = 0;
	getline(fileVek, prazdny);

	//to iste pre vzdelanie ako pre vek
	while (fileVek) {
		getline(fileVek, line);
		int pocetSlov = 0;
		key = "";
		string word = "";
		Array<int>* arrayVzdelania = new Array<int>(8);
		for (int i = 0; i < line.length(); i++)
		{
			if (line.at(i) != ';') {
				word += line.at(i);

			}
			else {
				if (pocetSlov == 0) {
					key = word;
				}
				else if (pocetSlov != 1) {

					cislo = stoi(word);
					arrayVzdelania->at(pocetSlov - 2) = cislo;
				}
				word = "";
				pocetSlov++;
			}
		}
		if (word.length() != 0) {
			cislo = stoi(word);
			arrayVzdelania->at(pocetSlov - 2) = cislo;
			tabulkaVzdelania->insert(key, arrayVzdelania);
		}
		else {
			delete arrayVzdelania;
		}
	}

	return tabulkaVzdelania;
}


