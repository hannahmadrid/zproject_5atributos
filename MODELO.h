//comparación de dos objetos, modelo de julio

//#ifndef _MODELO_H_
#define _MODELO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//definición de constantes
int Natr = 5;  //4 número de atributos //dinamico


//funciones
float negacion(float x)  // ¬
{
  float y;

  if(x>1 || x<0)
  { printf("\n Error 1"); getchar(); y=10; }
  else
  { y=1-x; }

  return y;
}


float conjuncion(float x,float y)  // ^
{
  float z;

  if(x>1 || x<0 || y>1 || y<0)
  { printf("\n Error 2"); getchar(); z=10; }
  else
  {
    //mínimo
    if(x<y)
    { z=x; }
    else
    { z=y; }
  }

  return z;
}


float conjuncion1(float x,float y,float lambda)  // ^ 1
{
  float acum,inv_lambda,conj;

  acum=pow(x,lambda)+pow(y,lambda)-1;

  if(acum<=0)
  { conj=0; }
  else
  {
    inv_lambda=1/lambda;
    conj=pow(acum,inv_lambda);
  }

  return conj;
}


float conjuncion2(float x[Natr],float ro)  // ^ 2
{
  float acum,inv_ro,conj;
  int i;

  acum=0;

  for(i=0;i<Natr;i++)
  { acum=acum+pow(x[i],ro); }

  acum=acum/Natr;
  inv_ro=1/ro;

  conj=pow(acum,inv_ro);

  if(conj>1)
  { conj=1; }

  if(conj<0)
  { conj=0; }

  return conj;
}


float conjuncion2_2(float x[2],float ro)  // ^ 2
{
  float acum,inv_ro,conj;
  int i;

  acum=0;

  for(i=0;i<2;i++)
  { acum=acum+pow(x[i],ro); }

  acum=acum/2;
  inv_ro=1/ro;

  conj=pow(acum,inv_ro);

  if(conj>1)
  { conj=1; }

  if(conj<0)
  { conj=0; }

  return conj;
}


float conjuncion2_3(float x[3],float ro)  // ^ 2
{
  float acum,inv_ro,conj;
  int i;

  acum=0;

  for(i=0;i<3;i++)
  { acum=acum+pow(x[i],ro); }

  acum=acum/3;
  inv_ro=1/ro;

  conj=pow(acum,inv_ro);

  if(conj>1)
  { conj=1; }

  if(conj<0)
  { conj=0; }

  return conj;
}


float disyuncion(float x,float y)  // V
{
  float z;

  if(x>1 || x<0 || y>1 || y<0)
  { printf("\n Error 2"); getchar(); y=10; }
  else
  {
    //máximo
    if(x<y)
    { z=y; }
    else
    { z=x; }
  }

  return z;
}


float disyuncion1(float x,float y,float lambda)  // V 1
{
  float inv_lambda,acum,s1,s2,max,disy;

  s1=pow(1-x,lambda);

  s2=pow(1-y,lambda);

  acum=s1+s2-1;

  if(acum<=0)
  { disy=1; }
  else
  {
    max=acum;
    inv_lambda=1/lambda;
    disy=1-pow(max,inv_lambda);
  }

  return disy;
}


float disyuncion2(float x[Natr],float p)  // V 2
{
  float acum,inv_p,disy;
  int i;

  acum=0;

  for(i=0;i<Natr;i++)
  { acum=acum + pow(1-x[i],p); }

  acum=acum/Natr;
  inv_p=1/p;

  disy=1-pow(acum,inv_p);

  if(disy>1)
  { disy=1; }

  if(disy<0)
  { disy=0; }

  return disy;
}


float disyuncion2_2(float x[2],float p)  // V 2
{
  float acum,inv_p,disy;
  int i;

  acum=0;

  for(i=0;i<2;i++)
  { acum=acum+pow(1-x[i],p); }

  acum=acum/2;
  inv_p=1/p;

  disy=1-pow(acum,inv_p);

  if(disy>1)
  { disy=1; }

  if(disy<0)
  { disy=0; }

  return disy;
}


// 4.2.1 Pertenencia de criterios a las coaliciones (tesis)

float favor(float x,float y,float q,float p)  // m(Cfavor)  Ec 4.1 tesis
{
  float z;

  if((x-y)<q)
  { z=0; }

  if((x-y)>p)
  { z=1; }

  if((x-y)>=q && (x-y)<=p)
  { z = (x-y-q)/(p-q); }

  return z;
}


