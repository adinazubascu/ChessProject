#include<stdio.h>
#include <math.h>
#include <stdlib.h>
#include<ctype.h>



void printBoard(char a[][9], int n)
{
  int i=0,j=0;

  for(i=0;i<n;i++)
  {

     for(j=0;j<n;j++)
    {  
       if(j==0)
       { if(i==0)
          printf("8 ");
           else
          printf("%d ",a[i][j]);
      }
    else
     printf("%c ",a[i][j]);
    }
  putchar('\n');
}

}

//initialises the board with the corresponding pieces

void SetBoard(char a[][9],int n)
{
       for(int i=1;i<n;i++)
    {
          a[1][i]='I';
          a[n-3][i]='i';
    }
  for(int i=2;i<6;i++)
   for(int j=1;j<9;j++)
        a[i][j]='.';
  a[0][1]='T'; a[0][8]='T';
  a[0][2]='C'; a[0][7]='C';
  a[0][3]='N'; a[0][6]='N';
  a[0][4]='M'; a[0][5]='F';
  a[7][1]='t'; a[7][8]='t';
  a[7][2]='c'; a[7][7]='c';
  a[7][3]='n'; a[7][6]='n';
  a[7][4]='m'; a[7][5]='f';

}
void getmove(char *pos,int *x,int *y)
{
   
    *y=pos[0]-'a'+1;
    *x=8-(pos[1]-'0');

}

//moves the piece by changing the value of the given position in the matrix and replacing the old position with '.'
//cases that have yet to be handled: the new position has a opponent piece and the move given is part of the procces of generating the best move(the move has to be restored to the initial scenario)
void doMove(int xi, int yi, int xf, int yf, char a[][9])
{
  a[xf][yf]=a[xi][yi];
  a[xi][yi]='.';
}


//checking the valid moves for each piece



int checkKing(char *st, char *end , char a[][9])
{
     int x1,x2,y1,y2;
    getmove(st,&y1,&x1);
    getmove(end,&y2,&x2);
    if(abs(x1-x2)<=1 && abs(y1-y2)<=1)
      return 1;
    else 
      return 0;
}
int checkBishop(char *st, char *end , char a[][9])
{
     int x1,x2,y1,y2;
    getmove(st,&y1,&x1);
    getmove(end,&y2,&x2);
    if(abs(x1-x2)==abs(y1-y2))
     return 1;
    else 
     return 0;

}
int checkRookMoves(char *st,char *end , char a[][9])
{
    int x1,x2,y1,y2;
    getmove(st,&y1,&x1);
    getmove(end,&y2,&x2); 
    if(x1==x2||y1==y2)
     return 1;
    else 
     return 0;

}
int checkQueen(char *st, char *end, char a[][9])
{
    int x1,x2,y1,y2;
    getmove(st,&y1,&x1);
    getmove(end,&y2,&x2);
    if((abs(x1-x2)==abs(y1-y2))|| x1==x2 || y1==y2)
      return 1;
    else 
      return 0;

}
int checkKnight(char *st , char *end, char a[][9])
{
  int x1,x2,y1,y2;
    getmove(st,&y1,&x1);
    getmove(end,&y2,&x2);
  if((abs(x1-x2) == 1 && abs(y1-y2)==2) || (abs(x1-x2) == 2 && abs(y1-y2)==1))
    return 1;
  else
   return 0;
}
int checkPawn(char *st, char *end , char a[][9])
{
    int x1,x2,y1,y2;
    getmove(st,&y1,&x1);
    getmove(end,&y2,&x2);
    if(a[y1][x1]=='i')
       { if(y1==6)
       {
          
        if((y1-y2==1 ||y1-y2==2) && x1==x2)
         return 1;
        else
         return 0;
       }
        
        if(y1-y2==1 && x1==x2)
         return 1;
        else
         return 0;
       }
    else 
    if(a[y1][x1]=='I')
      { if(y1==1)
      {
        if((y2-y1==1 || y2-y1==2) && x1==x2)
         return 1;
        else
        return 0;
      }
        if(y2-y1==1 && x1==x2)
         return 1;
        else
        return 0;
      }
      return 0;
}
int checkInside(int x,int y,char a[][9])
{
     
  if(x<0 || x>7 || y<1 || y>8)
     return 0;
  else
    return 1;

}

//checks if in the given position there is a piece of your own 

