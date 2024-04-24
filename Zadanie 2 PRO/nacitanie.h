//** Nacitanie vstupneho suboru do pola typu struct riadky_txt **
      // ziskanie poctu znakov suboru vstup:
      vstup.seekg(0,vstup.end);    //seekg nastavuje poziciu nasledujuceho znaku premennej vstup
      long size=vstup.tellg();    //tellg vracia poziciu sucasneho znaku premennej vstup
      vstup.seekg(0);            //seekg nastavi na zaciatok

      char* buffer=new char[size];        //smernik na pole s nazvom buffer a poctom size
      vstup.read(buffer,size);          //read nacita obsah subor2 do pola buffer


      //ziskanie poctu riadkov suboru vstup, ktory je nacitany v buffer
      for(i=0;i<size;i++) 
      { 
        if((int)buffer[i]==13) pocet_riadkov++;    //13 v asci je enter
      }

    struct riadky_txt* pole = new riadky_txt[pocet_riadkov];     //Definuje smernik na pole typu struct riadky_txt s poctom pocet_riadkov
    int pocet=0;
       //nacitanie jednotlivych riadkov do zoznamu:
      while (j<size)
      {

        while ((int)buffer[j]!=13){ //13 v asci je enter

        if(pom==0)
        {
          char* pomocny_riadok = new char[81];
          pocet_znakov_riadok=skopiruj_riadok(buffer, j, pomocny_riadok);

          //naplnenia stukury zoznam:
          strcpy((pole+pocet)->riadok,pomocny_riadok);
          (pole+pocet)->pocet_riadok = pocet_znakov_riadok;

          pocet++;
          delete[] pomocny_riadok;
          pom=1;
        }
    i++;
    j++;

    }
j=j+2;
      pom=0;
  }
  //** Koniec nacitania do pole **
  pocet_riadkov = pocet;    //zabezpeci, ze do poctu_riadkov nebudu zahrnute prazdne riadky
  delete[] buffer;
  return pole;        //vrati smernik na vytvorene pole typu struct riadky_txt

}

void vypis_txt(const riadky_txt pole, const int pocet_riadkov)
{
    int k=0;
      cout<<"Pocet riadkov v subore: "<<pocet_riadkov<<endl;

      for(int k=0; k<pocet_riadkov; k++) 
          cout << k+1 << ". (" << (pole+k)->pocet_riadok << ") " << (pole+k)->riadok << endl;
}

#endif