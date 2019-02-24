#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<ctime>

using namespace std;




void Inicjuj(char plansza[3][3])
{
  for (int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
      plansza[i][j]=' ';
    }
  }
}
bool Czymoznaruszyc(char plansza[3][3])
{
  for(int i=0;i<3;i++)
  {
    for (int j=0; j<3 ;j ++)
    {
      if(plansza[i][j]==' ')
      {
        return true;
      }
    }
  }
  return false;
}
void Pokaz(char plansza[3][3])
{
  cout<<" AKTUALNY WIDOK PLANSZY DO GRY:  "<<endl;
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
        cout<<"|"<<"     "<<plansza[i][j];
    }
    cout<<"|";
    cout<<endl;
    cout<<"-----------------------"<<endl;
  }
}
int Stangry(char plansza[3][3])
{

  int czujkaX=0;
  int czujkaO=0;

  for(int i=0;i<3;i++)
  {
    czujkaX=0;
    czujkaO=0;
    for(int j=0;j<3;j++)
  {

    if(plansza[i][j]=='X')
    {
      czujkaX++;
    }
    else if(plansza[i][j]=='O')
    {
      czujkaO++;
    }
    if(czujkaX==3)
    {
      return 10;
    }
    else if(czujkaO==3)
    {
      return -10;
    }
  }
}
  czujkaX=0;
  czujkaO=0;

  for(int i=0;i<3;i++)
  {
  czujkaX=0;
  czujkaO=0;
    for(int j=0;j<3;j++)
    {
      if(plansza[j][i]=='X')
      {
        czujkaX++;
      }
      else if(plansza[j][i]=='O')
      {
        czujkaO++;
      }
      if(czujkaX==3)
      {
        return 10;
      }
      else if(czujkaO==3)
      {
        return -10;
      }
    }
  }
  czujkaX=0;
  czujkaO=0;
  // Sprawdzenie przekatnych
  if(plansza[0][0]=='X' && plansza[1][1]=='X' && plansza[2][2]=='X'|| plansza[0][2]=='X' && plansza[1][1]=='X' && plansza[2][0]=='X')
  {
    return 10;
  }
  if(plansza[0][0]=='O' && plansza[1][1]=='O' && plansza[2][2]=='O'|| plansza[0][2]=='O' && plansza[1][1]=='O' && plansza[2][0]=='O')
  {
    return -10;
  }
  return 0;


}

int MinMax(char plansza[3][3], int glebokosc, bool isMax)
{
  int score=Stangry(plansza);
    if(score == 10)
    {
      return score;

    }
    if (score == -10)
    {
      return score;
    }

    if(Czymoznaruszyc(plansza)== false)
    {
      return 0;
    }
      if(isMax)
      {
        int best = -1000;
          for (int i=0; i<3 ;i++)
          for(int j=0;j<3; j++)
          {
            if(plansza[i][j]==' ')
            {
              plansza[i][j]='X';
              best=max(best,MinMax(plansza,glebokosc+1,!isMax));
              plansza[i][j]=' ';
            }

          }
          return best;

}

else
{
  int best= 1000;
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
      if(plansza[i][j]==' ')
      {
        plansza[i][j]='O';
        best=min(best,MinMax(plansza,glebokosc+1,!isMax));
        plansza[i][j]=' ';
      }
    }
  }
  return best;
}

      }


void ruszaKomputer(char plansza[3][3])
  {
    int bestVal= -1000;
    int kolumny=-1;
    int wiersze=-1;
      for(int i=0;i<3;i++)
      {
        for(int j=0;j<3;j++)
        {
          if(plansza[i][j]==' ')
          {
            plansza[i][j]='X';
            int moveVal=MinMax(plansza,0,false);
            plansza[i][j]=' ';
            if(moveVal > bestVal)
            {
              kolumny=i;
              wiersze=j;
              bestVal=moveVal;
            }
          }
        }
      }
    plansza[kolumny][wiersze]='X';
  }

