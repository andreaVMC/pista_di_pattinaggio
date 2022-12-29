#include <iostream>	/*includo librerie e classi che utilizzero per il programma*/
#include <time.h>
#include <Windows.h>
#include "pistaDiPattinaggio.cpp"
#include "pattini.cpp"
#include "GUI.h"
using namespace std;
int main(){
	srand(time(NULL));
	/*chiamo i costruttori delle varie classi*/
	pistaDiPattinaggio pista = pistaDiPattinaggio();
	pattini pat = pattini();
	gruppi grup = gruppi();
	int possible; //varibile per scegliere l' evento
	int ora=0; //espressa in minuti, serve a tener conto dell' orario
	ShellExecute(NULL, "open", "index.html",NULL, NULL, SW_SHOWNORMAL); //apre l' interfaccia che serve alla visualizzazione dei dati
	while(true){ /*ciclo infinito*/
		inizializzaPagina(); //crea la pagina
		cout<<"ora attuale: "<<ora<<endl; //stampo sul terminale
		possible=rand()%5+1; //faccio in modo che il selettore di evento sia randomico
			if(possible==1 || possible==3){ //2 possibilita su 5 fanno in modo che venga creato un nuovo gruppo
				int v[rand()%10+1]; //creo un array di dimensione casuale, da 1 a NMAXPERSONE
				grup.creagruppo(v,(sizeof(v)/sizeof(int)));	//creo il gruppo che pattinera in modo casuale sia numero di persone che numeri di scarpe
				grup.stampaGruppo(v,(sizeof(v)/sizeof(int))); //stampo sul terminale il gruppo appena creato
				if(pista.controlloPosti(sizeof(v)/sizeof(int))){ //controllo se all' intrno della pista ce posto
					if(pat.controlloPattini(v,(sizeof(v)/sizeof(int)),ora)){ //controllo se i pattini sono disponibili
						pista.assegnaPosti((sizeof(v)/sizeof(int))); //assegno i posti al gruppo
						grup.mettiInTurno(v,(sizeof(v)/sizeof(int)),ora); //metto il gruppo in turno
						pat.prenotaPattini(v,(sizeof(v)/sizeof(int)),grup.getIdGruppo(grup.getTOTGruppiTurno()-1)); //assegno i pattini al gruppo
						cout<<"il gruppo puo entrare"<<endl; //stampo su terminale se il gruppo puo entrare
						inserisciEvento("nuovo gruppo entrato"); //inserisco l' evento sull' interfaccia
					}else if(grup.controllaCoda()){
						grup.mettiInAttesa(v,(sizeof(v)/sizeof(int))); //nel caso un gruppo non possa entrare viene messo in attesa
						cout<<"pattini non sufficenti, gruppo in attesa"<<endl; //scrivo che il gruppo e' stato messo in attesa
						inserisciEvento("pattini non sufficenti, gruppo in attesa"); //scrivo il motivo del perche il gruppo e' stato messo in attesa
					}
				}else if(grup.controllaCoda()){
					grup.mettiInAttesa(v,(sizeof(v)/sizeof(int))); //nel caso un gruppo non possa entrare viene messo in attesa
					cout<<"non ce spazio, gruppo in attesa"<<endl; //scrivo che il gruppo e' stato messo in attesa
					inserisciEvento("posti non sufficenti, gruppo in attesa"); //inserisco l' evento sull' interfaccia
				}
			}
			if(possible==2 && grup.getTOTGruppiTurno()!=0){ //se il selettore e' uguale a 2 ed almeno un gruppo e' gia' entrato in pista allora viene fatto uscire un gruppo casuale
				int n;
				n=rand()%grup.getTOTGruppiTurno()+0; //assegno ad n un valoe casuale per scegliere il gruppo che uscira dalla pista
				pat.restituisciPattini(grup.getIdGruppo(n)); //restituisco i pattini del gruppo che esce
				cout<<"valore inutile: "<<grup.getDimGruppoTurno(n)<<endl;
				int dimGruppo=grup.getDimGruppoTurno(n); //memorizzo la dimensione del gruppo
				pista.restituisciPosti(dimGruppo); //restituisco i posti alla pista di pattinaggio
				pista.aggiornaFatturato(dimGruppo,grup.getOraEntrataGruppo(n),ora); //aggiorno il fatturato totale contando cio che abbiamo guadagnato col gruppo che esce
				cout<<"il gruppo id:"<<grup.getIdGruppo(n)<<" e' uscito"<<endl; //stampo sul terminale l' id del gruppo che esce
				grup.esciDalTruno(n); //rimuovo dal turnon il gruppo che esce
				int *v=grup.getInizioAttesa(); //punto al primo gruppo della lista d' attesa
				if(pista.controlloPosti(grup.getDimTestaAttesa())){ //controllo se i posti bastano
					if(pat.controlloPattini(v,grup.getDimTestaAttesa(),ora)){ //controllo se ci sono abbastanza pattini per tutto il gruppo
						pista.assegnaPosti(grup.getDimTestaAttesa()); //assegno i posti al gruppo
						grup.mettiInTurno(v,grup.getDimTestaAttesa(),ora); //metto il gruppo in turno
						pat.prenotaPattini(v,grup.getDimTestaAttesa(),grup.getIdGruppo(grup.getTOTGruppiTurno()-1)); //assegno i pattini al gruppo
						grup.aggiornaAttesa(); // se il gruppo entra lo rimuovo dalla lista d' attesa
						cout<<"il primo gruppo in attesa puo entrare"<<endl; //scrivo su terminale che il primo gruppo d' attesa
						inserisciEvento("gruppo uscito, gruppo in attesa entrato"); //inserisco l' evento sull' interfaccia
					}else{
						cout<<"pattina ancora non disponibili, attesa prolungata"<<endl; //se i pattini per il primo gruppo d' attesa non sono ancora disponibili lo segnalo
						inserisciEvento("gruppo uscito, pattini per attesa ancora non disponibili"); //inserisco l' evento sull' interfaccia
					}
				}else{
					cout<<"spazio ancora insufficente, attesa prolungata"<<endl; //se non ce abbastanza spazio per il primo gruppo d' attesa lo segnalo
					inserisciEvento("gruppo uscito, posti per attesa ancora non sufficenti"); //inserisco l' evento sull' interfaccia
				}
			}
			if(possible==4 || possible==5){ //nel caso il possible sia uguale a 4 o 5 allora nulla succedera in questo momento
				cout<<"nessuno e' entrato ne uscito"<<endl; //segno l' evento sul terminale
				inserisciEvento("ne entrati e ne usciti"); //inserisco l' evento sull' interfaccia
			}
		pista.aggiornaCostiManutenzione(); //aggiorno i costi  di manutenzione
		pista.aggiornaUtile(pat.getCMPattini()); //aggiorno l' utile
		grup.stampaInTurno(); //stampo le persone presenti in pista
		pat.stampaAssegnazioni(); //stampo le assegnazioni dei pattini 
		pat.stampaUtilizzi(); //stampo l' utilizzo dei pattini
		grup.stampaInAttesa(); //stampo la lista d' attesa
		cout<<"fatturato totale: "<<pista.getFatturato()<<endl; //stampo il fatturato totale
		cout<<"utile: "<<pista.getUtile()<<endl; //stampo l' utile totale
		cout<<"posti rimasti: "<<pista.getPosti()<<endl; //stampo i posti rimasti
		cout<<endl<<"-------------------------------------------------------------------------------"<<endl<<endl; //divisore grafico per terminale
		inserisciOra(ora); //inserisco l' ora nell' interfaccia
		inserisciAttesa(grup.getTOTGruppiAttesa(),grup);//stampo sull' interfaccia la lista d' attesa
		inserisciCosti(pista.getFatturato(),(pat.getCMPattini()+pista.getCManutenzione()),pista.getUtile()); //stampa fatturato spese e utile sull' interfaccia
		stampaPista(grup); //stampa i gruppi in turno  sulla pista sull' interfaccia
		stampaStatoPattini(pat); //stampa lo stato dei pattini sull' interfaccia
		chiudiPagina(); //chiude e salva le modifiche all' interfaccia
		ora++; //aumento l' ora
		Sleep(5100); //aspetta un intervallo di tempo prima di ripetere il ciclo
	}
	return 0;
}