float indif(float x,float y,float q,float p)  // m(Cindif)  Ec 4.2 tesis
{
  float z;

  if(fabs(x-y)>=p)
  { z=0; }

  if(fabs(x-y)<=q)
  { z=1; }

  if(fabs(x-y)<p && fabs(x-y)>q)
  { z = (p-fabs(x-y))/(p-q); }

  return z;
}


float contra(float x,float y,float q,float p)  //  m(Ccontra)  Ec 4.3 tesis
{
  float z;

  if((y-x)>=p)
  { z=1; }

  if((y-x)<=q)
  { z=0; }

  if((y-x)<p && (y-x)>q)
  { z = (y-x-q)/(p-q); }

  return z;
}


float favor_int(float x,float y,float s,float r)  // m(Cfavor_int)  Ec 4.4 tesis    //*************intensamente a favor
{
  float z;

  if((x-y)<=s)
  { z=0; }

  if((x-y)>=r)
  { z=1; }

  if((x-y)>s && (x-y)<r)
  { z = (x-y-s)/(r-s); }

  return z;
}


float contra_int(float x,float y,float s,float r)  // m(Ccontra_int)  Ec 4.5 tesis   //*************intensamente en contra
{
  float z;

  if((y-x)>=r)
  { z=1; }

  if((y-x)<=s)
  { z=0; }

  if((y-x)<r && (y-x)>s)
  { z = (y-x-s)/(r-s); }

  return z;
}


float veto(float x,float y,float r,float v)  // m(Cveto  Ec 4.6 tesis
{
  float z;

  if((y-x)>=v)
  { z=1; }

  if((y-x)<=r)
  { z=0; }

  if((y-x)<v && (y-x)>r)
  { z = (y-x-r)/(v-r); }

  return z;
}


float dict(float x,float y,float r,float d)  // m(Cdict)  Ec 4.7 tesis
{
  float z;

  if((x-y)<=r)
  { z=0; }

  if((x-y)>=d)
  { z=1; }

  if((x-y)>r && (x-y)<d)
  { z = (x-y-r)/(d-r); }

  return z;
}


// 4.3 Índices de fuerza de las coaliciones (tesis)

float ind_pref_favor(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr])  // J +  Ec 4.8 tesis
{
  float z,m,acum;
  int i;

  acum=0;
  for(i=0;i<Natr;i++)
  {
    m=favor(a[i],b[i],q[i],p[i]);
    acum=acum+(m*w[i]);
  }
  z=acum;

  return z;
}


float ind_indif(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr])  // J=  Ec 4.9 tesis

{
  float z,m,acum;
  int i;

  acum=0;
  for(i=0;i<Natr;i++)
  {
    m=indif(a[i],b[i],q[i],p[i]);
    acum=acum+(m*w[i]);
  }
  z=acum;

  return z;
}


float ind_pref_contra(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr])  // J-  Ec 4.10 tesis
{
  float z,m,acum;
  int i;

  acum=0;
  for(i=0;i<Natr;i++)
  {
    m=contra(a[i],b[i],q[i],p[i]);
    acum=acum+(m*w[i]);
  }
  z=acum;

  return z;
}


float ind_pref_int_favor(float a[Natr],float b[Natr],float w[Natr],float s[Natr],float r[Natr])  // J+ int  Ec 4.11 tesis
{
  float z,m,acum;
  int i;

  acum=0;
  for(i=0;i<Natr;i++)
  {
    m=favor_int(a[i],b[i],s[i],r[i]);
    acum=acum+(m*w[i]);
  }
  z=acum;

  return z;
}


float ind_pref_int_contra(float a[Natr],float b[Natr],float w[Natr],float s[Natr],float r[Natr])  // J- int  Ec 4.12 tesis
{
  float z,m,acum;
  int i;

  acum=0;
  for(i=0;i<Natr;i++)
  {
    m=contra_int(a[i],b[i],s[i],r[i]);
    acum=acum+(m*w[i]);
  }
  z=acum;

  return z;
}


float ind_veto(float a[Natr],float b[Natr],float r[Natr],float v[Natr],float lambda)  // I veto  Ec 4.13 tesis
{
  float z,x,y;
  int i;

  x = veto(a[0],b[0],r[0],v[0]);
  for(i=1;i<Natr;i++)
  {
    y=veto(a[i],b[i],r[i],v[i]);
    x=disyuncion1(x,y,lambda);         //////***********porque utiliza esta disyunción
  }
  z=x;

  return z;
}


