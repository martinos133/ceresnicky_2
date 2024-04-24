#include <iostream>
#include <fstream>
#include <cstring>				// Potrebne pre funkciu strcpy
#include <sstream>				// Potrebne pre funkciu istringstream
#include <cmath>				// Potrebne pre funkciu pow, vyuzivanu vo funkcii arrayToInt
//#include <string>
#include "lucky_hit.h"			// Potrebne pre pripojenie triedy TPlayer
#include "subory_txt.h" 		// Pripojenie hlavickoveho suboru pre funkcie nacitania a zobrazenia txt suboru:
								// struct riadky_txt* nacitaj_txt(const char* nazov_suboru, int &pocet_riadkov)
								// void vypis_txt(const riadky_txt* pole, const int pocet_riadkov)
using namespace std;			



int charArrayToInt(char arr[], int size);    //konverzia pola char na int
string intToString(int cislo); 		//funkcia konverzie premennej int na string, v programe je vyuzivana pri exporte do game.txt
bool hraLuckyHit(class TPlayer &player1, class TPlayer &player2);  //funkcia na samotnu hru
int skopiruj_riadok(char* buffer, int start, int end, char* novy);  //funkcia skopiruje od pozicie start do pozicie end znaky z buffer do novy a vrati pocet znakov v riadku

