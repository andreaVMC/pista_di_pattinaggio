#include <iostream>
#include <time.h>
#define NMAXGRUPPI 100
#define NMAXPERSONE 10
#define NMAXATTESA 10
using namespace std;
class gruppi{
	private: 
		int inTurno[NMAXGRUPPI][NMAXPERSONE]; //in entrambi i casi mi aspetto un massimo di 10 persone per gruppo
		int oraEntrata[NMAXGRUPPI];
		int inAttesa[NMAXATTESA][NMAXPERSONE];
		int idGruppo[NMAXGRUPPI];
		int codice;
		
		void eliminaVuoti(){
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
		gruppi(){
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
		
		void creagruppo(int *v,int dim){
			int i;
			for(i=0;i<dim;i++)
				v[i]=rand()%20+24;
		}
		
		void stampaGruppo(int *v,int dim){
			int i;
			for(i=0;i<dim;i++){
				cout<<v[i]<<" ";
			}
			cout<<endl;
		}
		
		void mettiInTurno(int *v,int dim,int ora){
			int i,id;
			id=getTOTGruppiTurno();
			for(i=0;i<dim;i++)
				inTurno[id][i]=v[i];
			oraEntrata[id]=ora;
			idGruppo[id]=codice;
			codice++;
		}
		
		int getTOTGruppiTurno(){
			int ctr=0;
			while(inTurno[ctr][0]!=0){
				ctr++;
			}
			return ctr;
		}
		
		void stampaInTurno(){
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
		
		int getIdGruppo(int n){
			return idGruppo[n];
		}
		
		int getDimGruppoTurno(int n){
			int dim=0;
			for(int i=0;inTurno[n][i]!=0 && i<=NMAXPERSONE;i++){
				dim++;
			}
			return dim;
		}
		
		void esciDalTruno(int n){
			int i;
			for(i=0;i<NMAXPERSONE;i++){
				inTurno[n][i]=0;
			}
			oraEntrata[n]=0;
			idGruppo[n]=0;
			eliminaVuoti();
		}
		
		int getOraEntrataGruppo(int n){
			return oraEntrata[n];
		}
		
		bool controllaCoda(){
			int i;
			for(i=0;i<NMAXATTESA;i++){
				if(inAttesa[i][0]==0){
					return true;
				}
			}
			return false;
		}
		
		void mettiInAttesa(int *v,int dim){
			int i,id;
			id=getTOTGruppiAttesa();
			for(i=0;i<dim;i++)
				inAttesa[id][i]=v[i];
		}
		
		void stampaInAttesa(){
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
		
		int getTOTGruppiAttesa(){
			int ctr=0;
			while(inAttesa[ctr][0]!=0 && ctr<NMAXATTESA){
				ctr++;
			}
			return ctr;
		}
		
		int getDimTestaAttesa(){
			int dim=0;
			for(int i=0;inAttesa[0][i]!=0 && i<=NMAXPERSONE;i++){
				dim++;
			}
			return dim;
		}
		
		int* getInizioAttesa(){
			return *inAttesa;
		}
		
		int xyAttesa(int x,int y){
			return inAttesa[x][y];
		}
		
		int xyTurno(int x,int y){
			return inTurno[x][y];
		}
		
		void aggiornaAttesa(){
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