float ind_dict(float a[Natr],float b[Natr],float r[Natr],float d[Natr],float ro)  // I dict  Ec 4.14 tesis
{
  float z,x[Natr];
  int i;

  for(i=0;i<Natr;i++)
  { x[i] = dict(a[i],b[i],r[i],d[i]); }

  z=disyuncion2(x,ro);

  return z;
}



// 4.4 Modelado de las comparaciones entre índices de fuerza (tesis)

float claramente_menor(float x,float y,float gamma,float delta)  // m<<  Ec 4.15 tesis
{
  float z,w,m;

  m=(gamma+delta)/2;

  if((y-x)<=gamma)
  { z=0; }

  if((y-x)>=delta)
  { z=1; }

  if((y-x)>gamma && (y-x)<=m)
  {
    w=(x-y+gamma)/(gamma-delta);
    z=2*pow(w,2);
  }

  if((y-x)>m && (y-x)<delta)
  {
    w=(x-y+delta)/(gamma-delta);
    z=1-(2*pow(w,2));
  }

  return z;
}


float menor_que(float x,float y,float alfa,float beta)  // m<  Ec 4.16 tesis
{
  float z,w,m;

  m=(alfa+beta)/2;

  if((y-x)<=alfa)
  { z=0; }

  if((y-x)>=beta)
  { z=1; }

  if((y-x)>alfa && (y-x)<=m)
  {
    w=(x-y+alfa)/(alfa-beta);
    z=2*pow(w,2);
  }

  if((y-x)>m && (y-x)<beta)
  {
    w=(x-y+beta)/(alfa-beta);
    z=1-(2*pow(w,2));
  }

  return z;
}


float parecido_a(float x,float y,float alfa,float beta)  // m~  Ec 4.17 tesis
{
  float z,w,m;

  m=(alfa+beta)/2;

  if(fabs(x-y)<=alfa)
  { z=1; }

  if(fabs(x-y)>=beta)
  { z=0; }

  if(fabs(x-y)>alfa && fabs(x-y)<=m)
  {
    w=(fabs(x-y)-alfa)/(beta-alfa);
    z=1-2*pow(w,2);
  }

  if(fabs(x-y)>m && fabs(x-y)<beta)
  {
    w=(fabs(x-y)-beta)/(beta-alfa);
    z=2*pow(w,2);
  }

  return z;
}


float algo_mayor_que(float x,float y,float alfa,float beta)  // m>~  Ec 4.18 tesis
{
  float z,w,m,n,o;

  m=(alfa+beta)/2;

  n=(beta+m)/2;

  o=(alfa+m)/2;

  if((x-y)==m)
  { z=1; }

  if((x-y)<=alfa || (x-y)>=beta)
  { z=0; }

  if((x-y)>alfa && (x-y)<=o)
  {
    w=(x-y-alfa)/(m-alfa);
    z=2*pow(w,2);
  }

  if((x-y)>n && (x-y)<beta)
  {
    w=(x-y-beta)/(beta-m);
    z=2*pow(w,2);
  }

  if((x-y)>o && (x-y)<m)
  {
    w=(x-y-m)/(m-alfa);
    z=1-2*pow(w,2);
  }

  if((x-y)>m && (x-y)<=n)
  {
    w=(x-y-m)/(beta-m);
    z=1-2*pow(w,2);
  }

  return z;
}


float mayor_que(float x,float y,float alfa,float beta)  // m>  Ec 4.19 tesis
{
  float z,w,m;

  m=(alfa+beta)/2;

  if((x-y)<=alfa)
  { z=0; }

  if((x-y)>=beta)
  { z=1; }

  if((x-y)>alfa && (x-y)<=m)
  {
    w=(x-y-alfa)/(beta-alfa);
    z=2*pow(w,2);
  }

  if((x-y)>m && (x-y)<beta)
  {
    w=(x-y-beta)/(beta-alfa);
    z=1-2*pow(w,2);
  }

  return z;
}


float claramente_mayor(float x,float y,float gamma,float delta)  // m>>  Ec 4.20 tesis
{
  float z,w,m;

  m=(gamma+delta)/2;

  if((x-y)<=gamma)
  { z=0; }

  if((x-y)>=delta)
  { z=1; }

  if((x-y)>gamma && (x-y)<=m)
  {
    w=(x-y-gamma)/(delta-gamma);
    z=2*pow(w,2);
  }

  if((x-y)>m && (x-y)<delta)
  {
    w=(x-y-delta)/(delta-gamma);
    z=1-2*pow(w,2);
  }

  return z;
}