int checkFriendly( int x1, int y1,int x2, int y2, char a[][9])
{  
    
    if(a[x2][y2]=='.')
       return 1;
    else
    {
      if(isupper(a[x1][y1])==isupper(a[x2][y2]))
        return 0;
       else 
         return 1;
    } 


           

}
//a function that calls all the checking procedures for a move

int validation(char *st, char *end, char a[][9])
{

    int x1,x2,y1,y2;
    getmove(st,&x1,&y1);
    getmove(end,&x2,&y2);
    if(!checkInside(x2,y2,a))
    {
      printf("move outside the board\n");
      return 0;
    }
    if(checkFriendly(x1,y1,x2,y2,a)==0)
    {
      printf("move slot occupied\n");
      return 0;
    }
      
    
   if(tolower(a[x1][y1])=='i')
      {
        if(checkPawn(st,end,a))
         {
          printf("valid move of pawn\n");
         return 1;
         }
      else 
      {
         printf("invalid move, try again of pawn\n");
         return 0;
      }
     }
   if(tolower(a[x1][y1])=='t') 
     {
         if(checkRookMoves(st,end,a)){
         printf("valid move of rook\n");
         return 1;
         }
      else{ 
         printf("invalid move, try again of rook\n");
         return 0;
      }
     }
      
   if(tolower(a[x1][y1])=='c')
    {
     if(checkKnight(st,end,a))
        { 
         printf("valid move of knight\n");
         return 1;
        }
      else{ 
         printf("invalid move, try again of knight\n");
         return 0;
      }
    }
   if(tolower(a[x1][y1])=='n')
    {
     if(checkBishop(st,end,a))
         printf("valid move of bishop\n");
      else 
         printf("invalid move, try again of bishop\n");
    }
   if(tolower(a[x1][y1])=='m')
    {
     if(checkKing(st,end,a))
         printf("valid move of king\n");
      else 
         printf("invalid move, try again of king\n");
    }
   if(tolower(a[x1][y1])=='f')
    {
         if(checkQueen(st,end,a))
         printf("valid move of queen\n");
      else 
         printf("invalid move, try again of queen\n");
    }

 }

//functions to generate all the possible moves for all the pieces(returns the number of moves as the mobility parameter of calculating the most efficient move)

