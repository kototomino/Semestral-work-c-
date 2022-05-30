#include "Loader.h"
#include "structures/heap_monitor.h"
#include "Vyhladavanie.h"
int main() {
	initHeapMonitor();
	
	Loader loader;
	
	SortedSequenceTable<std::string, UzemnaJednotka*>* obce = new SortedSequenceTable<std::string, UzemnaJednotka*>;
	SortedSequenceTable<std::string, UzemnaJednotka*>* kraje = new SortedSequenceTable<std::string, UzemnaJednotka*>;
	SortedSequenceTable<std::string, UzemnaJednotka*>* okresy = new SortedSequenceTable<std::string, UzemnaJednotka*>;
	cout << "NACITAVAM UDAJE ... (10sMAX) " << endl;
		loader.loadData(obce, okresy, kraje);
		SortedSequenceTable<std::string, Array<int>*>* tabulkaVeku = loader.nacitajVek();
		SortedSequenceTable<std::string, Array<int>*>* tabulkaVzdelania = loader.nacitajVzdelanie();
		
		system("CLS");
		cout << "NAHADZUJEM VYPOCTOVE UDAJE A PRIRADUJEM ... (30sMAX) " << endl;


		for (auto var : *obce) {
			var->accessData()->setVek(tabulkaVeku);
			var->accessData()->setVzdelanie(tabulkaVzdelania);
			var->accessData()->setEvsPreObec();
			var->accessData()->zvysPocetObyvatelov(var->accessData()->getEvs());
			var->accessData()->getMojeZaclenenie()->zvysEVS(var->accessData()->getEvs());
			var->accessData()->getMojeZaclenenie()->zvysPocetObyvatelov(var->accessData()->getEvs());
			var->accessData()->getMojeZaclenenie()->zvysVek(var->accessData()->getVek());
			var->accessData()->getMojeZaclenenie()->zvysVzdelanie(var->accessData()->getVzdelanie());
			var->accessData()->getMojeZaclenenie()->getMojeZaclenenie()->zvysEVS(var->accessData()->getEvs());
			var->accessData()->getMojeZaclenenie()->getMojeZaclenenie()->zvysPocetObyvatelov(var->accessData()->getEvs());
			var->accessData()->getMojeZaclenenie()->getMojeZaclenenie()->zvysVek(var->accessData()->getVek());
			var->accessData()->getMojeZaclenenie()->getMojeZaclenenie()->zvysVzdelanie(var->accessData()->getVzdelanie());
			var->accessData()->getMojeZaclenenie()->getMojeZaclenenie()->getMojeZaclenenie()->zvysEVS(var->accessData()->getEvs());
			var->accessData()->getMojeZaclenenie()->getMojeZaclenenie()->getMojeZaclenenie()->zvysPocetObyvatelov(var->accessData()->getEvs());
			var->accessData()->getMojeZaclenenie()->getMojeZaclenenie()->getMojeZaclenenie()->zvysVek(var->accessData()->getVek());
			var->accessData()->getMojeZaclenenie()->getMojeZaclenenie()->getMojeZaclenenie()->zvysVzdelanie(var->accessData()->getVzdelanie());
		}
		
	
		system("CLS");
		//spustac
		Vyhladavanie* vyhladavanie = new Vyhladavanie(obce, okresy, kraje);
		
		//destruktory
		for (auto var : *tabulkaVeku) {

			delete var->accessData();

		}
		for (auto var : *tabulkaVzdelania) {
			delete var->accessData();
		}
		
		for (auto var : *obce) {
			
			delete var->accessData();
			
		}
		for (auto var : *okresy) {
		
			delete var->accessData();
			
		}
		
		for (auto var : *kraje) {
			delete var->accessData();
		}
		
		delete tabulkaVeku;
		delete tabulkaVzdelania;	
		delete vyhladavanie;
		delete okresy;
		delete kraje;
		delete obce;

}