float signif(float x,float epsilon,float zita)  // m signif  Ec 4.21 tesis
{
  float z,w,m;

  m=(epsilon+zita)/2;

  if(x<=epsilon)
  { z=0; }

  if(x>=zita)
  { z=1; }

  if(x>epsilon && x<=m)
  {
    w=(x-epsilon)/(zita-epsilon);
    z=2*pow(w,2);
  }

  if(x>m && x<zita)
  {
    w=(x-zita)/(zita-epsilon);
    z=1-2*pow(w,2);
  }

  return z;
}



// 4.5 Cálculo de índices de credibilidad (tesis)


// 4.5.1 Cálculo del índice de credibilidad de la relación de preferencia estricta P (tesis)

//*****************4.22

float m_p1(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr],float s[Natr],float r[Natr],float alfa,float beta,float epsilon,float zita,float ro) //  Ec 4.23 tesis
{
  float p_favor,p_contra,p_int_favor,p_int_contra,m_mayor1,m_mayor2,m_signif,disy,neg,conj,z,c[2],d[2];

  p_favor=ind_pref_favor(a,b,q,p,w); // J+

  p_contra=ind_pref_contra(a,b,q,p,w); // J-

  p_int_favor=ind_pref_int_favor(a,b,w,s,r); // J+ int

  p_int_contra=ind_pref_int_contra(a,b,w,s,r); // J- int

  m_mayor1=mayor_que(p_favor,p_contra,alfa,beta); // m>(J+,J-)

  m_mayor2=mayor_que(p_int_contra,p_int_favor,alfa,beta); // m>(J- int,J+ int)

  m_signif=signif(p_contra,epsilon,zita); // m signif(J-)

  d[0]=m_mayor2;
  d[1]=m_signif;

  disy=disyuncion2_2(d,ro); // m>(J- int,J+ int) V m signif(J-)

  neg=negacion(disy); // ¬ [ m>(J- int,J+ int) V m signif(J-) ]

  c[0]=m_mayor1;
  c[1]=neg;

  conj=conjuncion2_2(c,ro); //  m>(J+,J-) ^ ¬ [ m>(J- int,J+ int) V m signif(J-) ]

  z=conj;

  return z;
}


float m_p2(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr],float s[Natr],float r[Natr],float gamma,float delta,float ro) //  Ec 4.24 tesis
{
  float p_favor,p_contra,p_int_favor,p_int_contra,m_c_mayor1,m_c_mayor2,neg,conj,z,c[2];

  p_favor=ind_pref_favor(a,b,q,p,w); // J+

  p_contra=ind_pref_contra(a,b,q,p,w); // J-

  p_int_favor=ind_pref_int_favor(a,b,w,s,r); // J+ int

  p_int_contra=ind_pref_int_contra(a,b,w,s,r); // J- int

  m_c_mayor1=claramente_mayor(p_favor,p_contra,gamma,delta); // m>>(J+,J-)

  m_c_mayor2=claramente_mayor(p_int_contra,p_int_favor,gamma,delta); // m>>(J- int,J+ int)

  neg=negacion(m_c_mayor2); //  ¬ [ m>>(J- int,J+ int) ]

  c[0]=m_c_mayor1;
  c[1]=neg;

  conj=conjuncion2_2(c,ro); //  m>>(J+,J-) ^ ¬ [ m>>(J- int,J+ int) ]

  z=conj;

  return z;
}