int main()
{
  //Definovanie instancie triedy TPlayer:
  class TPlayer player1;
  class TPlayer player2;
  
  //Definovanie premennych potrebnych pocas chodu programu:
  string prikaz = "XXXX";		//prikaz na ovladanie hry
  int pocet_zivotov=0;			//pocet zivotov hracov
  int pocet_cisel=0;			//pocet cisel v zasobniku
  int dolne=0;					//dolna hranica cisel
  int horne=0;					//horna hranica cisel
  int cislo=0;					//cislo	v zasobniku	
  bool platnost_cisla=true;		//platnost cisla v zadanom rozsahu	
  bool mozny_export=true;		//priznak, ci je mozne exportovat udaje do vystupneho suboru
  int i=0;
  
  char subor_vstup_vystup[]="game.txt";				//nazov vstupneho a vystupneho suboru uboru
  char vloz_enter[]="\n"; //sluzi na doplnenie znaku Enter pri zapise do vystupneho suboru
  
  
   //Definovanie prikazov NEW, LOAD, EXIT:
  while (prikaz != "EXIT")
  {
  	cout<<"Zadaj prikaz (NEW-nova hra,LOAD-nahratie ulozenej hry,EXIT-ulozenie hry v game.txt a ukoncenie hry: ";
  	cin>>prikaz; //nacita do premennej prikaz zadany prikaz uzivatelom 
  	
  	//********************** Prikaz NEW *****************************
  	if(prikaz == "NEW")   //nahratia parametrov novej hry
  	{
		cout<<"Zadaj pocet zivotov hracov: ";
  		cin>>pocet_zivotov;								//nacitanie poctu zivotov
  		player1.pocet_zivotov=pocet_zivotov;
  		player2.pocet_zivotov=player1.pocet_zivotov;
  		
		cout<<"Zadaj pocet prvkov v zasobniku: ";
  		cin>>pocet_cisel;								//nacitanie poctu prvkov v zasobniku
  		player1.ulozZasobnikPocet(pocet_cisel);
  		player2.ulozZasobnikPocet(pocet_cisel);
   		
  		cout<<"Zadaj dolnu hranicu cisel: ";
  		cin>>dolne;										//nacitanie dolnej hranice cisel
  		player1.dolne=dolne;
		player2.dolne=dolne;					
  		cout<<"Zadaj hornu hranicu cisel: ";
  		cin>>horne;										//nacitanie hornej hranice cisel
  		player1.horne=horne;
  		player2.horne=horne;
  		
  		system("cls");									//vymazanie konzoloveho okna
		cout<<endl<<"Zadaj meno hraca 1: ";
  		cin>>player1.meno_hraca;
  		
		for(i=0;i<player1.vratPocet();i++)				//naplnenie zasobnika hraca 1
  		{
  			cout<<"Zadaj "<<i+1<<".cislo: ";
  			cin>>cislo;
  			platnost_cisla=player1.naplnZasobnik(i, cislo);
  			if(platnost_cisla==false)
  			{
  				cout<<"Cislo je mimo povoleny rozsah"<<endl;
  				i--;
			}
		}
		
		system("cls");					//vymazanie konzoloveho okna
		cout<<endl<<"Zadaj meno hraca 2: ";
  		cin>>player2.meno_hraca;
  		
		for(i=0;i<player2.vratPocet();i++)				//naplnenie zasobnika hraca 2
  		{
  			cout<<"Zadaj "<<i+1<<".cislo: ";
  			cin>>cislo;
  			platnost_cisla=player2.naplnZasobnik(i, cislo);
  			if(platnost_cisla==false)
  			{
  				cout<<"Cislo je mimo povoleny rozsah"<<endl;
  				i--;
			}
		}
  		
  		mozny_export=hraLuckyHit(player1,player2);			//spustenie samotnej hry
  		
  		
	}
	//********************** koniec Prikazu NEW ***********************
  	
  	//********************** Prikaz LOAD ******************************
  	if(prikaz == "LOAD")   //nahratia parametrov novej hry
  	{
  		ifstream vstup (subor_vstup_vystup, ifstream::binary);  //vstupny subor na nacitanie
  
  		//*********** osetrenie stavu, ked sa zadany subor nenachadza *********************
  		if(!vstup)
  		{
    		cerr<< "nenasiel som subor s nazvom "<<subor_vstup_vystup;
    		exit(-1);
  		}
   		vstup.close();
   		//*********** koniec osetrenia stavu, ked sa zadany subor nenachadza **************
   
   		int pocet_riadkov=0;						//pocet riadkov vstupneho suboru	
		char pomocne_pole[81];						//pomocne pole pre nacitavanie jednotlivych poloziek
		int pom_pocet=0;							//sluzi na urcenie poctu znakov pre jednu premennu
		int urcenie_premennej=0;						//urci, do ktorej premennej priradi hodnotu
		int pozicia=-1;
   		struct riadky_txt* pole_riadkov = nacitaj_txt(subor_vstup_vystup, pocet_riadkov);	//Vrati smernik na naplnene pole typu struct riadky_txt s poctom pocet_riadkov
      	if(pocet_riadkov!=3)		//subor nie je korektne nahraty
      	{
      		cout<<"Nie je mozne nahrat subor, je potrebne zacat novu hru"<<endl;
		}
		else
		{ 
		
		//nacitanie prveho riadku - parametre hry:
      	while((pozicia+pom_pocet) < (pole_riadkov+0)->pocet_riadok)	
      	{
		  	pozicia++;
			while((int)(pole_riadkov+0)->riadok[pozicia+pom_pocet] != 59 && (pozicia+pom_pocet) < (pole_riadkov+0)->pocet_riadok)  //59 je v ASCII znak ";"
      		{
      			pomocne_pole[pom_pocet]=(pole_riadkov+0)->riadok[pom_pocet+pozicia];  //nahra do pomocne_pole premennu oddelenu ";"
      			pom_pocet++;
      			
      			if(urcenie_premennej == 0) 			//nahratie poctu zivotov
      			{
				  	pocet_zivotov = charArrayToInt(pomocne_pole, pom_pocet);	//konvertuje pole typu char na premennu typu int
				}
				if(urcenie_premennej == 1) 			//nahratie poctu cisel
      			{
				  	pocet_cisel = charArrayToInt(pomocne_pole, pom_pocet);	//konvertuje pole typu char na premennu typu int
				}
				if(urcenie_premennej == 2) 			//nahratie dolnej hranice
      			{
				  	dolne = charArrayToInt(pomocne_pole, pom_pocet);	//konvertuje pole typu char na premennu typu int
				}
				if(urcenie_premennej == 3) 			//nahratie hornej hranice
      			{
				  	horne = charArrayToInt(pomocne_pole, pom_pocet);	//konvertuje pole typu char na premennu typu int
				}
				
      			
			}
			if((int)(pole_riadkov+0)->riadok[pozicia+pom_pocet] == 59) //urci koniec premennej z dovodu znaku ";"
			{
				
				if(pom_pocet>0) urcenie_premennej++;
				pozicia=pozicia+pom_pocet;
				pom_pocet=0;
			}
			 
		}
		
		cout<<"pocet zivotov je "<<pocet_zivotov<<endl;
		cout<<"pocet cisel je "<<pocet_cisel<<endl;
		cout<<"dolna hranica je "<<dolne<<endl;
		cout<<"horna hranica je "<<horne<<endl;
		
		//nacitanie druheho riadku - hrac 1:
		i=0;
		pozicia=0;  
		while(pozicia<(pole_riadkov+1)->pocet_riadok)	//urcenie poctu prvkov
		{
			if((int)(pole_riadkov+1)->riadok[pozicia] == 59)	//59 je v ASCII znak ";"
				i++;
			pozicia++;
		}  
		player1.ulozZasobnikPocet(i-1);				//pocet prvkov v zasobniku je pocet znakov ";" - 1
		player1.dolne=dolne;
		player1.horne=horne;
		pozicia=0;
		while((int)(pole_riadkov+1)->riadok[pozicia] != 59)	//59 je v ASCII znak ";", prvy vyskyt
		{
			pozicia++;
		}
		pom_pocet=skopiruj_riadok((pole_riadkov+1)->riadok, 0, pozicia, pomocne_pole); //skopiruje meno hraca do pomocne_pole
		player1.meno_hraca.assign(pomocne_pole);				//prevod pole na string
		pom_pocet=pozicia+1;									//sluzi na ulozenie dolnej pozicie pola
		while((int)(pole_riadkov+1)->riadok[pozicia+1] != 59)	//59 je v ASCII znak ";", druhy vyskyt
		{
			pozicia++;
		}
		pom_pocet=skopiruj_riadok((pole_riadkov+1)->riadok, pom_pocet, pozicia, pomocne_pole); //skopiruje pocet zivotov do pomocne_pole
		player1.pocet_zivotov=charArrayToInt(pomocne_pole, pom_pocet);
		pom_pocet=pozicia+1;
		
		//nacitanie prvkov hraca 1:        
		int prvok;
		i=0;
		pom_pocet=0;
		while((pozicia+2+i)<(pole_riadkov+1)->pocet_riadok)
		{
			if((int)(pole_riadkov+1)->riadok[pozicia+2+i] != 59)
			{
				prvok=(int)(pole_riadkov+1)->riadok[pozicia+2+i]-(int)'0';
				player1.naplnZasobnik(pom_pocet, prvok);
				i++;
				pom_pocet++;
			}
			else i++;
		}
		
		//nacitanie tretieho riadku - hrac 2:
		char pomocne_pole2[81];
		i=0;
		pozicia=0;  
		while(pozicia<(pole_riadkov+2)->pocet_riadok)	//urcenie poctu prvkov
		{
			if((int)(pole_riadkov+2)->riadok[pozicia] == 59)	//59 je v ASCII znak ";"
				i++;
			pozicia++;
		}  
		player2.ulozZasobnikPocet(i-1);				//pocet prvkov v zasobniku je pocet znakov ";" - 1
		player2.dolne=dolne;
		player2.horne=horne;
		pozicia=0;
		while((int)(pole_riadkov+2)->riadok[pozicia] != 59)	//59 je v ASCII znak ";", prvy vyskyt
		{
			pozicia++;
		}
		pom_pocet=skopiruj_riadok((pole_riadkov+2)->riadok, 0, pozicia, pomocne_pole2); //skopiruje meno hraca do pomocne_pole
		player2.meno_hraca.assign(pomocne_pole2);				//prevod pole na string
		pom_pocet=pozicia+1;									//sluzi na ulozenie dolnej pozicie pola
		while((int)(pole_riadkov+2)->riadok[pozicia+1] != 59)	//59 je v ASCII znak ";", druhy vyskyt
		{
			pozicia++;
		}
		pom_pocet=skopiruj_riadok((pole_riadkov+2)->riadok, pom_pocet, pozicia, pomocne_pole2); //skopiruje pocet zivotov do pomocne_pole
		player2.pocet_zivotov=charArrayToInt(pomocne_pole2, pom_pocet);
		pom_pocet=pozicia+1;
		
		//nacitanie prvkov hraca 2:   
		i=0;
		pom_pocet=0;
		while((pozicia+2+i)<(pole_riadkov+2)->pocet_riadok)
		{
			if((int)(pole_riadkov+2)->riadok[pozicia+2+i] != 59)
			{
				prvok=(int)(pole_riadkov+2)->riadok[pozicia+2+i]-(int)'0';
				player2.naplnZasobnik(pom_pocet, prvok);
				i++;
				pom_pocet++;
			}
			else i++;
		}
		/*
		cout<<endl;
		cout<<"meno hraca 1 je "<<player1.meno_hraca<<endl;
		cout<<"pocet zivotov hraca 1 je "<<player1.pocet_zivotov<<endl;
		cout<<"pocet prvkov hraca 1 je "<<player1.vratPocet()<<endl;
		player1.zobrazZasobnik();
			
		cout<<endl;
		cout<<"meno hraca 2 je "<<player2.meno_hraca<<endl;
		cout<<"pocet zivotov hraca 2 je "<<player2.pocet_zivotov<<endl;
		cout<<"pocet prvkov hraca 2 je "<<player2.vratPocet()<<endl;
		player2.zobrazZasobnik();
		cout<<endl;
		*/
		mozny_export=hraLuckyHit(player1,player2);			//spustenie samotnej hry
      	
   		//vypis_txt(pole_riadkov, pocet_riadkov); 	// Vypis riadkov z pole_riadkov
   		delete[] pole_riadkov;						//nezabudnut uvolnit pamat po pouziti
	}
	}
	//********************** koniec Prikazu LOAD ***********************
  }
  
  
  
  //************* Nahratie udajov do suboru game.txt *******************
  ofstream vystup (subor_vstup_vystup, ios::app);     	//vystup formou pridavania
  ofstream vystup_prvy (subor_vstup_vystup); 		  	//vystup formou novych udajov
  
  //***************** Nahratie parametrov hry do game.txt ***************************
  string parametre_hry;									//premenna na nacitanie parametrov hry
  parametre_hry=intToString(pocet_zivotov)+";"+intToString(pocet_cisel)+";"+intToString(dolne)+";"+intToString(horne);
  int pocet_parametre_hry=parametre_hry.length();			//pocet znakov
  const char* pole_parametrov = parametre_hry.c_str();		//prevod string na array
  vystup_prvy.write(pole_parametrov,pocet_parametre_hry); 	//metoda write ako prvy parameter pozaduje char*
  vystup.write(vloz_enter,1); 	//doplni znak Enter 
  //***************** Koniec nahratia parametrov hry do game.txt *********************
  
  if(mozny_export==true)
  {
  
  //***************** Nahratie parametrov hraca1 do game.txt ***************************
  parametre_hry=player1.meno_hraca+";"+intToString(player1.pocet_zivotov);
  for(i=0;i<player1.vratPocet();i++)					//nacitanie jednotlivych prvkov hraca 1:
  {
  	  parametre_hry=parametre_hry+";";
	  parametre_hry=parametre_hry+intToString(player1.vratHodnotuZasobnika(i));
  }
  		
  pocet_parametre_hry=parametre_hry.length();			//pocet znakov
  const char* pole_hraca1 = parametre_hry.c_str();		//prevod string na array
  vystup.write(pole_hraca1,pocet_parametre_hry); 		//metoda write ako prvy parameter pozaduje char*
  vystup.write(vloz_enter,1); 							//doplni znak Enter 
  //***************** Koniec nahratia parametrov hraca1 do game.txt *********************
  
  //***************** Nahratie parametrov hraca2 do game.txt ***************************
  parametre_hry=player2.meno_hraca+";"+intToString(player2.pocet_zivotov);
  for(i=0;i<player2.vratPocet();i++)					//nacitanie jednotlivych prvkov hraca 1:
  {
  	  parametre_hry=parametre_hry+";";
	  parametre_hry=parametre_hry+intToString(player2.vratHodnotuZasobnika(i));
  }
  		
  pocet_parametre_hry=parametre_hry.length();			//pocet znakov
  const char* pole_hraca2 = parametre_hry.c_str();		//prevod string na array
  vystup.write(pole_hraca2,pocet_parametre_hry); 		//metoda write ako prvy parameter pozaduje char*
  vystup.write(vloz_enter,1); 							//doplni znak Enter 
  //***************** Koniec nahratia parametrov hraca1 do game.txt *********************
  
  cout<<endl<<"Udaje boli nahrate do suboru "<<subor_vstup_vystup<<endl;
  //************* Koniec nahratia udajov do suboru game.txt *******************	
  }
  
  cout<<endl<<"Koniec hry."<<endl;
  cin.get();
  return 0;
}


