//version with chase, infinite and Predator Herbs
#include <iostream>
#include <math.h>
#include <vector>
#include <random>
#include <unistd.h> //for macos or linux. if you use them, you don’t have to change the code)))
/*if you want to use it on Windows, remove the comment from here (include <windows.h> and void clear())
and comment #include <unistd.h> and void clear() below*/
/*#include <windows.h>
void clear() {
    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}*/
*/

void clear() {
    cout << "\x1B[2J\x1B[H";
}
using namespace std;
const int xl=101,yl=20; //размер
const int pymin=10,pymax=40,hymin=10,hymax=30; //границы возраста
const int pEat=2,hEat=2,EatCount=5; //еда сичтается за EatCount ходов, pEat и hEat - коэфициенты еды, нужной для жизни
const int nP=50; //начальное количество хищников
const int nH=50; //начальное кол-во травоядных
const int hChild=2, pChild=2; //сколько еды нужно, чтобы родить ребенка
const int hReproduce[2]={2,10},pReproduce[2]={4,6}; //репродуктивные границы
const int hMaxChild=2,pMaxChild=4; //максимальное количество детей за 1 раз
const int pMaxPopulation=50000, hMaxPopulation=50000; //ограничение максимального количества объектов для программы
const int nTrava=300; // кол-во травы;
const int tPercent=50; //процент восстановления травы за 1 ход
const int nFire=5; //кол-во пожаров за ход
const int MeteoriteChance=100000; //шанс метеорита 1/n
const int pSickChance=20, hSickChance=50; //шанс заболеть 1/n
const int phN=10;

int ym(int y,int r){
    if(r==0){
        if(y==0){
            y+=1;
        } else if(y==yl-1){
            y-=1;
        } else {
            if(rand()%2==0)
                y+=1;
            else
                y-=1;
        }
    } else {
        if(y==0){
            y+=rand()%2;
        } else if(y==yl-1){
            y-=rand()%2;
        } else
            y+=rand()%3-1;

    }
    return y;
}
int xm(int x){
    if(x==0){
        x+=rand()%2;
    } else if(x==xl-1){
        x-=rand()%2;
    } else {
        x+=rand()%2-1;
    }
    return x;
}
class PredatorHerb{
public:
    int x=rand()%xl,y=rand()%yl;

};
class Predator{
public:
    int x=rand()%xl,y=rand()%yl,year, maxyear=(random())%(pymax-pymin)+pymin,child=0,bufcount=0;
    vector<int> food={0,0};
    vector < vector <int> > buf={{}};
    bool dead = false,sick=false;
    void life(){
        for(int cock=0;cock<1;cock++){
            if(year==maxyear or food.size()<(pEat/*year)/pymin*/)){
                dead=true;
                break;
            }

            for(int i=0;i<food.size();i++){
                food[i]++;
            }
            vector<int> odd;
            copy_if(food.begin(), food.end(), back_inserter(odd), [](int i) {
                return i<EatCount == 1;
            });
            food=odd;

            if(year<pReproduce[1] && year>pReproduce[0] && pChild<=food.size() && !sick){
                child=rand()%pMaxChild;
            }
            if(rand()%pSickChance==1)
                sick= true;

        }}
    void search(int xh, int yh){
        if(!sick){
        buf.push_back({xh,yh});
        bufcount++;}
    }
    void move(){
        int bufx=-1, bufy=-1;
        year++;
        float smin=1000000;
        for(int i=1;i<bufcount;i++){
            float s=sqrt(pow(x-buf[i][0],2)+pow(y-buf[i][1],2));
            if(s<smin){
                bufx=buf[i][0];
                bufy=buf[i][1];
            }
        }
        if(bufx==-1 || smin==0){
            int r=xm(x)-x;
            y=ym(y,r);
            x+=r;
            year++;
        } else {
            if(bufx>x)
                x++;
            else
                x--;

            if(bufy>y)
                y++;
            else
                y--;
        }
        buf={{}};
        bufcount=0;
    }
    bool eat(int xz,int yz){
        if(!sick){
        if( abs(x-xz)<=1 && abs(y-yz)<=1){
            food.push_back(0);
            return true;
        }
        return false;
    }}
};
class Herbivore{
public:
    int x=rand()%xl,y=rand()%yl,year, maxyear=(random())%(hymax-hymin)+hymin,child=0,bufcount=0;
    vector<int> food={0,0};
    vector < vector <int> > buf={{}};
    bool dead = false, sick=false;
    void life(){
            for(int cock=0;cock<1;cock++){
                if(year==maxyear || food.size()<(hEat/*year*/)/*hymin*/){
                    dead=true;
                    break;
                }

                for(int i=0;i<food.size();i++){
                    food[i]++;
                }
                vector<int> odd;
                copy_if(food.begin(), food.end(), back_inserter(odd), [](int i) {
                    return i<EatCount == 1;
                });
                food=odd;

                if(year<hReproduce[1] && year>hReproduce[0] && hChild<=food.size() && !sick){
                    child=rand()%hMaxChild;
                }
                if(rand()%hSickChance==1){
                    sick= true;
                }
            }
    }

