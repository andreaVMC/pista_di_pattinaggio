#include <iostream>
using namespace std;
class pistaDiPattinaggio{ //creo la classe per gestire la pista di pattinaggio
	private: //creo le variabili che mi serviranno per monitorare la pista
		int posti;
		float cManutenzionePista;
		float fatturato;
		float utile;
	public:
		pistaDiPattinaggio(){ //azzero la pista di pattinaggio e ne definisco il  numero di posti
			posti=100;
			cManutenzionePista=0;
			fatturato=0;
			utile=0;
		}
		bool controlloPosti(int dim){ //metodo che controlla se i posti all' interno della pista di pastinaggio sono disponibili
			if((posti-dim)>=0){
				return true;
			}
			return false;
		}
		void assegnaPosti(int dim){ //metodo che assegna i posti grazie ad un input di dimensione del gruppo
			posti-=dim;
		}
		void restituisciPosti(int dim){ //metodo che libera i posti di un gruppo qunado esce
			posti+=dim;
		}
		int getPosti(){ //metodo che ritorna il numero rimanente di posti nella pista
			return posti;
		}
		void aggiornaCostiManutenzione(){ //metodo che aggiorna i costi di manutenzione
				cManutenzionePista+=0.2;
		}
		void aggiornaFatturato(int dim,int oraEntrata,int oraUscita){ //metodo che grazie alll' ora di entrarta e di uscita di un gruppo e la loro dimensione aggiorna il guadagno
			int time=oraUscita-oraEntrata;
			float cpm=dim*0.1;//costo per minuto
			fatturato+=(cpm*time);
		}
		float getFatturato(){ //ritorna il fatturato della pista
			return fatturato;
		}
		
		void aggiornaUtile(int cMPattini){ //aggiorna l'' utile della pista
			utile=fatturato-(cManutenzionePista+cMPattini);
		}
		
		float getUtile(){ //restituisce l' utile della pista
			return utile;
		}
		
		float getCManutenzione(){ //ritorna i costi di manutenzione per la pista
			return cManutenzionePista;
		}
};