int movesRook(int i, int j, char a[][9])
{
  char xf,yf;
  int x_int=i ,y_int=j,int1=1,int2=1,int3=1,int4=1,nrMoves=0;
    //printf("possible moves:\n");
             
       
           x_int=i+int1;
           while(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
           {
               yf=j+'a'-1;
               xf=8-x_int +'0';
               //printf(%c%c\n",xf,yf);
               nrMoves++;
               int1++;
               x_int++;
        
           }
            y_int=j+int2;
            while(checkFriendly(i,j,i,y_int,a)!=0 && checkInside(i,y_int,a)!=0)
           {
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              nrMoves++;
              int2++;
             y_int++;
           }
           x_int=i-int3;
           while(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
           {
               yf=y_int+'a'-1;
               xf=8-x_int +'0';
              //printf(%c%c\n",xf,yf);
               nrMoves++;
                int3++;
               x_int--;
        
            }
            y_int=j-int4;
          while(checkFriendly(i,j,i,y_int,a)!=0 && checkInside(i,y_int,a)!=0)
           {

              yf=y_int+'a'-1;
              xf=8-x_int +'0';
              nrMoves++;
            //printf(%c%c\n",xf,yf);
             int4++;
              y_int--;

           }
         if(nrMoves==0)
          {
         //printf("no moves\n");
           return 0;
          }
          else 
            return nrMoves;
}
int movesBishop(int i, int j, char a[][9])
{
  char xf,yf;
  int x_int=i ,y_int=j,int1=1,int2=1,int3=1,int4=1,nrMoves=0;
    //printf("possible moves:\n");
            x_int=x_int+int1;
         y_int=y_int+int1;
         while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
          {
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
        //   printf("%c%c\n",xf,yf);
             nrMoves++;
           int1++;
            x_int++;
            y_int++;
        
          }
          x_int=i-int2;
          y_int=j-int2;
          while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
          {
             yf=y_int+'a'-1;
             xf=8-x_int +'0';
            // printf("%c%c\n",xf,yf);
              nrMoves++;
             int2++;
             x_int--;
             y_int--;

           }
         x_int=i-int3;
         y_int=j+int3;
         while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
         {
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
         // printf("%c%c\n",xf,yf);
             nrMoves++;
            int3++;
            x_int--;
            y_int++;
        
          }
          x_int=i+int4;
          y_int=j-int4;
          while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
           {

              yf=y_int+'a'-1;
              xf=8-x_int +'0';
              nrMoves++;
           // printf("%c%c\n",xf,yf);
             int4++;
             x_int++;
             y_int--;

          }

         if(nrMoves==0)
          {
         //printf("no moves\n");
           return 0;
          }
          else 
             return nrMoves;
      
             
}
int movesQueen(int i, int j, char a[][9])
{
  char xf,yf;
  int x_int=i ,y_int=j,int1=1,int2=1,int3=1,int4=1,nrMoves=0;
    //printf("possible moves:\n");
    nrMoves=0;
       
         x_int=i+int1;
         while(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
          {
            yf=j+'a'-1;
            xf=8-x_int +'0';
           //printf(%c%c\n",xf,yf);
             nrMoves++;
           int1++;
            x_int++;

}
          y_int=j+int2;
          while(checkFriendly(i,j,i,y_int,a)!=0 && checkInside(i,y_int,a)!=0)
          {
             yf=y_int+'a'-1;
             xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              nrMoves++;
             int2++;
            y_int++;

           }
         x_int=i-int3;
         while(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
         {
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
          //printf(%c%c\n",xf,yf);
             nrMoves++;
            int3++;
           x_int--;
        
          }
          y_int=j-int4;
          while(checkFriendly(i,j,i,y_int,a)!=0 && checkInside(i,y_int,a)!=0)
           {

              yf=y_int+'a'-1;
              xf=8-x_int +'0';
              nrMoves++;
            //printf(%c%c\n",xf,yf);
             int4++;
              y_int--;

          }
           x_int=i+int1;
         y_int=j+int1;
         while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
          {
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
           //printf(%c%c\n",xf,yf);
             nrMoves++;
           int1++;
            x_int++;
            y_int++;
        
          }
          x_int=i-int2;
          y_int=j-int2;
          while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
          {
             yf=y_int+'a'-1;
             xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              nrMoves++;
             int2++;
            x_int--;
            y_int--;

           }
         x_int=i-int3;
         y_int=j+int3;
         while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
         {
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
          //printf(%c%c\n",xf,yf);
             nrMoves++;
            int3++;
           x_int--;
           y_int++;
        
          }
          x_int=i+int4;
          y_int=j-int4;
          while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
           {

              yf=y_int+'a'-1;
              xf=8-x_int +'0';
              nrMoves++;
            //printf(%c%c\n",xf,yf);
             int4++;
             x_int++;
             y_int--;

          }
          if(nrMoves==0)
          {
         // printf("no moves\n");
           return 0;
          }
          else 
          return nrMoves;
      


}
int movesPawn(int i, int j, char a[][9], int *dp, int *ip, int *bp)
{
   char xf,yf;
   int x_int=i ,y_int=j,int1=1,int2=1,int3=1,int4=1,nrMoves=0;
    //printf("possible moves:\n");
         nrMoves=0;
        if(i==1)
        { if(a[i][j]=='I')
         { 
            x_int=i+int1;
            if(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
            {
              if(a[x_int][j]!='.')
              {
                *bp=1;
              }
              else 
             { *bp=0;
               nrMoves++;
               yf=y_int+'a'-1;
               xf=8-x_int +'0';
               //printf(%c%c\n",xf,yf);
             }
              
            }
          
            int1++;
            x_int++;
             if(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0 && a[x_int][j]=='.')
             {
                nrMoves++;
                yf=y_int+'a'-1;
                xf=8-x_int +'0';
                //printf(%c%c\n",xf,yf);
             }
         }

        }
        if(i==6)
        { 
          if(a[i][j]=='i')
        {
            x_int=i-int1;
            if(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
          {
             if(a[x_int][j]!='.')
              {
                *bp=1;
              }
              else 
             {
               *bp=0;
               nrMoves++;
               yf=y_int+'a'-1;
               xf=8-x_int +'0';
               //printf(%c%c\n",xf,yf);
             }
          }
          int1++;
          x_int--;
          if(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0 && a[x_int][j]=='.')
          {
             nrMoves++;
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
          //printf(%c%c\n",xf,yf);
          }
         }
        }
          if(a[i][j]=='i' && i!=6)
          {
            
            x_int--;
            if(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
           {
            if(a[x_int][j]!='.')
              {
                *bp=1;
              }
              else 
             { *bp=0;
             nrMoves++;
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
          //printf(%c%c\n",xf,yf);
             }
           }
          }
          if(a[i][j]=='I' && i!=1)
          {
            x_int++;
            if(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
           {
            if(a[x_int][j]!='.')
              {
                *bp=1;
              }
              else 
             { *bp=0;
             nrMoves++;
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
           //printf(%c%c\n",xf,yf);
             }
              
            }
          }
              if(nrMoves==0)
          {
            if(checkFriendly(i,j,x_int,j,a)==0 && (a[x_int][j]=='i' ||  a[x_int][j]=='I') )
            {
              *dp=1;
            }
            else
            {
             *dp=0;
            }
         // /printf("No Moves\n");
           return 0;
           }
           else 
           return nrMoves;

}
int movesKnight(int i, int j, char a[][9])
{
  
   char xf,yf;
  int x_int=i ,y_int=j,int1=1,int2=1,int3=1,int4=1,nrMoves=0;
    //printf("possible moves:\n");
      
        x_int=x_int+2;
        y_int=y_int+1;
         if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
           //printf(%c%c\n",xf,yf);
              
             }
        y_int=y_int-2;
        if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
            //printf(%c%c\n",xf,yf);
              
             }
      
      
        x_int=x_int-1;
        y_int=y_int-1;
         if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
            //printf(%c%c\n",xf,yf);
              
             }
        y_int=y_int+4;
        if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              
             }
          x_int=x_int-2;
          if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              
             }
            x_int=x_int-1;
            y_int=y_int-1;
             if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              
             }
            y_int=y_int-2;
            if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              
             }
            x_int=x_int+1;
            y_int=y_int-1;
              if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
               
             }

      
           if(nrMoves==0)
           {
                 // // //printf("no moves\n");
                   return 0;
          }
          else 
          return nrMoves;

}
int movesKing(int i, int j, char a[][9])
{  char xf,yf;
  int x_int=i ,y_int=j,int1=1,int2=1,int3=1,int4=1,nrMoves=0;
   //printf("possible moves:\n");
         nrMoves=0;
       x_int++;
       if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
               
             }
       y_int++;
       if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
            //printf(%c%c\n",xf,yf);
               
             }
       x_int--;
       if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
               
              
             }
     x_int--;
     if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              
             }
     y_int--;
     if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              
             
             }
    y_int--;
    if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
            //printf(%c%c\n",xf,yf);
              
             }
    x_int++;
    if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              
             }

    x_int++;
    if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              
             }
    
           if(nrMoves==0)
           { return 0;
           }
           else 
           return nrMoves;
                
}