float m_p3(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr],float s[Natr],float r[Natr],float alfa,float beta,float epsilon,float zita,float ro) // Ec 4.25 tesis
{
  float p_favor,p_contra,p_int_favor,p_int_contra,p_indif,m_mayor1,m_mayor2,m_signif,disy,neg,conj,z,c[2],d[2];

  p_favor=ind_pref_favor(a,b,q,p,w); // J+

  p_contra=ind_pref_contra(a,b,q,p,w); // J-

  p_int_favor=ind_pref_int_favor(a,b,w,s,r); // J+ int

  p_int_contra=ind_pref_int_contra(a,b,w,s,r); // J- int

  p_indif=ind_indif(a,b,q,p,w); // J=

  m_mayor1=mayor_que(p_int_favor,p_int_contra,alfa,beta); // m>(J+ int,J- int)

  m_mayor2=mayor_que(p_contra,p_favor,alfa,beta); // m>(J-,J+)

  m_signif=signif(p_indif,epsilon,zita); // m signif(J=)

  d[0]=m_mayor2;
  d[1]=m_signif;

  disy=disyuncion2_2(d,ro); // m>(J-,J+) V m signif(J=)

  neg=negacion(disy); // ¬ [ m>(J-,J+) V m signif(J=) ]

  c[0]=m_mayor1;
  c[1]=neg;

  conj=conjuncion2_2(c,ro); // m>(J+ int,J- int) ^ ¬ [ m>(J-,J+) V m signif(J=) ]

  z=conj;

  return z;
}


float m_p4(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr],float s[Natr],float r[Natr],float gamma,float delta,float ro) // Ec 4.26 tesis
{
  float p_favor,p_contra,p_int_favor,p_int_contra,m_c_mayor1,m_c_mayor2,neg,conj,z,c[2];


  p_favor=ind_pref_favor(a,b,q,p,w); // J+

  p_contra=ind_pref_contra(a,b,q,p,w); // J-

  p_int_favor=ind_pref_int_favor(a,b,w,s,r); // J+ int

  p_int_contra=ind_pref_int_contra(a,b,w,s,r); // J- int

  m_c_mayor1=claramente_mayor(p_int_favor,p_int_contra,gamma,delta); // m>>(J+ int,J- int)

  m_c_mayor2=claramente_mayor(p_contra,p_favor,gamma,delta); // m>>(J-,J+)

  neg=negacion(m_c_mayor2); // ¬ [ m>>(J-,J+) ]

  c[0]=m_c_mayor1;
  c[1]=neg;

  conj=conjuncion2_2(c,ro); // m>>(J+ int,J- int) ^ ¬ [ m>>(J-,J+) ]

  z=conj;

  return z;
}


float m_p5(float a[Natr],float b[Natr],float r[Natr],float d[Natr],float ro) // Ec 4.27 tesis
{
  float p_dict,z;

  p_dict=0;

  p_dict=ind_dict(a,b,r,d,ro);  // I dict

  z=p_dict;

  return z;
}


// 4.5.2 Cálculo del índice de credibilidad de la relación de indiferencia I

float m_i1(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr],float s[Natr],float r[Natr],float alfa,float beta,float epsilon,float zita,float ro) // Ec 4.29 tesis
{
  float p_favor,p_contra,p_int_favor,p_int_contra,p_indif,conj,m_signif,m_parecido1,m_parecido2,z,c[3];

  p_favor=ind_pref_favor(a,b,q,p,w); // J+

  p_contra=ind_pref_contra(a,b,q,p,w); // J-

  p_int_favor=ind_pref_int_favor(a,b,w,s,r); // J+ int

  p_int_contra=ind_pref_int_contra(a,b,w,s,r); // J- int

  p_indif=ind_indif(a,b,q,p,w); // J=

  m_parecido1=parecido_a(p_favor,p_contra,alfa,beta); // m~(J+,J-)

  m_parecido2=parecido_a(p_int_favor,p_int_contra,alfa,beta); // m~(J+ int,J- int)

  m_signif=signif(p_indif,epsilon,zita); // m signif(J=)

  c[0]=m_parecido1;
  c[1]=m_parecido2;
  c[2]=m_signif;

  conj=conjuncion2_3(c,ro); // m~(J+,J-) ^ m~(J+ int,J- int) ^ m signif(J=)

  z=conj;

  return z;
}


float m_i2(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr],float s[Natr],float r[Natr],float alfa,float beta,float epsilon,float zita,float ro) // Ec 4.30 tesis
{
  float p_favor,p_contra,p_int_favor,p_int_contra,p_indif,conj,m_signif,m_algo_mayor1,m_algo_mayor2,z,c[3];


  p_favor=ind_pref_favor(a,b,q,p,w); // J+

  p_contra=ind_pref_contra(a,b,q,p,w); // J-

  p_int_favor=ind_pref_int_favor(a,b,w,s,r); // J+ int

  p_int_contra=ind_pref_int_contra(a,b,w,s,r); // J- int

  p_indif=ind_indif(a,b,q,p,w); // J=yum install -y epel-release

  m_algo_mayor1=algo_mayor_que(p_favor,p_contra,alfa,beta); // m>~(J+,J-)

  m_algo_mayor2=algo_mayor_que(p_int_contra,p_int_favor,alfa,beta); // m>~(J- int,J+ int)

  m_signif=signif(p_indif,epsilon,zita); // m signif(J=)

  c[0]=m_algo_mayor1;
  c[1]=m_algo_mayor2;
  c[2]=m_signif;

  conj=conjuncion2_3(c,ro); // m>~(J+,J-) ^ m>~(J- int,J+ int) ^ m signif(J=)

  z=conj;

  return z;
}


