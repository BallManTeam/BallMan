#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>

using namespace std;

#define WIDTH 480
#define HEIGHT 320

#include "wip.h"


struct ellipse
{
  float a;
  float b;
};

struct ellipse relps(void);
b2Vec2 inrpt(float,float,float,float);

int earthen(struct shape *&shape_pt)
{
    int nshapes;
  float shift = WIDTH;
  char end = 0;
  nshapes = 1;      //number of shapes

  struct ellipse e;
  struct shape *shapes = (struct shape *)malloc(6 * sizeof(struct shape));

  srand(time(NULL));

  int i = 0; //iterator - shapes
  int j = 0; //iterator - vertices
  int k = 0; //iterator gp
  int n = 0;

  e = relps();
  n = rand()%2 + 2;
  (shapes+i)->vertices = (b2Vec2*) malloc(sizeof(b2Vec2)+(n+2)*sizeof(b2Vec2));
  ((shapes+i)->vertices+j)->x = WIDTH; 
  ((shapes+i)->vertices+j)->y = e.b;

  for(j=1;j<=n;++j)
  {
    *((shapes+i)->vertices+j) = inrpt(e.a,e.b,WIDTH-j*e.a/(n+1),shift);
  }

  ((shapes+i)->vertices+j)->x = ((shapes+i)->vertices+j-1)->x;
  ((shapes+i)->vertices+j)->y = 0;
  ++j;
  ((shapes+i)->vertices+j)->x = (shapes+i)->vertices->x;
  ((shapes+i)->vertices+j)->y = 0;
  (shapes+i)->vertexCount = j + 1;

  shift -= e.a;
  j = 0;
  ++i;
  while(end == 0)
  {
    e = relps();
    if(shift-2*e.a<0)
    {
      end = 1;
      shift -= e.a;
      n = rand()%3 + 1;
      (shapes+i)->vertices = (b2Vec2*) malloc(sizeof(b2Vec2)+(n+3)*sizeof(b2Vec2));
      ((shapes+i)->vertices+j)->x = ((shapes+i-1)->vertices+(shapes+i-1)->vertexCount-3)->x; 
      ((shapes+i)->vertices+j)->y = ((shapes+i-1)->vertices+(shapes+i-1)->vertexCount-3)->y;

      for(j=1;j<=n;++j)
      {
        *((shapes+i)->vertices+j) = inrpt(e.a,e.b,shift+e.a-j*(shift+e.a)/(n+1),shift);
      }
      printf("sqrt is %f\n",1.0f-(shift/e.a)*(shift/e.a));
      ((shapes+i)->vertices+j)->x = 0;
      ((shapes+i)->vertices+j)->y = e.b*sqrtf(1.0f-(shift/e.a)*(shift/e.a));
      ++j;
      ((shapes+i)->vertices+j)->x = 0;
      ((shapes+i)->vertices+j)->y = 0;
      ++j;
      ((shapes+i)->vertices+j)->x = ((shapes+i)->vertices)->x;
      ((shapes+i)->vertices+j)->y = 0;
      (shapes+i)->vertexCount = j + 1;
      
      j = 0;
    }
    else
    {
      shift -= e.a;
      n = rand()%5 + 1;
      (shapes+i)->vertices = (b2Vec2*) malloc(sizeof(b2Vec2)+(n+2)*sizeof(b2Vec2));
      ((shapes+i)->vertices+j)->x = ((shapes+i-1)->vertices+(shapes+i-1)->vertexCount-3)->x; 
      ((shapes+i)->vertices+j)->y = ((shapes+i-1)->vertices+(shapes+i-1)->vertexCount-3)->y;

      for(j=1;j<=n;++j)
      {
        *((shapes+i)->vertices+j) = inrpt(e.a,e.b,shift+e.a-j*2*e.a/(n+2),shift);
      }

      ((shapes+i)->vertices+j)->x = ((shapes+i)->vertices+j-1)->x;
      ((shapes+i)->vertices+j)->y = 0;
      ++j;
      ((shapes+i)->vertices+j)->x = ((shapes+i)->vertices)->x;
      ((shapes+i)->vertices+j)->y = 0;
      (shapes+i)->vertexCount = j + 1;

      shift -= e.a;
      j = 0;
      ++i;
    }
  }
  nshapes = i+1;
 
  shape_pt = shapes;
  return nshapes;
}

b2Vec2 inrpt(float a,float b,float x, float shift)
{
  b2Vec2 pt;
  
  pt.x = x;
  pt.y = b*sqrtf(1-((x-shift)/a)*((x-shift)/a));


  return(pt);
}

struct ellipse relps(void)
{
  struct ellipse e;

  srand(time(NULL));
  e.b = (rand()+1)/( (float) RAND_MAX+1)*HEIGHT/2.5f; // the division by 2 needs tweaking
  e.a = (rand()+1)/( (float) RAND_MAX+1)*WIDTH/2.5f;

  if(e.a < WIDTH/6 )
  {
    e.a = WIDTH/6;
  }
  if(e.b < HEIGHT/6 )
  {
    e.b = HEIGHT/6;
  }
  return e;
}