//the function for calculating each move's efficiency for generating the best move for the opponent(in the gamemode PvC)

float evaluateMove(char a[][9])
{
 // printBoard(a,9);
  float score=0.0;
  int i,j,Rb=0,Rw=0,Nb=0,Nw=0,Bb=0,Bw=0,Qb=0,Qw=0,Kb=0,Kw=0,Pb=0,Pw=0,Mw=0,Mb=0,Dw=0,Db=0,Iw=0,Ib=0,Sb=0,Sw=0;
  int dp=0,ip=0,bp=0;
  for(i=0;i<8;i++)
     for(j=1;j<9;j++)
     {
      char piece;
      piece=a[i][j];
     // printf("we count the moves for piece %c\n",piece);
      switch(piece)
      {
        case 'T':
          Rw++;
          Mw=Mw+movesRook(i,j,a);
          break;
        case 'C':
          Nw++;
          Mw=Mw+movesKnight(i,j,a);
          break;
        case 'N':
          Bw++;
          int nr=movesBishop(i,j,a);
          Mw=Mw+nr;
          //printf("%d",nr);
          break;
        case 'F':
          Qw++;
           nr=movesQueen(i,j,a);
          Mw=Mw+nr;
         // printf("%d\n",nr);
          break;
        case 'M':
          Kw++;
          Mw=Mw+movesKing(i,j,a);
          break;
        case 'I':
          
          Pw++;
           nr=movesPawn(i,j,a,&dp,&ip,&bp);
           Dw=Dw+dp;
           Iw=Iw+ip;
           Sw=Sw+bp;
           Mw=Mw+nr; 
          //printf("%d\n",nr);
          break;
          case 't':
          Rb++;
          Mb=Mb+movesRook(i,j,a);
          break;
        case 'c':
          Nb++;
          Mb=Mb+movesKnight(i,j,a);
          break;
        case 'n':
          Bb++;
          Mb=Mb+movesBishop(i,j,a);
          break;
        case 'f':
          Qb++;
          Mb=Mb+movesQueen(i,j,a);
          break;
        case 'm':
          Kb++;
          Mb=Mb+movesKing(i,j,a);
          break;
        case 'i':
          Pb++;
           
           nr=movesPawn(i,j,a,&dp,&ip,&bp);
           Db=Db+dp;
           Ib=Ib+ip;
           Sb=Sb+bp;
          Mb=Mb+nr;
          
          break;
        default:
         break;
      }
     }
    
   // printf("%d-%d\n",Mw,Mb);
     score=200*(Kw-Kb)+9*(Qw-Qb)+5*(Rw-Rb)+3*(Bw-Bb+Nw-Nb)+1*(Pw-Pb)+0.1*(Mw-Mb)-0.5*(Dw-Db+Iw-Ib+Bw-Bb);
       //  printf("%f is the score\n\n",score);
        return score;
      
     

}
void generateMoves(int i, int j, char a[][9],float *sc,int *ifin, int *jfin)
 {
    float maxScore=-1000.0,score;//we set the score,which will be calculated for each possible move, amd a maxscore for the best possible move
 
    int x_ei=0,y_ei=0,x_ef=0,y_ef=0; //we set the coordinates for the best possible move
  char xf,yf;
  char piece=a[i][j];
    piece=tolower(piece);
    int x_int=i,y_int=j,int1=1,int2=1,int3=1,int4=1,nrMoves=0,aux;
  switch(piece)
  {  
      case 't':
            //printf("possible moves:\n");
            nrMoves=0;

           x_int=i+int1;
           while(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
           {
               yf=j+'a'-1;
               xf=8-x_int +'0';
               // printf("we evaluate move %c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              // printf("%f is the score\n\n",score);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=j;
              }
                nrMoves++;
               int1++;
               x_int++;
          
           }
            y_int=j+int2;
            while(checkFriendly(i,j,i,y_int,a)!=0 && checkInside(i,y_int,a)!=0)
           {  
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
               
              doMove(i,j,i,y_int,a);
              score=evaluateMove(a);
              doMove(i, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=i;
                y_ef=y_int;
              }
               nrMoves++;
              int2++;
             y_int++;
           }
           x_int=i-int3;
           while(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
           {
               yf=y_int+'a'-1;
               xf=8-x_int +'0';
               //printf(%c%c\n",xf,yf);
               aux=a[x_int][j];
              doMove(i,j,x_int,j,a);
              score=evaluateMove(a);
              doMove(x_int,j,i,j,a);
               a[x_int][j]=aux;
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=j;
              }
                nrMoves++;
                int3++;
               x_int--;
        
            }
            y_int=j-int4;
          while(checkFriendly(i,j,i,y_int,a)!=0 && checkInside(i,y_int,a)!=0)
           {

              yf=y_int+'a'-1;
              xf=8-x_int +'0';
              nrMoves++;
             //printf(%c%c\n",xf,yf);
              doMove(i,j,i,y_int,a);
              score=evaluateMove(a);
              doMove(i, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=i;
                y_ef=y_int;
              }
             int4++;
              y_int--;

           }
         
         if(nrMoves==0)
          {
         // /printf("no moves\n");
          }
          *sc=maxScore;
          *ifin=x_ef;
          *jfin=y_ef;
      
      break;
   
 case 'n':
      //printf("possible moves:\n");
    
         nrMoves=0;
       
         x_int=x_int+int1;
         y_int=y_int+int1;
         while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
          {
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             nrMoves++;
           int1++;
            x_int++;
            y_int++;
        
          }
          x_int=i-int2;
          y_int=j-int2;
          while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
          {
             yf=y_int+'a'-1;
             xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
              nrMoves++;
             int2++;
            x_int--;
            y_int--;

           }
         x_int=i-int3;
         y_int=j+int3;
         while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
         {
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
          //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             nrMoves++;
            int3++;
           x_int--;
           y_int++;
       
          }
          x_int=i+int4;
          y_int=j-int4;
          while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
           {
        
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
              nrMoves++;
            //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             int4++;
             x_int++;
             y_int--;

          }
         if(nrMoves==0)
          {
         // /printf("no moves\n");
          }
            *sc=maxScore;
          *ifin=x_ef;
          *jfin=y_ef;
      
      break;
  case 'f':
     //printf("possible moves:\n");
         nrMoves=0;
       
         x_int=i+int1;
         while(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
          {
            yf=j+'a'-1;
            xf=8-x_int +'0';
           //printf(%c%c\n",xf,yf);
              aux=a[x_int][j];
              doMove(i,j,x_int,j,a);
              score=evaluateMove(a);
              doMove(x_int,j,i,j,a);
              a[x_int][j]=aux;
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=j;
              }
             nrMoves++;
           int1++;
            x_int++;
        
          }
          y_int=j+int2;
          while(checkFriendly(i,j,i,y_int,a)!=0 && checkInside(i,y_int,a)!=0)
          {
             yf=y_int+'a'-1;
             xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
             aux=a[i][y_int];
              doMove(i,j,i,y_int,a);
              score=evaluateMove(a);
              doMove(i, y_int,i,j,a);
              a[i][y_int]=aux;
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=i;
                y_ef=y_int;
              }
              nrMoves++;
             int2++;
            y_int++;

           }
         x_int=i-int3;
         while(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
         {
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
          //printf(%c%c\n",xf,yf);
              aux=a[x_int][j];
              doMove(i,j,x_int,j,a);
              score=evaluateMove(a);
              doMove(x_int,j,i,j,a);
              a[x_int][j]=aux;
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=j;
              }
             nrMoves++;
            int3++;
           x_int--;
        
          }
          y_int=j-int4;
          while(checkFriendly(i,j,i,y_int,a)!=0 && checkInside(i,y_int,a)!=0)
           {

              yf=y_int+'a'-1;
              xf=8-x_int +'0';
              nrMoves++;
            //printf(%c%c\n",xf,yf);
              aux=a[i][y_int];
              doMove(i,j,i,y_int,a);
              score=evaluateMove(a);
              doMove(i, y_int,i,j,a);
              a[i][y_int]=aux;
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=i;
                y_ef=y_int;
              }
             int4++;
              y_int--;

          }
          int1=1;
          int2=1;
          int3=1;
          int4=1;
           x_int=i+int1;
         y_int=j+int1;
         while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
          {
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
           //printf(%c%c\n",xf,yf);
               aux=a[x_int][y_int];
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              a[x_int][y_int]=aux;
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             nrMoves++;
           int1++;
            x_int++;
            y_int++;
        
          }
          x_int=i-int2;
          y_int=j-int2;
          while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
          {
             yf=y_int+'a'-1;
             xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
             aux=a[x_int][y_int];
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              a[x_int][y_int]=aux;
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
              nrMoves++;
             int2++;
            x_int--;
            y_int--;

           }
         x_int=i-int3;
         y_int=j+int3;
         while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
         {
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
           //printf(%c%c\n",xf,yf);
             aux=a[x_int][y_int];
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              a[x_int][y_int]=aux;
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             nrMoves++;
            int3++;
           x_int--;
           y_int++;
        
          }
          x_int=i+int4;
          y_int=j-int4;
          while(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
           {

              yf=y_int+'a'-1;
              xf=8-x_int +'0';
              nrMoves++;
            //printf(%c%c\n",xf,yf);
              aux=a[x_int][y_int];
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              a[x_int][y_int]=aux;
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             int4++;
             x_int++;
             y_int--;

          }
          if(nrMoves==0)
          {
          //printf("no moves\n");
          }
            *sc=maxScore;
          *ifin=x_ef;
          *jfin=y_ef;
      
      break;
    case 'i':
        //printf("possible moves:\n");
         nrMoves=0;
        if(i==1)
        { if(a[i][j]=='I')
         { x_int=i+int1;
          if(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
          {
             nrMoves++;
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
          //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
          }
          int1++;
          x_int++;
          if(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
          {
             nrMoves++;
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
          //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
          
         }
         }

        }
        if(i==6)
        { if(a[i][j]=='i')
          {x_int=i-int1;
          if(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
          {
             nrMoves++;
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
          //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
          }
          int1++;
          x_int--;
          if(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
          {
             nrMoves++;
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
          //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
          }
        }
        }
          if(a[i][j]=='i' && i!=6)
          {
            
            x_int--;
            if(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
           {
             nrMoves++;
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
          //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
           }
          }
          if(a[i][j]=='I' && i!=1)
          {
            x_int++;
            if(checkFriendly(i,j,x_int,j,a)!=0 && checkInside(x_int,j,a)!=0)
           {
             nrMoves++;
            yf=y_int+'a'-1;
            xf=8-x_int +'0';
           //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
           }
          }
              if(nrMoves==0)
          {
           //printf("no moves\n");
          }
           *sc=maxScore;
          *ifin=x_ef;
          *jfin=y_ef;
      break;
    case 'c':
       //printf("possible moves:\n");
      
        x_int=x_int+2;
        y_int=y_int+1;
         if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
           //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }
        y_int=y_int-2;
        if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
            //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }
      
      
        x_int=x_int-1;
        y_int=y_int-1;
         if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
            //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }
        y_int=y_int+4;
        if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
           //   printf("the score is %f",score);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }
          x_int=x_int-2;
          if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }
            x_int=x_int-1;
            y_int=y_int-1;
             if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }
            y_int=y_int-2;
            if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }
            x_int=x_int+1;
            y_int=y_int-1;
              if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }

      
           if(nrMoves==0)
           {
                 //  //printf("no moves\n");
          }
           // printf("the maxscore is %f\n",maxScore);
            *sc=maxScore;
          *ifin=x_ef;
          *jfin=y_ef;
      break;
      case 'm':
        //printf("possible moves:\n");
         nrMoves=0;
       x_int++;
       if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }
       y_int++;
       if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
            //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }
       x_int--;
       if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }
     x_int--;
     if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }
     y_int--;
     if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }
    y_int--;
    if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
            //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }
    x_int++;
    if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }

    x_int++;
    if(checkFriendly(i,j,x_int,y_int,a)!=0 && checkInside(x_int,y_int,a)!=0)
             {
               nrMoves++;
              yf=y_int+'a'-1;
              xf=8-x_int +'0';
             //printf(%c%c\n",xf,yf);
              doMove(i,j,x_int,y_int,a);
              score=evaluateMove(a);
             // printf("%f is the score\n",score);
              doMove(x_int, y_int,i,j,a);
              if(score>maxScore)
              {
                maxScore=score;
                x_ef=x_int;
                y_ef=y_int;
              }
             }
    
           if(nrMoves==0)
           {
               //    /printf("no moves\n");
          }
         
           *sc=maxScore;
          *ifin=x_ef;
          *jfin=y_ef;
      
      break;
  }
}
//checking for chess(still to be improved)
int checkForBlackChess(char a[][9])
{ 
  float score,max=-300.0;
  int ip,jp,jef,ief;
  for(int i=0;i<8;i++)
   for(int j=1;j<9;j++)
    {  if(isupper(a[i][j]))
    {
      generateMoves(i,j,a,&score,&ip,&jp);
      if(score>max)
      {
        max=score;
        ief=ip;
        jef=jp;
      }
    }
    }
    if(max>200)
    {
      printf("the black king is in chess!\n");
      printf("black has to move the king!\n");
      return 1;

    }
    return 0;
}
int checkForWhiteChess(char a[][9])
{ 
 float score,max=-300.0;
  int ip,jp,jef,ief;
  for(int i=0;i<8;i++)
   for(int j=1;j<9;j++)
    {  if(islower(a[i][j]))
    {
      generateMoves(i,j,a,&score,&ip,&jp);
      if(score>max)
      {
        max=score;
        ief=ip;
        jef=jp;
      }
    }
    }
    if(max>200)
    {
      printf("the white king is in chess!\n");
      printf("white has to move the king!\n");
      return 1;

    }
    return 0;
}
//implementing the two game modes