    void search(int xh, int yh){
        if(!sick){
        buf.push_back({xh,yh});
        bufcount++;
        }
    }
    void move(){
        int bufx=-1, bufy=-1;
        year++;
        float smin=1000000;
        for(int i=1;i<bufcount;i++){
            float s=sqrt(pow(x-buf[i][0],2)+pow(y-buf[i][1],2));
            if(s<smin){
                bufx=buf[i][0];
                bufy=buf[i][1];
            }
        }
        if(bufx==-1 || smin==0){
            int r=xm(x)-x;
            y=ym(y,r);
            x+=r;
            year++;
        } else {
            if(bufx>x)
                x++;
            else
                x--;

            if(bufy>y)
                y++;
            else
                y--;
        }
        buf={{}};
        bufcount=0;
    }

    bool eat(int xz,int yz){
        if(!sick){
        if(x==xz and y==yz){
            food.push_back(0);
            return true;
        } return false;
    }
    }

};
class Trava{
public:
    int recoveryCount=100,x=rand()%xl,y=rand()%yl;
    bool dead = false;
    void recovery(){
        if(recoveryCount<100){
            recoveryCount+=tPercent;
        }
    }
    char visual(){
        if(recoveryCount<100) return '_';
        return '^';
    }
};
class Fire{
public:
    int x=rand()%xl,y=rand()%yl;
};

