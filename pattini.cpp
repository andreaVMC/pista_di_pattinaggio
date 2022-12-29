#include <iostream>
#include <fstream>
#include <stdio.h>
#define NUM 20
#define PAIA 6
using namespace std; //24...44
class pattini{
	private:
		int utilizzi[PAIA][NUM];
		bool disponibilita[PAIA][NUM];
		bool dispCopia[PAIA][NUM];
		float inizioManutenzione[PAIA][NUM];
		int assegnazione[PAIA][NUM];
		int cManutenzionePattini;
		
		void copiaDisponibilita(){
			int i,j;
			for(i=0;i<PAIA;i++){
				for(j=0;j<NUM;j++){
					dispCopia[i][j]=disponibilita[i][j];
				}
			}
		}
		
		void controllaManutenzione(int ora){
			int i,j;
			/*controllo i  pattini che devono andare in manutenzione*/
			for(i=0;i<PAIA;i++){
				for(j=0;j<NUM;j++){
					if(utilizzi[i][j]==10){
						disponibilita[i][j]=false;
						utilizzi[i][j]=0;
						cManutenzionePattini+=2;
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
		
		pattini(){
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
		
		bool controlloPattini(int *v,int dim,int ora){
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
		
		bool xyDisponibilita(int x,int y){
			return disponibilita[x][y];
		}
		
		bool xyManutenzione(int x,int y){
			if(inizioManutenzione[x][y]!=0){
				return true;
			}
			return false;
		}
		
		bool xyAssegnazioni(int x,int y){
			if(assegnazione[x][y]==0){
				return true;
			}
			return false;
		}
		
		void prenotaPattini(int *v,int dim,int idgruppo){
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
		
		void stampaAssegnazioni(){
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
		
		void stampaUtilizzi(){
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
		
		void restituisciPattini(int grupid){
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
		
		int getCMPattini(){
			return cManutenzionePattini;
		}
};
