#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int N = 50, M = 50;
int size = 16;
int w = size*N;
int h = size*M;
int dir = 4;
int score = 0;
int lscore =-10;
int level = 0;
int num = 10;
int pn = 0;
int Game = 0;
float Delay = 0.1;
char Mode = 'N';
float GbotSpeed = 0.1;


struct Drifter{
int x=10,y=10;
}D;

struct Photon{
int x,y,z;
}P[4];

struct GreenBot{
int x,y,z;
}G[100];

void iflevel(){
    if(score-lscore==10){level++;lscore=score;num=num+2;
     cout<<"test"<<endl;
    for(int i=0;i<num;i++){G[i].x=rand()%N; G[i].y=rand()%M;}}
}


void instance(){

    if (dir==0) D.y+=1;
    if (dir==1) D.x-=1;
    if (dir==2) D.x+=1;
    if (dir==3) D.y-=1;

    if (D.x>N) D.x=0;  if (D.x<0) D.x=N;
    if (D.y>M) D.y=0;  if (D.y<0) D.y=M;

    for (int i=0;i<num;i++)
    {for (int j=0;j<4;j++)
    { if (D.x==G[i].x && D.y==G[i].y) { Game++;}}}

    iflevel();



}

void Accelerate(Sprite sD){
Delay=0.03;
Mode = 'A';
}

void Deccelerate(){
Delay=0.5;
cout<<GbotSpeed<<endl;
GbotSpeed = 0.5;
cout<<GbotSpeed<<endl;
Mode = 'D';
}



void photosec(){
    pn=pn%4;
    for(int i=0; i<4;i++){
    if(P[i].z==0) P[i].y+=1;
    if(P[i].z==1) P[i].x-=1;
    if(P[i].z==2) P[i].x+=1;
    if(P[i].z==3) P[i].y-=1;
    }

    for (int i=0; i<4; i++){
        for (int j=0; j<num; j++){
            if(P[i].x==G[j].x&&P[i].y==G[j].y){score++; G[j].x=N+1; G[j].y=M+1;}
            }}
}

void Gbotsec(){

for(int i=0;i<num;i++){
    G[i].z=rand()%4;
    if (G[i].z==0) {G[i].y+=1;}
    if (G[i].z==1) {G[i].x-=1;}
    if (G[i].z==2) {G[i].x+=1;}
    if (G[i].z==3) {G[i].y-=1;}

    if (G[i].x>N) {G[i].x=0;}  if (G[i].x<0) {G[i].x=N;}
    if (G[i].y>M) {G[i].y=0;}  if (G[i].y<0) {G[i].y=M;}
    }



}


int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(w, h), "SpaceDrift");


    Texture bg,D0,P0,G0,D1,D2;
    bg.loadFromFile("/home/xenosblue/Pictures/space000.png");
    P0.loadFromFile("/home/xenosblue/Pictures/white.png");
    D0.loadFromFile("/home/xenosblue/Pictures/white.png");
    G0.loadFromFile("/home/xenosblue/Pictures/green.png");
    D1.loadFromFile("/home/xenosblue/Pictures/red.png");
    D2.loadFromFile("/home/xenosblue/Pictures/blue.png");

    Sprite BG(bg);
    Sprite sD(D0);
    Sprite sD1(D1);
    Sprite sD2(D2);
    Sprite sP(P0);
    Sprite sG(G0);



    Clock clock;
    float timer=0, delay=0.1, PhotonTimer=0, PhotonSpeed=0.01, GbotTimer=0, GbotSpeed=0.3;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        PhotonTimer+=time;
        GbotTimer+=time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {window.close();}
            if(Game==1){window.close();}
        }


        if (Keyboard::isKeyPressed(Keyboard::Left)&&dir==1) { P[pn].x=D.x; P[pn].y=D.y; P[pn].z=dir;pn++;}
        if (Keyboard::isKeyPressed(Keyboard::Right)&&dir==2){ P[pn].x=D.x; P[pn].y=D.y; P[pn].z=dir;pn++;}
        if (Keyboard::isKeyPressed(Keyboard::Up)&&dir==3)   { P[pn].x=D.x; P[pn].y=D.y; P[pn].z=dir;pn++;}
        if (Keyboard::isKeyPressed(Keyboard::Down)&&dir==4) { P[pn].x=D.x; P[pn].y=D.y; P[pn].z=dir;pn++;}


        if (Keyboard::isKeyPressed(Keyboard::Left))  dir=1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir=2;
        if (Keyboard::isKeyPressed(Keyboard::Up))    dir=3;
        if (Keyboard::isKeyPressed(Keyboard::Down))  dir=0;


        if (Keyboard::isKeyPressed(Keyboard::A))  Accelerate(sD);
        if (Keyboard::isKeyPressed(Keyboard::D))  Deccelerate();


        if(timer>Delay){timer=0;instance();}
        if(PhotonTimer>PhotonSpeed){PhotonTimer=0;photosec();}
        if(GbotTimer>GbotSpeed){GbotTimer=0;Gbotsec();}


        window.clear();

        for (int i=0; i<N; i++){
        for (int j=0; j<M; j++)
        { BG.setPosition(i*size, j*size);  window.draw(BG); }}

        if(Mode=='A'){sD1.setPosition(D.x*size, D.y*size);window.draw(sD1);}
        if(Mode=='D'){sD2.setPosition(D.x*size, D.y*size);window.draw(sD2);}
        if(Mode=='N'){sD.setPosition(D.x*size, D.y*size);window.draw(sD);}

        for(int i=0; i<4; i++){
        sP.setPosition(P[i].x*size, P[i].y*size);window.draw(sP);}

        for(int i=0; i<num; i++){
        sG.setPosition(G[i].x*size, G[i].y*size);window.draw(sG);}

        window.display();
    }



//    cout << "Hello world!" << endl;
    cout << "Level Reached: " <<level<<endl;
    cout <<"The Score Is "<<score<< endl;
    return 0;
}