bool hraLuckyHit(class TPlayer &player1, class TPlayer &player2)  //funkcia na samotnu hru, vracia priznak bool, ak exportovat udaje
{
	string prikaz;
	string stav_hry = "PLAY";
	bool prve_uhadnutie_hrac1 = true;
	bool prve_uhadnutie_hrac2 = true;
	bool hrac1_uhadol = false;
	bool hrac2_uhadol = false;
	int hrac1_cislo;
	int hrac2_cislo;
	int posledny_prvok;
	bool priznak_exportu = true;  	//urci, ci je potrebne exportovat udaje hry do game.txt
	int ciselnik_textu=0;			//urci, co vypise po vymazani konzoloveho okna
	
	system("cls");					//vymazanie konzoloveho okna
	if(player1.pocet_zivotov > player2.pocet_zivotov) hrac2_uhadol=true; //zacna ako prvy hrac 2
	
	
	while(stav_hry == "PLAY")
	{
	  //************************ Hadania hraca 1 ******************************
	  if(hrac2_uhadol == false)	
	  {
	  	cout<<endl<<player1.meno_hraca<<" - pocet zivotov: "<<player1.pocet_zivotov<<", pocet prvkov: "<<player1.vratPocet()<<endl;
		cout<<player2.meno_hraca<<" - pocet zivotov: "<<player2.pocet_zivotov<<", pocet prvkov: "<<player2.vratPocet()<<endl;
		cout<<"Cislo hada hrac "<<player1.meno_hraca<<endl;
		cout<<"Zadaj cislo alebo EXIT pre ukoncenie hry: ";
		cin>>stav_hry;
		if(stav_hry == "EXIT")
		{
			cout<<endl<<"Hru ukoncil hrac "<<player1.meno_hraca<<endl;
			priznak_exportu=true;
		}
		else
		{
			
			istringstream(stav_hry) >> hrac1_cislo;	//konverzia premennej typu string na int
			stav_hry = "PLAY";
			if(hrac1_cislo == player2.vratHodnotuZasobnika(player2.vratPocet()-1))  //porovna na posledny prvok v zasobniku a rovna sa
			{
				posledny_prvok=player2.vratPocet()-1;
				player2.ulozZasobnikPocet(posledny_prvok);			//vymaze posledny prvok zo zasobnika hraca 2
				if(prve_uhadnutie_hrac1 == true)					//uhadnutie prvku na prvy krat
				{
					cout<<endl<<"Uhadol si cislo na prvy krat, pripocita dva zivoty"<<endl;
					ciselnik_textu=1;
					player1.pocet_zivotov=player1.pocet_zivotov+2;	//pripocita dva zivoty
					hrac1_uhadol=true;
					prve_uhadnutie_hrac1=true;
				}
				else
				{
					cout<<endl<<"Uhadol si cislo, pripocita jeden zivot"<<endl;
					ciselnik_textu=2;
					player1.pocet_zivotov=player1.pocet_zivotov+1;	//pripocita jeden zivot
					hrac1_uhadol=true;
					prve_uhadnutie_hrac1=true;
				}
				
				if(player2.vratPocet() == 0)			//hrac 2 nema ziadny prvok v zasobníku
				{
					cout<<"Hrac "<<player2.meno_hraca<<" nema ziadny prvok v zasobniku, vyhrava hrac "<<player1.meno_hraca<<endl;
					ciselnik_textu=3;
					priznak_exportu=false;
					stav_hry = "EXIT";
				}
			}
			else													//neuhadol
			{
				cout<<endl<<"Neuhadol si cislo, odpocita jeden zivot"<<endl;
				ciselnik_textu=4;
				player1.pocet_zivotov=player1.pocet_zivotov-1;		//odpocita jeden zivot
				hrac1_uhadol=false;
				prve_uhadnutie_hrac1=false;
				
				if(player1.pocet_zivotov == 0)		//hrac 1 nema ziadny zivot, ukoncuje hru
				{
					cout<<"Hrac "<<player1.meno_hraca<<" nema ziadny zivot, vyhrava hrac "<<player2.meno_hraca<<endl;
					ciselnik_textu=5;
					priznak_exportu=false;
					stav_hry = "EXIT";
				}
			}
		}
			system("cls");					//vymazanie konzoloveho okna
			if(ciselnik_textu == 1) cout<<endl<<"Uhadol si cislo na prvy krat, pripocita dva zivoty"<<endl<<endl;
			if(ciselnik_textu == 2) cout<<endl<<"Uhadol si cislo, pripocita jeden zivot"<<endl;
			if(ciselnik_textu == 3) cout<<"Hrac "<<player2.meno_hraca<<" nema ziadny prvok v zasobniku, vyhrava hrac "<<player1.meno_hraca<<endl;
			if(ciselnik_textu == 4) cout<<endl<<"Neuhadol si cislo, odpocita jeden zivot"<<endl;
			if(ciselnik_textu == 5) cout<<"Hrac "<<player1.meno_hraca<<" nema ziadny zivot, vyhrava hrac "<<player2.meno_hraca<<endl;
			cin.get();
	  }
	  //************************ Koniec hadania hraca 1 ***********************
	
	  //************************ Hadania hraca 2 ******************************	
	  if(hrac1_uhadol == false && stav_hry == "PLAY")	
	  {
	  	cout<<endl<<player1.meno_hraca<<" - pocet zivotov: "<<player1.pocet_zivotov<<", pocet prvkov: "<<player1.vratPocet()<<endl;
		cout<<player2.meno_hraca<<" - pocet zivotov: "<<player2.pocet_zivotov<<", pocet prvkov: "<<player2.vratPocet()<<endl;
		cout<<"Cislo hada hrac "<<player2.meno_hraca<<endl;
		cout<<"Zadaj cislo alebo EXIT pre ukoncenie hry: ";
		cin>>stav_hry;
		if(stav_hry == "EXIT")
		{
			cout<<endl<<"Hru ukoncil hrac "<<player2.meno_hraca<<endl;
			priznak_exportu=true;
		}
		else
		{
			
			istringstream(stav_hry) >> hrac2_cislo;	//konverzia premennej typu string na int
			stav_hry = "PLAY";
			if(hrac2_cislo == player1.vratHodnotuZasobnika(player1.vratPocet()-1))  //porovna na posledny prvok v zasobniku
			{
				posledny_prvok=player1.vratPocet()-1;
				player1.ulozZasobnikPocet(posledny_prvok);			//vymaze posledny prvok zo zasobnika hraca 1
				if(prve_uhadnutie_hrac2 == true)					//uhadnutie prvku na prvy krat
				{
					cout<<endl<<"Uhadol si cislo na prvy krat, pripocita dva zivoty"<<endl;
					ciselnik_textu=6;
					player2.pocet_zivotov=player2.pocet_zivotov+2;	//pripocita dva zivoty
					hrac2_uhadol=true;
					prve_uhadnutie_hrac2=true;
				}
				else
				{
					cout<<endl<<"Uhadol si cislo, pripocita jeden zivot"<<endl;
					ciselnik_textu=7;
					player2.pocet_zivotov=player2.pocet_zivotov+1;	//pripocita jeden zivot
					hrac2_uhadol=true;
					prve_uhadnutie_hrac2=true;
				}
				
				if(player1.vratPocet() == 0)			//hrac 1 nema ziadny prvok v zasobníku
				{
					cout<<"Hrac "<<player1.meno_hraca<<" nema ziadny prvok v zasobniku, vyhrava hrac "<<player2.meno_hraca<<endl;
					ciselnik_textu=8;
					priznak_exportu=false;
				}
			}
			else													//neuhadol
			{
				cout<<endl<<"Neuhadol si cislo, odpocita jeden zivot"<<endl;
				ciselnik_textu=9;
				player2.pocet_zivotov=player2.pocet_zivotov-1;		//odpocita jeden zivot
				hrac2_uhadol=false;
				prve_uhadnutie_hrac2=false;
				
				if(player2.pocet_zivotov == 0)		//hrac 2 nema ziadny zivot, ukoncuje hru
				{
					cout<<"Hrac "<<player2.meno_hraca<<" nema ziadny zivot, vyhrava hrac "<<player1.meno_hraca<<endl;
					ciselnik_textu=10;
					priznak_exportu=false;
					stav_hry = "EXIT";
				}
			}
		}
			system("cls");					//vymazanie konzoloveho okna
			if(ciselnik_textu == 6) cout<<endl<<"Uhadol si cislo na prvy krat, pripocita dva zivoty"<<endl<<endl;
			if(ciselnik_textu == 7) cout<<endl<<"Uhadol si cislo, pripocita jeden zivot"<<endl;
			if(ciselnik_textu == 8) cout<<"Hrac "<<player1.meno_hraca<<" nema ziadny prvok v zasobniku, vyhrava hrac "<<player2.meno_hraca<<endl;
			if(ciselnik_textu == 9) cout<<endl<<"Neuhadol si cislo, odpocita jeden zivot"<<endl;
			if(ciselnik_textu == 10) cout<<"Hrac "<<player2.meno_hraca<<" nema ziadny zivot, vyhrava hrac "<<player1.meno_hraca<<endl;
			cin.get();
	  }
	  //************************ Koniec hadania hraca 2 ***********************
		
		
	}  //koniec prikazu while
	if(player1.pocet_zivotov == 0 || player2.pocet_zivotov == 0 || player1.vratPocet() == 0 || player2.vratPocet() == 0 ) priznak_exportu=false;
	else priznak_exportu=true;
	return priznak_exportu;
}


string intToString(int cislo) 		//funkcia konverzie int na string
{
    string cisloString;
    bool negative = false;
    
    if (cislo < 0) {
        negative = true;
        cislo = -cislo;
    }
    
    do {
        cisloString.insert(cisloString.begin(), '0' + cislo % 10);
        cislo /= 10;
    } while (cislo != 0);
    
    if (negative)
        cisloString.insert(cisloString.begin(), '-');
    
    return cisloString;
}

int charArrayToInt(char arr[], int size)    //konverzia pola char na int
{
    int result = 0;
    int i = 0;
    // Iterujte cez pole znakov, kým nedosiahnete ukonèujúci znak '\0'
    while (i<size) 
	{
        result = result * 10 + (arr[i] - '0'); // Prevedenie znaku na èíslicu
        ++i;
    }
    return result;
}

int skopiruj_riadok(char* buffer, int start, int end, char* novy)  //funkcia skopiruje od pozicie start do pozicie end znaky z buffer do novy a vrati pocet znakov v riadku
{
 int i=0;
 do{ novy[i]=buffer[start];
        start++;
        i++; 
      } while (start<=end);  
  return i;
}



  
