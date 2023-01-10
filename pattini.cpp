#include <iostream>
#include <fstream>
#include <stdio.h>
#define NUM 20
#define PAIA 6
using namespace std; //24...44
class pattini{ //creo la classe che mi servira per gestire i pattini
	private:
		int utilizzi[PAIA][NUM]; //matrice per segnarmi le volte che ogni pattine viene utilizzato
		bool disponibilita[PAIA][NUM]; //matrice per segnarmi se i pattini sono disponibili o non
		bool dispCopia[PAIA][NUM]; //matrice che mi serve per la verifica di disponibilita dei pattini
		float inizioManutenzione[PAIA][NUM]; //matrice che utilizzo per segnarmi l' inizio delle manutenzioni
		int assegnazione[PAIA][NUM]; //matrice che uso per segnarmi a che gruppo vengono distribuiti i rispettivi pattini
		int cManutenzionePattini; //intero per tener traccia dei costi della manutenzione dei pattini
		
		void copiaDisponibilita(){ //metodo che serve a copiare la matrice disponibilita all' interno di dispCopia
			int i,j;
			for(i=0;i<PAIA;i++){
				for(j=0;j<NUM;j++){
					dispCopia[i][j]=disponibilita[i][j];
				}
			}
		}
		
		void controllaManutenzione(int ora){ // metodo che controlla le varie entrate/uscite di manutenzione rispettivamente all' ora
			int i,j;
			/*controllo i  pattini che devono andare in manutenzione*/
			for(i=0;i<PAIA;i++){
				for(j=0;j<NUM;j++){
					if(utilizzi[i][j]==10){
						disponibilita[i][j]=false;
						utilizzi[i][j]=0;
						cManutenzionePattini+=2; //se un pattine va in manutenzione aggiungo la spesa ai costi di manutenzione
						inizioManutenzione[i][j]=ora;
					}
				}
			}
			/*controllo i pattini che devono uscire dalla manutenzione*/
			for(i=0;i<PAIA;i++){
				for(j=0;j<NUM;j++){
					if((inizioManutenzione[i][j]+15)<=ora){
						inizioManutenzione[i][j]=0;
						disponibilita[i][j]=true;
					}
				}
			}
		}
		
	public:
		
		pattini(){ //costruttore che utilizzo per azzerare gli utilizzi e portare a defaut lo stato di tutti i pattini
			int i,j;
			cManutenzionePattini=0;
			for(i=0;i<PAIA;i++)
				for(j=0;j<NUM;j++){
					utilizzi[i][j]=0;
					inizioManutenzione[i][j]=0;
					disponibilita[i][j]=true;
					assegnazione[i][j]=0;
				}
		}
		
		bool controlloPattini(int *v,int dim,int ora){ //metodo che controlla la disponibilita di tutti i pattinin per il gruppo
			int i,j,num;
			controllaManutenzione(ora);
			copiaDisponibilita();
			for(i=0;i<dim;i++){
				j=0;
				num=v[i]-24;
				while((dispCopia[j][num]==false || assegnazione[j][num]!=0) && j<=5){
					j++;
				}
				if(j==6){
					return false;
				}else if(j<=5){
					dispCopia[j][num]=false;
				}
			}
			return true;
		}
		
		bool xyDisponibilita(int x,int y){ //metodo che controlla la disponibilita di un pattine specifico attraverso un x ed una y
			return disponibilita[x][y];
		}
		
		bool xyManutenzione(int x,int y){ //metodo che controlla se un pattine è in manutenzione o meno
			if(inizioManutenzione[x][y]!=0){
				return true;
			}
			return false;
		}
		
		bool xyAssegnazioni(int x,int y){ //metodo che controlla se un pattine è assegnato ad un gruppo o meno
			if(assegnazione[x][y]==0){
				return true;
			}
			return false;
		}
		
		void prenotaPattini(int *v,int dim,int idgruppo){ //metodo che usufruendo di un gruppo con dimensione ed id prenota i pattini necessari
			int i,j,num;
			for(i=0;i<dim;i++){
				j=0;
				num=v[i]-24;
				while(disponibilita[j][num]==false || assegnazione[j][num]!=0){
					j++;
				}
				disponibilita[j][num]=false;
				utilizzi[j][num]++;
				assegnazione[j][num]=idgruppo;
			}
		}
		
		void stampaAssegnazioni(){ //metodo che stampa su cmd le assegnazione dei pattini
			int i,j;
			cout<<"------------assegnazioni-------------"<<endl;
			for(i=0;i<PAIA;i++){
				for(j=0;j<NUM;j++){
					printf("%5d",assegnazione[i][j]);
				}
				cout<<endl;
			}
			cout<<endl<<"-------------------"<<endl<<endl;
		}
		
		void stampaUtilizzi(){ //metodo che stampa gli utilizzi dei pattinin su cmd
			int i,j;
			cout<<"------------utilizzi-------------"<<endl;
			for(i=0;i<PAIA;i++){
				for(j=0;j<NUM;j++){
					printf("%5d",utilizzi[i][j]);
				}
				cout<<endl;
			}
			cout<<endl<<"-------------------"<<endl<<endl;
		}
		
		void restituisciPattini(int grupid){ //metodo che (quando un gruppo esce dalla pista) usufruendo dell' id restituisce i pattini 
			int i,j;
			for(i=0;i<PAIA;i++){
				for(j=0;j<NUM;j++){
					if(assegnazione[i][j]==grupid){
						disponibilita[i][j]=true;
						assegnazione[i][j]=0;
					}
				}
			}
		}
		
		int getCMPattini(){ //metodo che restituisce i costi di manutenzione
			return cManutenzionePattini;
		}
};