char PlayPvP(char a[][9])
{  int checkmate=0,xi=0,yi=0,xf=0,yf=0;
   char pos[10],move[10],winner;
  while(checkmate==0)
  {  int ok=0;
  while(ok==0)
  {
    printf("introduce the move for the white piece in the format initial position and final position:\n");
    scanf("%10s %10s", pos, move);
   // printf("%d%d %d%d\n",xi,yi,xf,yf);
    while(validation(pos,move,a)==0)
    {
       scanf("%10s %10s", pos, move);
      printf("invalid move, try again\n");
    }
     
    getmove(move,&xf,&yf);
    getmove(pos,&xi,&yi);
    char aux=a[xf][yf];
    doMove(xi,yi,xf,yf,a);
    if(checkForWhiteChess(a))
    {
      printf("invalid move,the king is in chess!\n");
      doMove(xf,yf,xi,yi,a);
      a[xf][yf]=aux;
    }
    else 
       ok=1;
     checkForBlackChess(a);
  }
    
    printBoard(a,9);
    ok=0;
    while(ok==0)
  {
    printf("introduce the move for the black piece in the format initial position and final position:\n");
    scanf("%10s %10s", pos, move);
   // printf("%d%d %d%d\n",xi,yi,xf,yf);
    while(validation(pos,move,a)==0)
    {
       scanf("%10s %10s", pos, move);
      printf("invalid move, try again\n");
    }
     
    getmove(move,&xf,&yf);
    getmove(pos,&xi,&yi);
    char aux=a[xf][yf];
    doMove(xi,yi,xf,yf,a);
    if(checkForBlackChess(a))
    {
      printf("invalid move,the king is in chess!\n");
      doMove(xf,yf,xi,yi,a);
      a[xf][yf]=aux;
    }
    else 
       ok=1;
     checkForWhiteChess(a);
  }
    printBoard(a,9);

  }
  return winner;
}
char PlayPvC(char a[][9])
{  
   int checkmate=0,xi=0,yi=0,xf=0,yf=0;
   char pos[10],move[10],winner;
   float score,max=-300.0;
  int ip,jp,ief,jef,jinit,iinit;
   while(checkmate==0)
  {  int ok=0;
   while(ok==0)
  {
     printBoard(a,9);
    printf("introduce the move for your piece in the format initial position and final position:\n");
    scanf("%10s %10s", pos, move);
   // printf("%d%d %d%d\n",xi,yi,xf,yf);
    while(validation(pos,move,a)==0)
    {
       scanf("%10s %10s", pos, move);
      printf("invalid move, try again\n");
    }
     
    getmove(move,&xf,&yf);
    getmove(pos,&xi,&yi);
    char aux=a[xf][yf];
    doMove(xi,yi,xf,yf,a);
    if(checkForBlackChess(a))
    {
      printf("invalid move,the king is in chess!\n");
      doMove(xf,yf,xi,yi,a);
      a[xf][yf]=aux;
    }
    else 
       ok=1;
     checkForWhiteChess(a);
     
  }
   
    printBoard(a,9);
    for(int i=0;i<9;i++)
   for(int j=1;j<9;j++)
    {
      if(isupper(a[i][j]))
      {
        generateMoves(i,j,a,&score,&ip,&jp);
      printf("the score is %f\n",score);
      if(score>max)
      {
    
        max=score;
        ief=ip;
        jef=jp;
        jinit=j;
        iinit=i;
      }
    }
    }
    printf("the final score is %f at the move%d %d to %d %d\n",max,iinit,jinit,ief,jef);
    doMove(iinit,jinit,ief,jef,a);
      printBoard(a,9);
       checkForBlackChess(a);

    



  }

}


int main()
{  
   
   char chessBoard[9][9]= {0}, i=0;
  for(i=0;i<9;i++)
 {
    chessBoard[8][i]='a'+i-1;
    chessBoard[i][0]=8-i;
 }
 SetBoard(chessBoard,9);
 printBoard(chessBoard,9);
   
 int menu;
  
  while(1)
  {
    printf("0.exit\n1.Play PvP\n2.Play PvC\n");
    scanf("%d",&menu);
    switch(menu)
  {  
    case 0:
       exit(0);
       break;
    case 1:
      printBoard(chessBoard,9);
     if(PlayPvP(chessBoard)=='w')
     {
      printf("white is the winner!\n");
     }
     else 
      printf("black is the winner!\n");
      break;
    case 2:

    
    PlayPvC(chessBoard);
      break;

  }  
  
 }
  
    
   
 
  return 0;

}