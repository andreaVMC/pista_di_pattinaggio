#include <iostream>
using namespace std;
class pistaDiPattinaggio{
	private:
		int posti;
		float cManutenzionePista;
		float fatturato;
		float utile;
	public:
		pistaDiPattinaggio(){
			posti=100;
			cManutenzionePista=0;
			fatturato=0;
			utile=0;
		}
		bool controlloPosti(int dim){
			if((posti-dim)>=0){
				return true;
			}
			return false;
		}
		void assegnaPosti(int dim){
			posti-=dim;
		}
		void restituisciPosti(int dim){
			posti+=dim;
		}
		int getPosti(){
			return posti;
		}
		void aggiornaCostiManutenzione(){
				cManutenzionePista+=0.2;
		}
		void aggiornaFatturato(int dim,int oraEntrata,int oraUscita){
			int time=oraUscita-oraEntrata;
			float cpm=dim*0.1;//costo per minuto
			fatturato+=(cpm*time);
		}
		float getFatturato(){
			return fatturato;
		}
		
		void aggiornaUtile(int cMPattini){
			utile=fatturato-(cManutenzionePista+cMPattini);
		}
		
		float getUtile(){
			return utile;
		}
		
		float getCManutenzione(){
			return cManutenzionePista;
		}
};