float m_i3(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr],float s[Natr],float r[Natr],float alfa,float beta,float epsilon,float zita,float ro) // Ec 4.31 tesis
{
  float p_favor,p_contra,p_int_favor,p_int_contra,p_indif,conj,m_signif,m_algo_mayor1,m_algo_mayor2,z,c[3];

  p_favor=ind_pref_favor(a,b,q,p,w); // J+

  p_contra=ind_pref_contra(a,b,q,p,w); // J-

  p_int_favor=ind_pref_int_favor(a,b,w,s,r); // J+ int

  p_int_contra=ind_pref_int_contra(a,b,w,s,r); // J- int

  p_indif=ind_indif(a,b,q,p,w); // J=

  m_algo_mayor1=algo_mayor_que(p_contra,p_favor,alfa,beta); // m>~(J-,J+)

  m_algo_mayor2=algo_mayor_que(p_int_favor,p_int_contra,alfa,beta); // m>~(J+ int,J- int)

  m_signif=signif(p_indif,epsilon,zita); // m signif(J=)

  c[0]=m_algo_mayor1;
  c[1]=m_algo_mayor2;
  c[2]=m_signif;

  conj=conjuncion2_3(c,ro); // // m>~(J-,J+) ^ m>~(J+ int,J- int) ^ m signif(J=)

  z=conj;

  return z;
}


float m_i4(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr],float s[Natr],float r[Natr],float gamma,float delta,float epsilon,float zita,float ro) // Ec 4.32 tesis
{
  float p_int_favor,p_int_contra,p_indif,m_signif,m_c_mayor1,m_c_mayor2,neg,conj,disy,z,c[2],d[2];


  p_int_favor=ind_pref_int_favor(a,b,w,s,r); // J+ int

  p_int_contra=ind_pref_int_contra(a,b,w,s,r); // J- int

  p_indif=ind_indif(a,b,q,p,w); // J=

  m_signif=signif(p_indif,epsilon,zita); // m signif(J=)

  m_c_mayor1=claramente_mayor(p_int_favor,p_int_contra,gamma,delta); // m>>(J+ int,J- int)

  m_c_mayor2=claramente_mayor(p_int_contra,p_int_favor,gamma,delta); // m>>(J- int,J+ int)

  d[0]=m_c_mayor1;
  d[1]=m_c_mayor2;

  disy=disyuncion2_2(d,ro); // m>>(J+ int,J- int) V m>>(J- int,J+ int)

  neg=negacion(disy); // ¬ [ m>>(J+ int,J- int) V m>>(J- int,J+ int) ]

  c[0]=m_signif;
  c[1]=neg;

  conj=conjuncion2_2(c,ro); // m signif(J=) ^ ¬ [ m>>(J+ int,J- int) V m>>(J- int,J+ int) ]

  z=conj;

  return z;
}


float sigma_aPb(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr],float s[Natr],float r[Natr],float v[Natr],float d[Natr],float alfa,float beta,float gamma,float delta,float epsilon,float zita,float lambda,float ro) // Ec 4.22 tesis
{
  float mp1,mp2,mp3,mp4,mp5,iveto,disy,neg,conj,z;

  mp1=m_p1(a,b,q,p,w,s,r,alfa,beta,epsilon,zita,ro);

  mp2=m_p2(a,b,q,p,w,s,r,gamma,delta,ro);

  mp3=m_p3(a,b,q,p,w,s,r,alfa,beta,epsilon,zita,ro);

  mp4=m_p4(a,b,q,p,w,s,r,gamma,delta,ro);

  mp5=m_p5(a,b,r,d,ro);

  iveto=ind_veto(a,b,r,v,lambda);

  neg=negacion(iveto);

  disy=disyuncion1(mp1,mp2,lambda); // mp1(a,b) V mp2(a,b)

  disy=disyuncion1(disy,mp3,lambda); // mp1(a,b) V mp2(a,b) V mp3(a,b)

  disy=disyuncion1(disy,mp4,lambda); // mp1(a,b) V mp2(a,b) V mp3(a,b) V mp4(a,b)

  disy=disyuncion1(disy,mp5,lambda); // mp1(a,b) V mp2(a,b) V mp3(a,b) V mp4(a,b) V mp5(a,b)

  conj=conjuncion1(disy,neg,lambda); // [ mp1(a,b) V mp2(a,b) V mp3(a,b) V mp4(a,b) V mp5(a,b) ] ^ ¬ iveto(a,b)

  z=conj;

  return z;
}


