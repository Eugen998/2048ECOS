#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void stergere_fer()
{
    WINDOW *gol=newwin(LINES,COLS,0,0); //fereastra goala
    wborder(gol, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(gol);
    delwin(gol);
    refresh();
} 

int meniu() {
    int k,j; 
    WINDOW *m;
    WINDOW *n;
    WINDOW *o;
    init_color(8,800,500,400);
    init_color(9,0,600,600);
    init_pair(15,0,8);
    init_pair(16,0,9);
    init_pair(17,0,5);
    char lista[6][80];
    strcpy(lista[0],"                          INCEPERE JOC NOU                          ");
    strcpy(lista[1],"                             REVENIRE                               "); 
    strcpy(lista[2],"                              IESIRE                                "); 
    strcpy(lista[3],"                              DESPRE                                ");
    strcpy(lista[4],"                              SCORURI                               ");
    strcpy(lista[5],"                          INTRODUCETI NUME                          ");
    //lista optiunilor din meniu
    char sel[80];
    //optiunea selectata
    int ch, i = 0;
    initscr(); 


    n = newwin( 11, COLS, (LINES/2)-16, 0 ); 
    wattron(n, COLOR_PAIR(15));
    for(k=1;k<11;k++)
        for(j=1;j<COLS;j++)
            mvwprintw(n,k,j," ");
    mvwprintw(n,1,((COLS/2)-20),"    ****                  ***      ****** ");
    mvwprintw(n,2,((COLS/2)-20),"  ********    ****       ****    ***    *** ");
    mvwprintw(n,3,((COLS/2)-20),"  **   ***  ***  ***    ** **    ***    ***  ");
    mvwprintw(n,4,((COLS/2)-20),"     ***   ***    ***  **  **      ******  ");
    mvwprintw(n,5,((COLS/2)-20),"   ***     ***    *** *********    ******    ");
    mvwprintw(n,6,((COLS/2)-20),"  ***      ***    *** *********   ***  ***");
    mvwprintw(n,7,((COLS/2)-20),"***        ***    ***      **    ***    *** ");
    mvwprintw(n,8,((COLS/2)-20),"*********   ***  ***       **    ***    *** ");
    mvwprintw(n,9,((COLS/2)-20),"*********     ****         **      ******     ");
    box( n, 0, 0 );
    wrefresh(n);
    wattroff(n,COLOR_PAIR(15));


    o = newwin( 11, COLS, (LINES/2)+5, 0 ); 
    wattron(o, COLOR_PAIR(16));
    for(k=1;k<11;k++)
        for(j=1;j<COLS;j++)
            mvwprintw(o,k,j," ");
    mvwprintw(o,2,((COLS/2)-19),"*******    ******    ******     ******* ");
    mvwprintw(o,3,((COLS/2)-19),"*******   *******   ********   ******** ");
    mvwprintw(o,4,((COLS/2)-19),"**        **        **    **   **      ");
    mvwprintw(o,5,((COLS/2)-19),"*****     **        **    **   *******  ");
    mvwprintw(o,6,((COLS/2)-19),"*****     **        **    **    ******* ");
    mvwprintw(o,7,((COLS/2)-19),"**        **        **    **         ** ");
    mvwprintw(o,8,((COLS/2)-19),"*******   *******   ********   ******** ");
    mvwprintw(o,9,((COLS/2)-19),"*******    ******    ******    *******  ");
    box( o, 0, 0 );
    wrefresh(o);
    wattron(o, COLOR_PAIR(16));


    m = newwin( 10, COLS, (LINES/2)-5, 0 ); 
    wattron(m, COLOR_PAIR(17));
    for(k=1;k<11;k++)
        for(j=1;j<COLS;j++)
            mvwprintw(m,k,j," ");
    box( m, 0, 0 );
    for( i=0; i<6; i++ ) {
        if( i == 0 ) 
            wattron( m, A_STANDOUT | A_BOLD );
            //prima optiune este mereu selectata
        else
            wattroff( m, A_STANDOUT | A_BOLD );
        sprintf(sel, "%-7s",  lista[i]);
        mvwprintw( m, i+2, (COLS/2)-33, "%s", sel );
    }
 
    wrefresh( m ); 
    i = 0;
    noecho(); 
    keypad( m, TRUE );
    curs_set( 0 );
    while(( ch = wgetch(m)) != 10){ //tasta enter
            sprintf(sel, "%-7s",  lista[i]); 
            mvwprintw( m, i+2, (COLS/2)-33, "%s", sel ); 
            switch( ch ) {
                case KEY_UP:
                            i--;
                            i = ( i<0 ) ? 5 : i;
                            break;
                case KEY_DOWN:
                            i++;
                            i = ( i>5 ) ? 0 : i;
                            break;
            }
            wattron( m, A_STANDOUT | A_BOLD );
             
            sprintf(sel, "%-7s",  lista[i]);
            mvwprintw( m, i+2, (COLS/2)-33, "%s", sel);
            wattroff( m, A_STANDOUT | A_BOLD);
    }
    wattron(m, COLOR_PAIR(17));
    stergere_fer();
    return i;//ne intereseaza doar indicele optiunii selectate
}

WINDOW *fer(int inalt, int lat, int x, int y, int val, int ant)
{  
    int i; 
    noecho();
    WINDOW *f;
    /*  COLOR_BLACK   0
        COLOR_RED     1
        COLOR_GREEN   2
        COLOR_YELLOW  3
        COLOR_BLUE    4
        COLOR_MAGENTA 5
        COLOR_CYAN    6
        COLOR_WHITE   7*/
    //se definesc culori customizate 
    //care nu exista in lista cu cele predefinite
    init_color(10,1000,0,1000);
    init_color(11,408,0,1000);
    init_color(12,408,1000,1000);
    init_color(13,600,200,600);
    for(i=1;i<=13;i++)
    {
        init_pair(i,0,i);
    }
    init_pair(14,7,0);
    f = newwin(inalt,lat,y,x);

    if( val != 0 )/* daca este nenula, o coloram*/
    {                     /* in functie de valoare*/
        switch (val)
        {
            case 2:
                wattron(f, COLOR_PAIR(1));
                break;
            case 4:
                wattron(f, COLOR_PAIR(2));
                break;
            case 8:
                wattron(f, COLOR_PAIR(3));
                break;
            case 16:
                wattron(f, COLOR_PAIR(4));
                break;
            case 32:
                wattron(f, COLOR_PAIR(5));
                break;
            case 64:
                wattron(f, COLOR_PAIR(6));
                break;
            case 128:
                wattron(f, COLOR_PAIR(8));
                break;
            case 256:
                wattron(f, COLOR_PAIR(10));
                break;
            case 512:
                wattron(f, COLOR_PAIR(11));
                break;
            case 1024:
                wattron(f, COLOR_PAIR(12));
                break;
            case 2048:
                wattron(f, COLOR_PAIR(13));
                break;
            default:
                wattron(f, COLOR_PAIR(7));
        }
        for(i=1;i<4;i++)
        {
            mvwprintw(f,i,1,"         ");//se umple fereastra cu culoarea de background
        }
        if(val<10)
            mvwprintw(f,2,5,"%d",val); 
        else
            mvwprintw(f, 2, 4, "%d", val);
        for(i=1;i<=13;i++) wattroff(f,COLOR_PAIR(i));   
    }
    else box(f, 0 , 0);/* se printeaza doar borderul pentru ferestrele nule*/
    wrefresh(f);
    return f;
}


void atribuire( WINDOW *f[16], int val[16],int ant[16])
{/* fiecarei ferestre i se atribuie o valoare din val[16]*/
//pentru simplitate folosim o matrice unidimensionala val[16] in loc de bidimensionala

    int i,inalt=5,lat=11,x=(COLS/2)-22,y=(LINES/2)-10;////ca sa fie la jumatatea ecranului
    for( i=1;i<=16;i++)
        {
            curs_set (0);/* sa nu se mai vada cursorul*/
            f[i]=fer(inalt,lat,x,y,val[i],ant[i]);
            nodelay(f[i],TRUE);
            if((i%4) == 0)
            {
                y=y+inalt;/* se trece la urmatoarea coloana*/
                x=(COLS/2)-22;
            }
            else {x=x+lat;  /* urmatorul rand*/}
        }  
}

void initializare_matrice(int val[16], int ant[16],int *scor)
{/* se executa doar la inceputul fiecarui joc*/
//se intializeaza scorul, si toate val[i]
    int i;
    srand(time(0));
    for( i=1;i<=16;i++) 
    {
        ant[i]=0;
        val[i]=0;/* se populeaza toate pozitiile cu 0*/
    }
    int i1,i2,r;
    i1=rand()%16+1;
    do
    {
        i2=rand()%16+1;
    }while(i1==i2);
    r=(rand()%2+1)*2;
    val[i1]=r;
    ant[i1]=r;       
    r=(rand()%2+1)*2; 
    val[i2]=r;
    ant[i2]=r;
    *scor=0;
    /* se populeaza doua pozitii alese aleator
    cu 2 sau 4, alese aleator cu conditia
    ca al doilea element populat sa nu fie pe pozitia
    primului element ce a fost deja populat*/
}

void shift_dreapta(int val[16], bool *valid)
{//se cauta val[i]=0 pentru a shifta dreapta
    int i,j=1,ok;
    while(j<=13)
    {   
        ok=1;
        while(ok)//daca ok = 0 nu mai sunt mutari 
        {
            ok=0;
            for(i=j;i<j+3;i++)
            {
                if(val[i]!=0 && val[i+1]==0)
                {
                    val[i+1]=val[i];
                    val[i]=0;
                    ok=1;
                    *valid=TRUE;//s-a executat o mutare valida
                }
            }
        }
        j+=4;
    }
}
void adunare_dreapta(int val[16], int *scor, bool *valid)
{//se cauta valori egale pentru a fi adunate
    
    int i,j=1;
    while(j<=13)
    {
        i=j+3;
        while(i>j)
        {
            if(val[i]!=0) 
            {
                if(val[i-1]==val[i]) 
                {
                    val[i]=val[i-1]*2;
                    *scor=*scor+val[i];
                    val[i-1]=0;
                    *valid=TRUE;//s-a executat o mutare valida

                }
            }
            i--;
        }
        j+=4;
    }
}
void shift_stanga(int val[16], bool *valid)
{
    int i,j=1,ok;
    while(j<=13)
    {   
        ok=1;
        while(ok)
        {
            ok=0;
            for(i=j+3;i>j;i--)
            {
                if(val[i]!=0 && val[i-1]==0)
                {
                    val[i-1]=val[i];
                    val[i]=0;
                    ok=1;
                    *valid=TRUE;
                }
            }
        }
        j+=4;
    }
}
void adunare_stanga(int val[16],int *scor,bool *valid)
{
    int i,j=4;
    while(j<=16)
    {
        i=j-3;
        while(i<j)
        {
            if(val[i]!=0) 
            {
                if(val[i+1]==val[i]) 
                {
                    val[i]=val[i+1]*2;
                    *scor=*scor+val[i];
                    val[i+1]=0;
                    *valid=TRUE;

                }
            }
            i++;
        }
    j+=4;
}

}
void shift_jos(int val[16],bool *valid)
{
    int i,ok,j;
    for(j=0;j<4;j++)
    {
        ok=1;
        while(ok)
        {
            ok=0;
            for(i=1+j;i<13+j;i+=4)
            {
                if(val[i]!=0 && val[i+4]==0)
                {
                    val[i+4]=val[i];
                    val[i]=0;
                    ok=1;
                    *valid=TRUE;
                }
            }
        }
    }
}
void shift_sus(int val[16],bool *valid)
{
    int i,ok,j;
    for(j=0;j<4;j++)
    {
        ok=1;
        while(ok)
            {
                ok=0;
                for(i=13+j;i>1+j;i-=4)
                {
                    if(val[i]!=0 && val[i-4]==0)
                    {
                        val[i-4]=val[i];
                        val[i]=0;
                        ok=1;
                        *valid=TRUE;
                    }
                }
            }
    }
}
void adunare_sus(int val[16],int *scor,bool *valid)
{
    int i,j;
    for(j=0;j<4;j++)
    {
        i=j+1;
        while(i<13+j)
        {
            if(val[i]!=0)
            {
                if( val[i+4]==val[i] )
                {
                    val[i]=val[i+4]*2;
                    *scor=*scor+val[i];
                    val[i+4]=0;
                    *valid=TRUE;
                }
            }
            i+=4;
        }
    }
}
void adunare_jos(int val[16],int *scor,bool *valid)
{
    int i,j;
    for(j=0;j<4;j++)
    {
        i=j+13;
        while(i>j+1)
        {
            if(val[i]!=0)
            {
                if( val[i-4]==val[i] )
                {
                    val[i]=val[i-4]*2;
                    *scor=*scor+val[i];
                    val[i-4]=0;
                    *valid=TRUE;
                }
            }
            i-=4;
        }
    }
    
}
void populare(int val[16])
//se executa dupa fiecare shiftare sau contopire
{//se populeaza sirul val[16] cu un element aleator 2 sau 4
// pe o pozitie aleator aleasa nenula
    int r,i;
    srand(time(0));
    r=(rand()%2+1)*2;
    i=(rand()%16)+1;
    while(val[i]!=0)
        i=(rand()%16)+1;
    val[i]=r;
}

bool verivic(int val[16])
    {//se verifica VICTORIA
        int i;
        bool vic=FALSE;
        for (i=1;i<=16;i++)   
            if (val[i]==2048) {vic = TRUE;}
        return vic;
    }
void afisare_scor(WINDOW *sc,int scor)
{
    mvwprintw(sc,1,0,"             " );
    mvwprintw(sc,1,1,"  SCOR:%d",scor);
    box(sc,0,0);
    wrefresh(sc);
}   
bool mutari_valide(int val[16])
{//se verifica daca mai sunt val[i] nenule sau daca mai sunt casute identice 
  // pe orizontala sau verticala  
    bool ok = FALSE;
    int i,j=1;
    while(j<=13)
    {
        for(i=j;i<j+3;i++)
        {
            if(val[i]==val[i+1] || val[i]==0 || val[i+1]==0) 
            {
                ok=TRUE;
                return ok;
            }
        }
    j=j+4;
    }
    j=1;
    while(j<=4)
    {
        for(i=j;i<j+12;i+=4)
        {
            if(val[i]==val[i+4] || val[i]==0 || val[i+4]==0) 
                {
                    ok=TRUE;
                    return ok;
                }
        }
        j++;
    }
    return ok;//daca ok=TRUE, mai sunt mutari
}
void afisare_ora()
{   
    int i;
    time_t ora;
    init_color(8,800,500,400);
    init_pair(18,0,8);
    ora = time(NULL);
    WINDOW *timp;//afisarea orei
    timp=newwin(3,58,(LINES/2)-13,(COLS/2)-22);
    wattron(timp,COLOR_PAIR(18));
    for(i=1;i<58;i++) mvwprintw(timp,1,i," ");
    mvwprintw(timp,1,12,"DATA/ORA: %s",ctime(&ora));
    for(i=46;i<58;i++) mvwprintw(timp,1,i," ");
    box(timp,0,0);
    wattroff(timp,COLOR_PAIR(15));
    wrefresh(timp);
}

void afisare_user( char nume[20] )
{
    int i;
    WINDOW *user;
    init_color(9,0,600,600);
    init_pair(20,0,9);
    user=newwin(3,58,(LINES/2)+10,(COLS/2)-22);
    wattron(user,COLOR_PAIR(20));
    for(i=1;i<58;i++) mvwprintw(user,1,i," ");
    mvwprintw(user,1,23,"HELLO %s", nume);
    box(user,0,0);
    wattroff(user,COLOR_PAIR(20));
    wrefresh(user);
}

int nr_zero(int aux[16])
{// se calculeaza numarul de zerouri
 // aceasta functie este utilizata pentru a decide in care directie
 //se va muta pentru auto-move   
    int i,z=0;
    for(i=1;i<=16;i++)
    {
        if(aux[i]==0) z++;
    }
    return z;
}



int main()
{
    int val[16],ant[16]={0},scor=0,x,y,i,j,scorant=0,ok=0,zd,zs,zup,zdwn,aux[16],scor2,timer=0;
    char nume[20]= "Stranger";
    //char lista[10][20];
    //for(i=0;i<10;i++) strcpy(lista[i],"Stranger");
    bool valid;
    bool mutari;
    bool terminat;
    initscr();
    getmaxyx(stdscr,y,x);//aflam dimensiuni ecran
    start_color();
    raw();
    cbreak();
    noecho();
    nodelay(stdscr,TRUE);
    timeout(1000);

    typedef struct nume_scor//definesc o structura pentru tabela de scoruri 
    {
    	char username[10];
    	int userscore;

    }namescore;

	namescore nmscr[10];

	strcpy(nmscr[1].username,"user");//initializez tabela de scoruri cu perechi
	nmscr[1].userscore=0;          // user-scor 

	strcpy(nmscr[2].username,"user");
	nmscr[2].userscore=0;

	strcpy(nmscr[3].username,"user");
	nmscr[3].userscore=0;

	strcpy(nmscr[4].username,"user");
	nmscr[4].userscore=0;

	strcpy(nmscr[5].username,"user");
	nmscr[5].userscore=0;

	strcpy(nmscr[6].username,"user");
	nmscr[6].userscore=0;

	strcpy(nmscr[7].username,"user");
	nmscr[7].userscore=0;

	strcpy(nmscr[8].username,"user");
	nmscr[8].userscore=0;

	strcpy(nmscr[9].username,"user");
	nmscr[9].userscore=0;

	strcpy(nmscr[10].username,"user");
	nmscr[10].userscore=0;

	
    int men = meniu();
    label:
    switch(men)
    {
        case 0:
        {
            initializare_matrice(val,ant,&scor);
            ok=1;//prima optiune din meniul  principal, joc nou
            timer=0;
            break;
        }
        case 1:
        {
            if(ok==0) initializare_matrice(val,ant,&scor);
            ok=1;
            break;
        }
        case 2:
        {
            stergere_fer();
            endwin();
            return 0;//optiunea quit
        }
        case 3:
        {  
            stergere_fer();
            WINDOW *p;
            init_color(8,800,500,400);
            init_color(10,0,600,600);
            init_pair(17,10,8);
            init_pair(18,5,5);
            p=newwin(16,COLS,(LINES/2)-8,0);
            wattron(p,COLOR_PAIR(17));
            for(i=1;i<20;i++)
                for(j=1;j<COLS;j++)
                    mvwprintw(p,i,j," ");
            mvwprintw(p,6,(COLS/2)-26,"JOC 2048, realizat de EUGEN COSTIN, Dec 2017-Ian 2018");
            mvwprintw(p,9,(COLS/2)-13,"PRESS ANY KEY TO MAIN MENU");
            wattroff(p,COLOR_PAIR(17));
            wattron(p,COLOR_PAIR(18));
            box(p,0,0);
            wrefresh(p);
            wattroff(p,COLOR_PAIR(18));
            getchar();
            stergere_fer();
            men=meniu();
            goto label;
        }
        case 4:
        {
            stergere_fer();
            WINDOW *s;
            s=newwin(24,COLS,(LINES/2)-10,0);
            init_color(8,800,500,400);
            init_color(10,0,600,600);
            init_pair(17,10,8);
            init_pair(18,5,5);
            wattron(s,COLOR_PAIR(17));//printez cele mai mare 10 scoruri
            for(i=1;i<24;i++)//printez cu rand liber
                for(j=1;j<COLS;j++)
                    mvwprintw(s,i,j," ");
            for(i=2;i<22;i+=2) mvwprintw(s, i+1, (COLS/2)-1, "%d    %s",nmscr[i/2].userscore,nmscr[i/2].username);
            wattroff(s,COLOR_PAIR(17));
            wattron(s,COLOR_PAIR(18));
            box(s,0,0);
            wrefresh(s);
            wattroff(s,COLOR_PAIR(18));
            getchar();
            stergere_fer();
            men=meniu();
            goto label;
        }
        case 5:
        {  
            
            stergere_fer();
            WINDOW *p;
            init_color(8,800,500,400);
            init_color(10,0,600,600);
            init_pair(17,10,8);
            init_pair(18,5,5);
            p=newwin(16,COLS,(LINES/2)-8,0);
            keypad(p,FALSE);
            echo();
            wattron(p,COLOR_PAIR(17));
            for(i=1;i<16;i++)
                for(j=1;j<COLS;j++)
                    mvwprintw(p,i,j," ");
            mvwprintw(p,6,(COLS/2)-26,"JOC 2048, realizat de EUGEN COSTIN, Dec 2017-Ian 2018");
            mvwprintw(p,9,(COLS/2)-6,"INTRODU NUME");
            mvwprintw(p,12,(COLS/2)-5," ");
            wattroff(p,COLOR_PAIR(17));
            wattron(p,COLOR_PAIR(18));
            box(p,0,0);
            wrefresh(p);
            wattroff(p,COLOR_PAIR(18));
            wgetstr(p,nume);
            nume[strlen(nume)] = '\0';
            stergere_fer();
            men=meniu();
            goto label;
        }
    }
    if(has_colors() == FALSE)
    {   
        endwin();
        printf("Terminalul nu suporta culori\n");
    }
    
    afisare_ora();
    afisare_user(nume);
    WINDOW *sc;/* fereastra unde se va afisa scorul*/
    sc=newwin(3,14,(LINES/2)+7,(COLS/2)+22);
    afisare_scor(sc,scor);
    init_pair(19,0,5);
    WINDOW *help;/* afisarea meniului help*/
    help=newwin(17,14,(LINES/2)-10,(COLS/2)+22);
    wattron(help,COLOR_PAIR(19));
    for(i=1;i<17;i++)
        for(j=1;j<14;j++)
            mvwprintw(help,i,j," ");
    mvwprintw(help,1,1, "W-Sus");
    mvwprintw(help,2,1, "S-Jos");
    mvwprintw(help,3,1, "A-Stanga");
    mvwprintw(help,4,1, "D-Dreapta");
    mvwprintw(help,5,1, "U-UNDO");
    mvwprintw(help,6,1, "Q-Meniu");
    mvwprintw(help,8,1, "Z-AUTOMOVE");
    mvwprintw(help,10,1, "Dimensiune");
    mvwprintw(help,11,1, "  ecran");
    mvwprintw(help,12,1, "x=%d, y=%d",x,y);
    mvwprintw(help,13,1, "-----------");
    mvwprintw(help,14,1, "TIMER");
    box(help,0,0);
    wrefresh(help);
    wattroff(help,COLOR_PAIR(19));

    WINDOW *f[16];
    atribuire(f,val,ant); 

    int ch;
    ch=getch();
    while( ch != 27 ) //tasta ESC iese complet din joc
    {
        initial:
        afisare_ora();
        if( ch == ERR )
        {
            timer++;
            wattron(help,COLOR_PAIR(19));
            mvwprintw(help,15,1, "AUTOMOVE: %d",10-timer);
            wrefresh(help);
            wattroff(help,COLOR_PAIR(19));
            if(timer >= 10)
            {
                ch = 'z';
                timer=0;
            }
        }
        if(ch == 'd' )
        {
            timer=0;//se reseteaza contorul de auto move
            scorant=scor;
            for(i=1;i<=16;i++)  ant[i]=val[i];
            valid=FALSE;
            shift_dreapta(val,&valid);
            adunare_dreapta(val,&scor,&valid);
            shift_dreapta(val,&valid);
            if(valid)
            { 
                populare(val);
                atribuire(f,val,ant);
            }
            
        }
        if(ch == 'a' )
        {
            timer=0;//se reseteaza contorul de auto move
            scorant=scor;
            for(i=1;i<=16;i++)  ant[i]=val[i];
            valid=FALSE;
            shift_stanga(val,&valid);
            adunare_stanga(val,&scor,&valid);
            shift_stanga(val,&valid);
            if(valid)
            { 
                populare(val);
                atribuire(f,val,ant);
            }

        }
        if(ch == 's')
        {
            timer=0;//se reseteaza contorul de auto move
            scorant=scor;
            for(i=1;i<=16;i++)  ant[i]=val[i];
            valid=FALSE;
            shift_jos(val,&valid);
            adunare_jos(val,&scor,&valid);
            shift_jos(val,&valid);
            if(valid)
            { 
                populare(val);
                atribuire(f,val,ant);
            }
        }   
        if(ch == 'w')
        {
            timer=0;//se reseteaza contorul de auto move
            scorant=scor;
            for(i=1;i<=16;i++)  ant[i]=val[i];
            valid=FALSE;
            shift_sus(val,&valid);
            adunare_sus(val,&scor,&valid);
            shift_sus(val,&valid);
            if(valid)
            { 
                populare(val);
                atribuire(f,val,ant);
            }   
        }
        if(ch == 'u')
        {
            timer=0;//se reseteaza contorul de auto move
            scor=scorant;
            for(i=1;i<=16;i++)
            {
                val[i]=ant[i];
            }
            atribuire(f,val,ant);
        }

        if(ch == 'q')
        {
            stergere_fer();            
            men=meniu();//se iese in meniul principal
            goto label;
        }   
        if(ch == 'z')
        {
            valid=FALSE;
            scor2=0;
            for(i=1;i<=16;i++) aux[i]=val[i];//copiez matricea intr-o matrice auxiliara
            shift_dreapta(aux,&valid);
            adunare_dreapta(aux,&scor2,&valid);//calculez zerourile obtinute in toate directiile
            shift_dreapta(aux,&valid);
            if(valid) zd=nr_zero(aux);
            else zd=0;
            valid=FALSE;
            for(i=1;i<=16;i++) aux[i]=val[i];
            shift_stanga(aux,&valid);
            adunare_stanga(aux,&scor2,&valid);
            shift_stanga(aux,&valid);
            if(valid) zs=nr_zero(aux);
            else zs=0;
            valid=FALSE;
            for(i=1;i<=16;i++) aux[i]=val[i];
            shift_sus(aux,&valid);
            adunare_sus(aux,&scor2,&valid);
            shift_sus(aux,&valid);
            if(valid) zup=nr_zero(aux);
            else zup=0;
            valid=FALSE;
            for(i=1;i<=16;i++) aux[i]=val[i];
            shift_jos(aux,&valid);
            adunare_jos(aux,&scor2,&valid);
            shift_jos(aux,&valid);
            if(valid) zdwn=nr_zero(aux);
            else zdwn=0;
            int max=zd;
            if(zs>max) max=zs;//decid in ce directie este cel mai recomandat sa mut
            if(zup>max) max=zup;//pe baza numarului maxim de celule eliberate 
            if(zdwn>max) max=zdwn;
            if(max==zd) ch='d';
            if(max==zs) ch='a';
            if(max==zup) ch='w';
            if(max==zdwn) ch='s';
            goto initial;
        } 
            
        afisare_scor(sc,scor);
        terminat=verivic(val);
        if (terminat) 
        {
                box(sc,0,0);
                mvwprintw(sc,1,3,"BRAVO!   ");
                wrefresh(sc);
                sleep(3);
                namescore temporary;// o variabila temporara pentru sortare
            	ok=1;				        
        			if (scor>nmscr[10].userscore)//daca scorul curent este mai mare decat cel mai mic scor
            			{
            			nmscr[10].userscore=scor;//adaug userul si scorul curente
            			strcpy(nmscr[10].username,nume);//pe ultima pozitie din lista de scoruri

            			}
					while(ok)//sortez lista bidimensionala user/scor
        				{
                            ok=0;// s-a terminat sortarea cand OK=0
            				for(i=1;i<10;i++)
            				{
                				if(nmscr[i].userscore<nmscr[i+1].userscore) 
                				{                                           
                    			temporary.userscore=nmscr[i].userscore;
                    			nmscr[i].userscore=nmscr[i+1].userscore;
                    			nmscr[i+1].userscore=temporary.userscore;
                    			strcpy(temporary.username,nmscr[i].username);
                    			strcpy(nmscr[i].username,nmscr[i+1].username);
                    			strcpy(nmscr[i+1].username,temporary.username);
                    			ok=1;
                				}
            				}
                        }
                getch();
                stergere_fer();
                men=meniu();
                goto label;
                endwin();
        }
        mutari=mutari_valide(val);
        if (mutari==FALSE)
        {
                box(sc,0,0);
                mvwprintw(sc,1,1,"FARA MUTARI!");
                wrefresh(sc);
                sleep(3);
                namescore temporary;// o variabila buffer temporara pentru sortare
            	ok=1;				        
        			if (scor>nmscr[10].userscore)//daca scorul curent este mai mare decat cel mai mic scor
            			{
            			nmscr[10].userscore=scor;//adaug userul si scorul curente
            			strcpy(nmscr[10].username,nume);//pe ultima pozitie din lista de scoruri

            			}
					while(ok)//sortez lista bidimensionala user/scor
        				{
            			ok=0;// s-a terminat sortarea cand OK=0
            				for(i=1;i<10;i++)
            				{
                				if(nmscr[i].userscore<nmscr[i+1].userscore) 
                				{                                           
                    			temporary.userscore=nmscr[i].userscore;
                    			nmscr[i].userscore=nmscr[i+1].userscore;
                    			nmscr[i+1].userscore=temporary.userscore;
                    			strcpy(temporary.username,nmscr[i].username);
                    			strcpy(nmscr[i].username,nmscr[i+1].username);
                    			strcpy(nmscr[i+1].username,temporary.username);
                    			ok=1;
                				}
            				}
        				}
                getch();
                stergere_fer();
                men=meniu();
                goto label;
                endwin();
        }
        afisare_ora();
        ch=getch();
    }

    endwin();
}
