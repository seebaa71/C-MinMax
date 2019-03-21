#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<ctime>

using namespace std;




void Initialize(char board[3][3])
{
  for (int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
      board[i][j]=' ';
    }
  }
}
bool Canyoumove(char board[3][3])
{
  for(int i=0;i<3;i++)
  {
    for (int j=0; j<3 ;j ++)
    {
      if(board[i][j]==' ')
      {
        return true;
      }
    }
  }
  return false;
}
void Show(char board[3][3])
{
  cout<<" AKTUALNY WIDOK PLANSZY DO GRY:  "<<endl;
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
        cout<<"|"<<"     "<<board[i][j];
    }
    cout<<"|";
    cout<<endl;
    cout<<"-----------------------"<<endl;
  }
}
int Gamestatus(char board[3][3])
{

  int sensorX=0;
  int sensorO=0;

  for(int i=0;i<3;i++)
  {
    sensorX=0;
    sensorO=0;
    for(int j=0;j<3;j++)
  {

    if(board[i][j]=='X')
    {
      sensorX++;
    }
    else if(board[i][j]=='O')
    {
      sensorO++;
    }
    if(sensorX==3)
    {
      return 10;
    }
    else if(sensorO==3)
    {
      return -10;
    }
  }
}
  sensorX=0;
  sensorO=0;

  for(int i=0;i<3;i++)
  {
  sensorX=0;
  sensorO=0;
    for(int j=0;j<3;j++)
    {
      if(board[j][i]=='X')
      {
        sensorX++;
      }
      else if(board[j][i]=='O')
      {
        sensorO++;
      }
      if(sensorX==3)
      {
        return 10;
      }
      else if(sensorO==3)
      {
        return -10;
      }
    }
  }
  sensorX=0;
  sensorO=0;
  // Sprawdzenie przekatnych
  if(board[0][0]=='X' && board[1][1]=='X' && board[2][2]=='X'|| board[0][2]=='X' && board[1][1]=='X' && board[2][0]=='X')
  {
    return 10;
  }
  if(board[0][0]=='O' && board[1][1]=='O' && board[2][2]=='O'|| board[0][2]=='O' && board[1][1]=='O' && board[2][0]=='O')
  {
    return -10;
  }
  return 0;


}

int MinMax(char board[3][3], int glebokosc, bool isMax)
{
  int score=Gamestatus(board);
    if(score == 10)
    {
      return score;

    }
    if (score == -10)
    {
      return score;
    }

    if(Canyoumove(board)== false)
    {
      return 0;
    }
      if(isMax)
      {
        int best = -1000;
          for (int i=0; i<3 ;i++)
          for(int j=0;j<3; j++)
          {
            if(board[i][j]==' ')
            {
              board[i][j]='X';
              best=max(best,MinMax(board,glebokosc+1,!isMax));
              board[i][j]=' ';
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
      if(board[i][j]==' ')
      {
        board[i][j]='O';
        best=min(best,MinMax(board,glebokosc+1,!isMax));
        board[i][j]=' ';
      }
    }
  }
  return best;
}

      }


void ruszaKomputer(char board[3][3])
  {
    int bestVal= -1000;
    int column=-1;
    int line=-1;
      for(int i=0;i<3;i++)
      {
        for(int j=0;j<3;j++)
        {
          if(board[i][j]==' ')
          {
            board[i][j]='X';
            int moveVal=MinMax(board,0,false);
            board[i][j]=' ';
            if(moveVal > bestVal)
            {
              column=i;
              line=j;
              bestVal=moveVal;
            }
          }
        }
      }
    board[column][line]='X';
  }

int Checkfieldstatus(char board[3][3],int field)
{
  if(field >= 0 && field <= 3)
  {
    if(field==1 && board[0][0]==' ' || field==2 && board[0][1]==' ' || field==3 &&board[0][2]==' ')
    {
      return 1;
    }
    else
    return -1;
  }
  if(field>3 && field <= 6)
  {
    if(field==4 && board[1][0]==' ' || field==5 && board[1][1]==' ' || field==6 &&board[1][2]==' ')
    {
      return 1;
    }
    else
    return -1;
  }
  if(field>=7 && field <= 9)
  {
    if(field==7 && board[2][0]==' ' || field==8 && board[2][1]==' ' || field==9 &&board[2][2]==' ')
    {
      return 1;
    }

  }
  else
  return -1;

}


void Enter(char board[3][3],char Sign)
{
  int field=1;
  int motion=0;
  cout<<"WYBIERZ field OD 1-9!!!!"<<endl;
  cout<<"                       "<<endl;

while(Sign != 'k' &&motion!=9)
  {
    motion++;
    cout<<"-------------------------------------"<<endl;
    cout<<"Kolej na kolejnego gracza!"<<endl;
      if(Sign=='O' )
      {
        Sign='X';
        cout<<"Rusza komputer"<<endl;
        cout<<"Wykonano "<<motion<<" motionow!"<<endl;
        ruszaKomputer(board);
        Show(board);
        if(Gamestatus(board)==10)
        {
          cout<<"PRZEGRALES!!!"<<endl;
          break;
        }
        if(Gamestatus(board)==-10)
        {
          cout<<"WYGRALES!!!"<<endl;
          break;
        }

       continue;
      }
     else if (Sign=='X')
      {
        Sign='O';
        cout<<"Enter field: "<<endl;
        cin>>field;
          while(Checkfieldstatus(board,field)==-1)
          {
            cout<<"field zajete!!! Sprobuj jeszcze raz: "<<endl;
            cin>>field;
          }
          cout<<"Wykonano "<<motion<<" motionow!"<<endl;
        }
      if(motion==9 && Gamestatus(board)==0)
      {
        cout<<"PADL REMIS!"<<endl;
        Show(board);
        break;
      }

    switch(field)
    {
    case 1:
     board[0][0]=Sign;
     Show(board);
      break;
    case 2:
     board[0][1]=Sign;
     Show(board);
    break;
    case 3:
     board[0][2]=Sign;
     Show(board);
    break;
    case 4:
     board[1][0]=Sign;
     Show(board);
    break;
    case 5:
     board[1][1]=Sign;
     Show(board);
    break;
    case 6:
     board[1][2]=Sign;
     Show(board);
    break;
    case 7:
     board[2][0]=Sign;
     Show(board);
    break;
    case 8:
     board[2][1]=Sign;
     Show(board);
    break;
    case 9:
     board[2][2]=Sign;
     Show(board);
    break;
    default:
    cout<<"Niestety to nie ten Sign"<<endl;
    motion--;
    break;
  }


}
}



int main()
{
  char board[3][3];
  char Sign;
  //int wymiar;



cout<<"GRA KOLKO I KRZYZYK!!!"<<endl;
cout<<"Jaki wymiar ma miec board 3x3...NxN ???"<<endl;
//cout<<"Podaj wymiar : "<<endl;
//cin>>wymiar;
//char board[wymiar][wymiar];
cout<<"Zaczyna gracz? Tak(T) lub Nie(N)"<<endl;
cin>>Sign;
/*
while(Sign == 'T' || Sign == 't' || Sign == 'N' || Sign == 'n')
{
  cout<<"JESTEM TUTAJ: "<<Sign<<endl;
  cout<<"Enterono zly Sign! Sprobuj jeszcze raz: "<<endl;
  cin>>Sign;
}
*/
  if(Sign == 'T' || Sign == 't')
    {
      Sign='X';
      Initialize(board);
      Enter(board,Sign);
    }
    else if(Sign == 'N' || Sign== 'n')
    {
      Sign='O';
      Initialize(board);
      Enter(board,Sign);
    }
return 0;
}
