#include <iostream>
#include <time.h>
#define NMAXGRUPPI 100
#define NMAXPERSONE 10
#define NMAXATTESA 10
using namespace std;
class gruppi{ //creo la classe che usero per gestire i gruppi
	private: 
		int inTurno[NMAXGRUPPI][NMAXPERSONE]; //in entrambi i casi mi aspetto un massimo di 10 persone per gruppo
		int oraEntrata[NMAXGRUPPI]; //array che segna l' ora di entrata dei gruppi
		int inAttesa[NMAXATTESA][NMAXPERSONE]; //matrice che memorizza i gruppi in coda d' attesa
		int idGruppo[NMAXGRUPPI]; //array che memorizza gli id dei gruppi
		int codice;
		
		void eliminaVuoti(){ //metodo che elimina i gruppi che escono dalla pista, dalla lista dei gruppi totali
			int i,j,k;
			for(i=0;i<NMAXGRUPPI-1;i++){
				if(inTurno[i][0]==0){
					for(j=i;j<NMAXGRUPPI-1;j++){
						for(k=0;k<NMAXPERSONE;k++){
							inTurno[j][k]=inTurno[j+1][k];
						}
						idGruppo[j]=idGruppo[j+1];
						oraEntrata[j]=oraEntrata[j+1];		
					}
				}
			}
			for(i=0;i<NMAXPERSONE;i++){
				inTurno[NMAXGRUPPI-1][i]=0;
			}
			oraEntrata[NMAXGRUPPI-1]=idGruppo[NMAXGRUPPI-1]=0;
		}
	public:
		gruppi(){ //costruttore che porta a default tutti i vari parametri
			srand(time(NULL));
			int i,j;
			codice=1;
			for(i=0;i<NMAXGRUPPI;i++){
				for(j=0;j<NMAXPERSONE;j++){
					inTurno[i][j]=0;
				}
				oraEntrata[i]=0;
				idGruppo[i]=0;
			}
			for(i=0;i<NMAXATTESA;i++){
				for(j=0;j<NMAXPERSONE;j++){
					inAttesa[i][j]=0;
				}
			}
		}
		
		void creagruppo(int *v,int dim){ //metodo che crea gruppo sul puntatore di un array con la dimensione e lo ripassa al main
			int i;
			for(i=0;i<dim;i++)
				v[i]=rand()%20+24;
		}
		
		void stampaGruppo(int *v,int dim){ //metdo che stampa un gruppo avendone puntatore e dimensione
			int i;
			for(i=0;i<dim;i++){
				cout<<v[i]<<" ";
			}
			cout<<endl;
		}
		
		void mettiInTurno(int *v,int dim,int ora){ //metodo che aggiunge alla lista dei turni un gruppo
			int i,id;
			id=getTOTGruppiTurno();
			for(i=0;i<dim;i++)
				inTurno[id][i]=v[i];
			oraEntrata[id]=ora;
			idGruppo[id]=codice;
			codice++;
		}
		
		int getTOTGruppiTurno(){ //metdo che ritorna il numero di gruppi in turno
			int ctr=0;
			while(inTurno[ctr][0]!=0){
				ctr++;
			}
			return ctr;
		}
		
		void stampaInTurno(){ //metodo che stampa i gruppi in turno
			int i,j;
			cout<<endl<<"---------------- in Turno -----------"<<endl;
			for(i=0;i<getTOTGruppiTurno();i++){
				cout<<"id: "<<idGruppo[i]<<" | ora entrata: "<<oraEntrata[i]<<" | gruppo: ";
				for(j=0;inTurno[i][j]!=0 && j<NMAXPERSONE;j++){
					cout<<inTurno[i][j]<<" ";
				}
				cout<<endl;
			}
			cout<<"--------------------------------------"<<endl;
		}
		
		int getIdGruppo(int n){ //metodo che grazie al riferimento assolutno di un gruppo ne restituisce l' id
			return idGruppo[n];
		}
		
		int getDimGruppoTurno(int n){ //metodo che restituisce la dimensione di un gruppo usandone il riferimento assoluto
			int dim=0;
			for(int i=0;inTurno[n][i]!=0 && i<=NMAXPERSONE;i++){
				dim++;
			}
			return dim;
		}
		
		void esciDalTruno(int n){ //metodo che toglie dal turno un gruppo usandone un refirimento assoluto
			int i;
			for(i=0;i<NMAXPERSONE;i++){
				inTurno[n][i]=0;
			}
			oraEntrata[n]=0;
			idGruppo[n]=0;
			eliminaVuoti();
		}
		
		int getOraEntrataGruppo(int n){ //metodo che ritorna l' ora di entrata di un gruppo
			return oraEntrata[n];
		}
		
		bool controllaCoda(){ //metodo che controlla se ce ancora spazzio nella lista d' attesa
			int i;
			for(i=0;i<NMAXATTESA;i++){
				if(inAttesa[i][0]==0){
					return true;
				}
			}
			return false;
		}
		
		void mettiInAttesa(int *v,int dim){ //metodo che mette in attesa un gruppo
			int i,id;
			id=getTOTGruppiAttesa();
			for(i=0;i<dim;i++)
				inAttesa[id][i]=v[i];
		}
		
		void stampaInAttesa(){ //metodo che stampa i gruppi in attesa
			int i,j;
			cout<<endl<<"----------------- in Attesa -----------"<<endl;
			for(i=0;i<getTOTGruppiAttesa();i++){
				cout<<"gruppo "<<i<<": ";
				for(j=0;inAttesa[i][j]!=0 && j<NMAXPERSONE;j++){
					cout<<inAttesa[i][j]<<" ";
				}
				cout<<endl;
			}
			cout<<"--------------------------------------"<<endl;
		}
		
		int getTOTGruppiAttesa(){ //metodo che ritorna il numero di gruppi in attesa
			int ctr=0;
			while(inAttesa[ctr][0]!=0 && ctr<NMAXATTESA){
				ctr++;
			}
			return ctr;
		}
		
		int getDimTestaAttesa(){ //metodo che ritorna la dimensione del primo gruppo in attesa
			int dim=0;
			for(int i=0;inAttesa[0][i]!=0 && i<=NMAXPERSONE;i++){
				dim++;
			}
			return dim;
		}
		
		int* getInizioAttesa(){ //metodo che ritorna il puntatore che punto alla lista d' attesa
			return *inAttesa;
		}
		
		int xyAttesa(int x,int y){ //metodo che ritorna uno specifico punto della lista d' attesa
			return inAttesa[x][y];
		}
		
		int xyTurno(int x,int y){ //metodo che ritorna uno specifico d' ato della lista in turno
			return inTurno[x][y];
		}
		
		void aggiornaAttesa(){ //metodo che aggiorna la lista d' attesa quando se ne va qualcuno
			int i,j;
			for(i=0;i<NMAXATTESA;i++){
				for(j=0;j<NMAXPERSONE;j++){
					inAttesa[i][j]=inAttesa[i+1][j];
				}
			}
			for(i=0;i<NMAXPERSONE;i++){
				inAttesa[NMAXATTESA-1][i]=0;
			}
		}
};
