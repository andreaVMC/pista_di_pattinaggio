/*libreria per interfaccia grafica*/
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "gruppi.cpp"
using namespace std;
ofstream file; //creo il file globale su cui scrivero i vari dati

void inizializzaPagina(){ //funzione che serve per inizializzare la pagina ed aprire i vari tag
	file.open("index.txt",ios::out);
	file<<"<!DOCTYPE html>";
	file<<"<html><head><title>Pista Di Pattinaggio Andrea Vaccaro</title><link rel=\"stylesheet\" href=\"style.css\"><script src=\"js.js\"></script></head>";
    file<<"<body onload=\"aggiorna()\"><div class=\"container\"><div class=\"row-1\"><div class=\"logo\"><img src=\"IMG/logo-text.png\" class=\"logo-img\"></div><div class=\"evento\">";
}

void inserisciEvento(string s){ //funzione che inserisce l' evento del tempo corrente
	file<<"\n<div class=\"events\">";
	file<<s;
	file<<"</div></div>";
}

void inserisciOra(int ora){ //metodo che va a scrivere sulla GUI l' ora corrente
	int h=0,m=0;
	int i;
	for(i=0;i<ora;i++){
		m++;
		if(m==60){
			h++;
			m=0;
		}
		if(h==24){
			h=0;
		}
	}
	file<<"<div class=\"ora\"><div class=\"orario\">";
	if(h<=9){
		file<<"0"<<h<<":";
	}else{
		file<<h<<":";
	}
	if(m<=9){
		file<<"0"<<m;
	}else{
		file<<m;
	}
	file<<"</div></div></div>";
}

void inserisciAttesa(int totGruppi,gruppi grup){ //metodo che inserisce la lista d' attesa nella GUI
	file<<"<div class=\"row-2\"><div class=\"row-2-1\"><div class=\"attesa\">";
    file<<"<table class=\"table-attesa\"><tr><td colspan=\"2\" class=\"titolo-attesa\">Coda d' attesa</td></tr>";
    int i,j;
    for(i=0;i<totGruppi;i++){
    	file<<"<tr>";
    	file<<"<td class=\"id-attesa\">"<<(i+1)<<"</td>";
    	file<<"<td class=\"gruppo-attesa\">";
    	for(j=0;grup.xyAttesa(i,j)!=0 && j<10;j++){
    		file<<grup.xyAttesa(i,j)<<" ";
		}
		file<<"</td></tr>";
	}
	for(i=i;i<10;i++){
		file<<"<tr>";
    	file<<"<td class=\"id-attesa\">"<<(i+1)<<"</td>";
    	file<<"<td class=\"gruppo-attesa\"></td></tr>";
	}
	file<<"</table></div>";
}

void inserisciCosti(int fatturato,float cmanutenzione,float utile){ //metodo che scrive i vari costi e ricavi sulla GUI
	file<<"<div class=\"fatturato\"><div class=\"testo-fatturato\">Fatturato: ";
	file<<fatturato<<"&euro;</div></div>";
	file<<"<div class=\"costo-manutenzione\"><div class=\"testo-costo-manutenzione\">Spese: ";
	file<<cmanutenzione<<"&euro;</div></div>";
	if(utile>0){
		file<<"<div class=\"utile\"><div class=\"testo-utile\" style=\"color: rgba(11, 179, 11, 0.589)\">Utile: ";
		file<<utile<<"&euro;</div></div>";
	}else if(utile<0){
		file<<"<div class=\"utile\"><div class=\"testo-utile\" style=\"color: rgba(255, 0, 0, 0.658)\">Utile: ";
		file<<utile<<"&euro;</div></div>";
	}else if(utile==0){
		file<<"<div class=\"utile\"><div class=\"testo-utile\">Utile: ";
		file<<utile<<"&euro;</div></div>";
	}
	file<<"</div>";
}

void stampaPista(gruppi grup){ //metodo che disegna graficamente lo stato della pista
	int i,j,x=0,y=0,ctr=0;
	file<<"<div class=\"pista\"><table class=\"table-pista\"><tr><td class=\"titolo-pista\" colspan=\"10\">Pista di pattinaggio</td></tr>";
	for(i=0;i<10;i++){
		file<<"<tr>";
		for(j=0;j<10;j++){
			if(grup.xyTurno(x,y)==0 && x<100){
				x++;
				y=0;
			}
			if(grup.xyTurno(x,y)==0){
				file<<"<td class=\"libero\"></td>";
			}else{
				file<<"<td class=\"occupato\">"<<grup.xyTurno(x,y)<<"</td>";
				y++;
			}
		}
		file<<"</tr>";
	}
	file<<"</table></div>";
}

void stampaStatoPattini(pattini pat){ //metodo che stampa lo stato dei vari patttini graficamente 
	int i,j;
	file<<"<div class=\"pattini\"><table class=\"table-pattini\"><tr><td class=\"titolo-pattini\">Pattini</td></tr>";
	for(i=0;i<20;i++){
		file<<"<tr>";
		file<<"<td class=\"n-pattini\">"<<(i+24)<<"</td>";
		for(j=0;j<6;j++){
			if(pat.xyAssegnazioni(j,i)){
				file<<"<td class=\"disponibile\"></td>";
			}else if(pat.xyManutenzione(j,i)){
				file<<"<td class=\"manutenzione\"></td>";
			}else{
				file<<"<td class=\"non-disponibile\"></td>";
			}
		}
		file<<"</tr>";
	}
	file<<"</table></div>";
}

void chiudiPagina(){ //metodo che si occupa di chiudere l' interfaccia grafica e di salvarla
	file<<"</div></div><div class=\"credits\" onclick=\"credits()\">by Andrea Vaccaro</div></body></html>";
	file.close();
}

void creagui(){
	char c;
	FILE *in=fopen("index.txt","r");
	FILE *out=fopen("index.html","w");
	while(!feof(in)){
		fscanf(in,"%c",&c);
		fprintf(out,"%c",c);
	}
	fclose(in);
	fclose(out);
}