int SprawdzDostepnoscPola(char plansza[3][3],int pole)
{
  if(pole >= 0 && pole <= 3)
  {
    if(pole==1 && plansza[0][0]==' ' || pole==2 && plansza[0][1]==' ' || pole==3 &&plansza[0][2]==' ')
    {
      return 1;
    }
    else
    return -1;
  }
  if(pole>3 && pole <= 6)
  {
    if(pole==4 && plansza[1][0]==' ' || pole==5 && plansza[1][1]==' ' || pole==6 &&plansza[1][2]==' ')
    {
      return 1;
    }
    else
    return -1;
  }
  if(pole>=7 && pole <= 9)
  {
    if(pole==7 && plansza[2][0]==' ' || pole==8 && plansza[2][1]==' ' || pole==9 &&plansza[2][2]==' ')
    {
      return 1;
    }

  }
  else
  return -1;

}


void Wprowadz(char plansza[3][3],char znak)
{
  int pole=1;
  int ruch=0;
  cout<<"WYBIERZ POLE OD 1-9!!!!"<<endl;
  cout<<"                       "<<endl;

while(znak != 'k' &&ruch!=9)
  {
    ruch++;
    cout<<"-------------------------------------"<<endl;
    cout<<"Kolej na kolejnego gracza!"<<endl;
      if(znak=='O' )
      {
        znak='X';
        cout<<"Rusza komputer"<<endl;
        cout<<"Wykonano "<<ruch<<" ruchow!"<<endl;
        ruszaKomputer(plansza);
        Pokaz(plansza);
        if(Stangry(plansza)==10)
        {
          cout<<"PRZEGRALES!!!"<<endl;
          break;
        }
        if(Stangry(plansza)==-10)
        {
          cout<<"WYGRALES!!!"<<endl;
          break;
        }

       continue;
      }
     else if (znak=='X')
      {
        znak='O';
        cout<<"Wprowadz pole: "<<endl;
        cin>>pole;
          while(SprawdzDostepnoscPola(plansza,pole)==-1)
          {
            cout<<"Pole zajete!!! Sprobuj jeszcze raz: "<<endl;
            cin>>pole;
          }
          cout<<"Wykonano "<<ruch<<" ruchow!"<<endl;
        }
      if(ruch==9 && Stangry(plansza)==0)
      {
        cout<<"PADL REMIS!"<<endl;
        Pokaz(plansza);
        break;
      }

    switch(pole)
    {
    case 1:
     plansza[0][0]=znak;
     Pokaz(plansza);
      break;
    case 2:
     plansza[0][1]=znak;
     Pokaz(plansza);
    break;
    case 3:
     plansza[0][2]=znak;
     Pokaz(plansza);
    break;
    case 4:
     plansza[1][0]=znak;
     Pokaz(plansza);
    break;
    case 5:
     plansza[1][1]=znak;
     Pokaz(plansza);
    break;
    case 6:
     plansza[1][2]=znak;
     Pokaz(plansza);
    break;
    case 7:
     plansza[2][0]=znak;
     Pokaz(plansza);
    break;
    case 8:
     plansza[2][1]=znak;
     Pokaz(plansza);
    break;
    case 9:
     plansza[2][2]=znak;
     Pokaz(plansza);
    break;
    default:
    cout<<"Niestety to nie ten znak"<<endl;
    ruch--;
    break;
  }


}
}



int main()
{
  char plansza[3][3];
  char znak;
  //int wymiar;



cout<<"GRA KOLKO I KRZYZYK!!!"<<endl;
cout<<"Jaki wymiar ma miec plansza 3x3...NxN ???"<<endl;
//cout<<"Podaj wymiar : "<<endl;
//cin>>wymiar;
//char plansza[wymiar][wymiar];
cout<<"Zaczyna gracz? Tak(T) lub Nie(N)"<<endl;
cin>>znak;
/*
while(znak == 'T' || znak == 't' || znak == 'N' || znak == 'n')
{
  cout<<"JESTEM TUTAJ: "<<znak<<endl;
  cout<<"Wprowadzono zly znak! Sprobuj jeszcze raz: "<<endl;
  cin>>znak;
}
*/
  if(znak == 'T' || znak == 't')
    {
      znak='X';
      Inicjuj(plansza);
      Wprowadz(plansza,znak);
    }
    else if(znak == 'N' || znak== 'n')
    {
      znak='O';
      Inicjuj(plansza);
      Wprowadz(plansza,znak);
    }
return 0;
}
