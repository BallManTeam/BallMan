#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

struct shape
{
  struct b2Vec2 *vertices;
  int vertexCount;
};

struct ellipse
{
  float a;
  float b;
};

struct ellipse relps(void);
struct b2Vec2 inrpt(float,float,float,float);

int earthen(struct shape *shape_pt)
{
  float shift = visibleSize.width;
  char end = 0;
  nshapes = 1;      //number of shapes

  struct ellipse e;
  struct shape shapes[6];

  srand(time(NULL));

  int i = 0; //iterator - shapes
  int j = 0; //iterator - vertices
  int k = 0; //iterator gp
  int n = 0;

  e = relps();
  n = rand()%2 + 2;
  (shapes+i)->vertices = (struct b2Vec2*) malloc(sizeof(struct b2Vec2)+(n+2)*sizeof(struct b2Vec2));
  ((shapes+i)->vertices+j)->x = visibleSize.width; 
  ((shapes+i)->vertices+j)->y = e.b;

  for(j=1;j<=n;++j)
  {
    *((shapes+i)->vertices+j) = inrpt(e.a,e.b,visibleSize.width-j*e.a/(n+1),shift);
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
      (shapes+i)->vertices = (struct b2Vec2*) malloc(sizeof(struct b2Vec2)+(n+3)*sizeof(struct b2Vec2));
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
      (shapes+i)->vertices = (struct b2Vec2*) malloc(sizeof(struct b2Vec2)+(n+2)*sizeof(struct b2Vec2));
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
 
  shape = &shapes[0];
  return nshapes;
}

struct b2Vec2 inrpt(float a,float b,float x, float shift)
{
  struct b2Vec2 pt;
  
  pt.x = x;
  pt.y = b*sqrtf(1-((x-shift)/a)*((x-shift)/a));


  return(pt);
}

struct ellipse relps(void)
{
  struct ellipse e;

  srand(time(NULL));
  e.b = (rand()+1)/( (float) RAND_MAX+1)*visibleSize.height/2.5f; // the division by 2 needs tweaking
  e.a = (rand()+1)/( (float) RAND_MAX+1)*visibleSize.width/2.5f;

  if(e.a < visibleSize.width/6 )
  {
    e.a = visibleSize.width/6;
  }
  if(e.b < visibleSize.height/6 )
  {
    e.b = visibleSize.height/6;
  }
  return e;
}