void the_end(int count){
    vector<string> f1(yl/2-2, string(xl, ' '));
    vector<string> f2(1, string(xl, '-'));
    vector<string> f3(1, string(xl, ' '));
    f3[0][xl/2-2]='T';
    f3[0][xl/2-1]='H';
    f3[0][xl/2]='E';
    f3[0][xl/2+2]='E';
    f3[0][xl/2+3]='N';
    f3[0][xl/2+4]='D';
    for( auto str: f1){
        cout<<str<<endl;
    }
    for( auto str: f2){
        cout<<str<<endl;
    }
    for( auto str: f3){
        cout<<str<<endl;
    }
    for( auto str: f2){
        cout<<str<<endl;
    }
    cout<<string((xl-14)/2+2,' ')+"Total Step: "<<count<<endl;
}
void met(int count){
    the_end(count);
    cout<<string((xl-14)/2+2,' ')+"Meteorite fell";
    vector<string> f1(yl/2-2, string(xl, ' '));
    for( auto str: f1){
        cout<<str<<endl;
    }
}
int main() {
    int n=nP, n1=nH;
    srand(time(NULL));

    Trava tArr[nTrava];
    int count=0;
    while(count<nTrava){
        bool t=true;
        for(int i=0;i<count;i++){
            if(tArr[i].y==tArr[count].y && tArr[i].x==tArr[count].x)
                t=false;
        }
        if(!t)
            tArr[count].x=rand()%xl,tArr[count].y=rand()%yl;
        else
            count++;
    }
    count=0;
    PredatorHerb phArr[phN];
    while(count<phN){
        bool t=true;
        for(int i=0;i<count;i++){
            if(phArr[i].y==phArr[count].y && phArr[i].x==phArr[count].x)
                t=false;
        }
        if(!t)
            phArr[count].x=rand()%xl,phArr[count].y=rand()%yl;
        else
            count++;
    }
    int mainCount=0;
    Predator pArr[pMaxPopulation];
    Herbivore hArr[hMaxPopulation];
    while(1==1) {
        if(rand()%MeteoriteChance==1){
            clear();
            met(mainCount);
            return 0;
        }
        mainCount++;
        int hcount=0, pcount=0, tcount1=0, tcount2=0,hsick=0,psick=0;
        vector<string> f(yl, string(xl+1, ' '));
        for(int i=0;i<nTrava;i++){ //trava
            if(!tArr[i].dead){
                tArr[i].recovery();
                f[tArr[i].y][tArr[i].x]=tArr[i].visual();
                if(f[tArr[i].y][tArr[i].x]=='_')
                    tcount2++;
                else
                    tcount1++;}
        }
        for(int i=0;i<phN;i++){
            f[phArr[i].y][phArr[i].x]='7';
        }
        for(int i=0;i<n1;i++){ //herd
            if(!hArr[i].dead){
                hcount++;
                if(hArr[i].sick)
                    hsick++;
                hArr[i].life();
                for(int q=0;q<nTrava;q++){
                    if(tArr[q].recoveryCount==100 && !tArr[q].dead) {
                        if (hArr[i].eat(tArr[q].x, tArr[q].y)) {
                            tArr[q].recoveryCount = 0;
                        }
                    }}
                for(int q=0; q<nTrava;q++){
                    if(!tArr[q].dead){
                        hArr[i].search(tArr[q].x,tArr[q].y);
                    }
                }
                hArr[i].move();
                f[hArr[i].y][hArr[i].x]='%';
                n1+=hArr[i].child;
            }
        }
        for(int i=0;i<n;i++){ //pred
            if(!pArr[i].dead){
                pcount++;
                if(pArr[i].sick){
                    psick++;
                }
                pArr[i].life();
                for(int q=0;q<n1;q++){
                    if(!hArr[q].dead){
                        if(pArr[i].eat(hArr[q].x, hArr[q].y)){
                            hArr[q].dead= true;
                        }}
                }
                for(int q=0; q<n1;q++){
                    if(!hArr[q].dead){
                        pArr[i].search(hArr[q].x,hArr[q].y);
                    }
                }
                pArr[i].move();
                f[pArr[i].y][pArr[i].x]='*';
                n+=pArr[i].child;
            }
        }
        Fire fire[nFire];
        int bufcount=0;
        for(int y=0;y<nFire;y++){ //Fire and PH

            f[fire[y].y][fire[y].x]='#';
            for(int i=0;i<nTrava;i++){
                if(bufcount<phN){
                    if(phArr[bufcount].y==tArr[i].y && phArr[bufcount].x==tArr[i].x)
                        tArr[i].dead=true;
                }
                if(fire[y].y==tArr[i].y && fire[y].x==tArr[i].x)
                    tArr[i].dead=true;
            }
            for(int i=0;i<n;i++){
                if(bufcount<phN){
                    if(phArr[bufcount].y==pArr[i].y && phArr[bufcount].x==pArr[i].x)
                        pArr[i].dead=true;
                }
                if(fire[y].y==pArr[i].y && fire[y].x==pArr[i].x)
                    pArr[i].dead=true;
            }
            for(int i=0;i<n1;i++){
                if(bufcount<phN){
                    if(phArr[bufcount].y==hArr[i].y && phArr[bufcount].x==hArr[i].x)
                        hArr[i].dead=true;
                }
                if(fire[y].y==hArr[i].y && fire[y].x==hArr[i].x)
                    hArr[i].dead=true;
            }
            bufcount++;
        }
        for(int i=0;i<yl;i++){
            f[i][xl]='|';
        }
        for (auto str: f) {
            cout << str << endl;
        }
        cout<<string(xl+1,'-')<<endl;
        cout<<"Predators:"<<pcount<<"  Herbivore:"<<hcount<<"  Trava rec:"<<tcount1<<"  Trava not rec:"<<tcount2<<"  Step:"<<mainCount<<endl;
        if(pcount==0)
            n+=20;
        if(hcount==0)
            n1+=20;
        sleep(1);
        clear();
    }
}