float sigma_aIb(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr],float s[Natr],float r[Natr],float v[Natr],float d[Natr],float alfa,float beta,float gamma,float delta,float epsilon,float zita,float lambda,float ro) // Ec 4.28 tesis
{
  float mi1,mi2,mi3,mi4,disy1,disy2,iveto,idict,neg,conj,z;


  mi1=m_i1(a,b,q,p,w,s,r,alfa,beta,epsilon,zita,ro);

  mi2=m_i2(a,b,q,p,w,s,r,alfa,beta,epsilon,zita,ro);

  mi3=m_i3(a,b,q,p,w,s,r,alfa,beta,epsilon,zita,ro);

  mi4=m_i4(a,b,q,p,w,s,r,gamma,delta,epsilon,zita,ro);

  iveto=ind_veto(a,b,r,v,lambda);

  idict=ind_dict(a,b,r,d,ro);

  disy1=disyuncion1(iveto,idict,lambda);

  neg=negacion(disy1);

  disy2=disyuncion1(mi1,mi2,lambda);

  disy2=disyuncion1(disy2,mi3,lambda);

  disy2=disyuncion1(disy2,mi4,lambda);

  conj=conjuncion1(disy2,neg,lambda);

  z=conj;

  return z;
}


// 4.5.3 Cálculo del índice de credibilidad de la relación de preferencia débil Q

float sigma_aQb(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr],float s[Natr],float r[Natr],float v[Natr],float d[Natr],float alfa,float beta,float gamma,float delta,float epsilon,float zita,float lambda,float ro) // Ec 4.33 tesis
{
  float aPb,bPa,aIb,conj,m_parecido1,m_parecido2,m_parecido3,z;

  aPb=sigma_aPb(a,b,q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);

  bPa=sigma_aPb(b,a,q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);

  aIb=sigma_aIb(a,b,q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);

  m_parecido1=parecido_a(aPb,0.5,alfa,beta);

  m_parecido2=parecido_a(aIb,0.5,alfa,beta);

  m_parecido3=parecido_a(bPa,0.0,alfa,beta);

  conj=conjuncion1(m_parecido1,m_parecido2,lambda);

  conj=conjuncion1(conj,m_parecido3,lambda);

  z=conj;

  return z;
}


// 4.5.4 Cálculo del índice de credibilidad de la relación de incomparabilidad R

float sigma_aRb(float a[Natr],float b[Natr],float q[Natr],float p[Natr],float w[Natr],float s[Natr],float r[Natr],float v[Natr],float d[Natr],float alfa,float beta,float gamma,float delta,float epsilon,float zita,float lambda,float ro) // Ec 4.34 tesis
{
  float aPb,aIb,aQb,bPa,bQa,m_parecido1,m_parecido2,m_parecido3,m_parecido4,m_parecido5,conj,z;


  aPb=sigma_aPb(a,b,q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);

  aIb=sigma_aIb(a,b,q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);

  aQb=sigma_aQb(a,b,q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);

  bPa=sigma_aPb(b,a,q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);

  bQa=sigma_aQb(b,a,q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);

  m_parecido1=parecido_a(aPb,0.0,alfa,beta);

  m_parecido2=parecido_a(aIb,0.0,alfa,beta);

  m_parecido3=parecido_a(aQb,0.0,alfa,beta);

  m_parecido4=parecido_a(bPa,0.0,alfa,beta);

  m_parecido5=parecido_a(bQa,0.0,alfa,beta);

  conj=conjuncion1(m_parecido1,m_parecido2,lambda);

  conj=conjuncion1(conj,m_parecido3,lambda);

  conj=conjuncion1(conj,m_parecido4,lambda);

  conj=conjuncion1(conj,m_parecido5,lambda);

  z=conj;

  return z;
}
