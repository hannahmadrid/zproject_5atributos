#include "MODELO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//#define N 100//5
//#define OBJ 4

//definición de constantes
int obj = 4; //número de objetivos
int n = 455;//455; //tamaño de la población
//int Natr = 4;  // número de atributos //dinamico
int Tpob = 456;//456; // tamaño de la población del AG
int Tind = 44; // tamaño del individuo ( 7*Natr + 9  )
int Tnr = 20;//50;    // tamaño del núcleo de referencia
int t = 10;//20; //tamaño del vecindario

int tnr_prueba = 100;
//int Natr = 5;  //está definido en el modelo


int moea();
int ordenar(int n, float*ord_val, int*ord_id);
float maximo(float val1, float val2, float val3, float val4);
void Pob_ini(float Pob[Tpob][Tind], int t_pob);
void generar_nr(float nr[Tnr][Natr], int Tnr, int Natr);
void weight_vectors(float lamda[n][obj]);
void distancias_euclideanas(float euc[n][n], float lamda[n][obj]);
void generar_vecindario(int b[n][t], float Pob[Tpob][Tind], float euc[n][n]);
void armar_individuo(float Pob[Tpob][Tind], float Ind[Tind], int ind);
void evaluar_individuo(float Ind[Tind], float nr[Tnr][Natr], char matriz_comp[Tnr][Tnr]);
void contar_discrepancias(char matriz_ind[Tnr][Tnr], char modelo_comp[Tnr][Tnr], int matriz_disc[n][obj], int pos);
void cruza_individuo(float Pob[Tpob][Tind], float Ind_cruza[Tind], int ind_k, int ind_l, float Pc, float nr[Tnr][Natr], char matriz_ind[Tnr][Tnr]);
void muta_ind(float I[Tind]);
int imprimir_hora();

void weight_vectors_2(float lamda[n][obj]);

/*int main(int argc, char * argv[])
{
  //use current time as seed for random generator
  //srand(time(0));

  //float a[Natr],b[Natr],sigmaaPb,sigmaaIb,sigmaaRb,sigmabPa,sigmabIa,sigmabRa,sigmaaSb, sigmabSa;
  //float q[Natr],p[Natr],s[Natr],r[Natr],d[Natr],v[Natr],w[Natr],alfa,beta,gamma,delta,epsilon,zita,ro,lambda,lambda_corte;

  //moea();

  //return 0;
}*/


//función MOEA
int main(int argc, char * argv[])
{
  //use current time as seed for random generator
  srand(time(0));

  FILE* fd;
  fd=fopen(argv[1], "wt");//Abre archivo destino

  //inicializacion de variables
  int i, j, k, l, k_, l_, ind_k, ind_l;
  int g, gen = 100;//100; //A stopping criterion
  int r, ren = 6; //reinicios //5 + 1
  //T the number of the weight vectors in the neighborhood of each weight vector

  float euc[n][n];
  float lamda[n][obj]; //tam poblacion row x num obj col
  float Pob[Tpob][Tind], Ind[Tind], Ind_cruza[Tind], Ind_real[Tind], Ind_ren[Tind];
  float z[obj];
  float nr[Tnr][Natr]; //nucleo de referencia

  float nr_prueba[tnr_prueba][Natr]; //nucleo de referencia para prueba final
  char matriz_ind_prueba[tnr_prueba][tnr_prueba];
  char modelo_comp_prueba[tnr_prueba][tnr_prueba];
  int matriz_disc_p[1][obj];

  int b[n][t];

  char d_real, d_gen; //decisor real y decisor generado, para la comparación

  //individuo cruce
  float cruza_q[obj], cruza_p[obj], cruza_s[obj], cruza_r[obj], cruza_d[obj], cruza_v[obj], cruza_w[obj];
  float cruza_alfa,cruza_beta,cruza_gamma,cruza_delta,cruza_epsilon,cruza_zita,cruza_ro,cruza_lambda,cruza_lambda_corte;
  float cruza_sigmaaPb, cruza_sigmabPa, cruza_sigmaaIb, cruza_sigmabIa, cruza_sigmaaRb, cruza_sigmabRa, cruza_sigmaaQb, cruza_sigmabQa, cruza_sigmaaSb, cruza_sigmabSa;

  //vector de discrepancias
  int disc1, disc2, disc3, disc4, conc, total_disc, t_disc; //pasar a vector
  int disc_c[1][obj];//, disc_m[4];

  //matriz de discrepancias
  int matriz_disc[n][obj];
  int p_cruce; //punto de cruce
  //matriz de comparacion para el modelo que funge como decisor (455)
  char matriz_ind[Tnr][Tnr];
  char modelo_comp[Tnr][Tnr];
  char cruza_comp[Tnr][Tnr];

  int indice_lambda;
  float gte_y, gte_y1, gte_y2, gte_y3, gte_y4;
  float gte_x, gte_x1, gte_x2, gte_x3, gte_x4;

  float aleat, Pm, Pc;

  int ind_temp, no_dom, vec_dom;

  int stop, ind_nodom;

  Pm=0.01; //Indice de mutaci�n
  Pc=0.8; //Indice de cruzamiento

  imprimir_hora();

  //valors de 0-7  o 0-10????*** porqué
  //generar el nucleo de referencia //5 atributos de momento //¿como generarlos?
  generar_nr(nr, Tnr, Natr);

  fprintf(fd, "nucleo de referencia \n");
  printf("nucleo de referencia \n");
  for(i=0; i<Tnr;i++)
  {
    for(j=0; j<Natr;j++)
    {
      printf("%f ", nr[i][j]);
      fprintf(fd, "%f ", nr[i][j]);
    }
    printf("\n");
    fprintf(fd, "\n");
  }

  printf("fin nucleo de referencia \n\n");
  fprintf(fd, "fin nucleo de referencia \n\n");



  //vectores de peso uniformemente distribuidos
  //a uniform spread of N weight vectors lamdai ... lamdaN;
  //de momento no es uniforme
  //weight_vectors(lamda);

  weight_vectors_2(lamda);


  /*printf("inicio vectores de peso uniformemente distribuidos -main\n" );
  for(i=0; i<n;i++)
  {
      printf("%f ", lamda[i][0]);
      printf("%f ", lamda[i][1]);
      printf("%f ", lamda[i][2]);
      printf("%f\n", lamda[i][3]);
  }
  printf("fin vectores de peso uniformemente distribuidos - main\n" );*/


  //Step 1 Inicialización
  //Step 1.1 inicializar EP = {0}
  int ep[n];

  //Step 1.2 Calcule las distancias euclidianas entre dos vectores de peso
  //cualesquiera y luego calcule los T vectores de peso más cercanos a cada vector de peso.
  //calcular la distancia euclideana
  distancias_euclideanas(euc, lamda);
  /*printf("inicio distancias euclideanas\n" );
  for(i=0; i<n;i++)
  {
    for(j=0; j<n;j++)
    {
      printf("%f ", euc[i][j]);
    }
    printf("\n");
  }
  printf("fin distancias euclideanas\n" );*/


  //Por cada i = 1... N, establece B(i) = {i1,...iT}, donde lamda i1, .... lamda iT son los T
  //vectores de peso mas cercanos a lamda i
  generar_vecindario(b, Pob, euc);
  /*printf("inicio vecindario\n" );
  for(i=0; i<n;i++)
  {
    for(j=0; j<t;j++)
    {
      printf("%d ", b[i][j]);
    }
    printf("\n");
  }
  printf("fin vecindario\n" );*/

  //Step 1.3 Genera una población inicial x1, ..., xN random o por un método específico del problema.

  for(r=0;r<ren;r++)
  {

  if(r==0)
  {
    //Tpob
    Pob_ini(Pob, Tpob);


  }
  else
  {
    //Pob[n][j] decisor real*
    Pob_ini(Pob, Tpob - 2);

    //poner en la penúltima posición el mejor individuo encontrado en el reinicio anterior
    for(i=0;i<Tind; i++)
    {
      Pob[n][i] = Ind_ren[i];
    }

    //poner en la última posición el decisor real
    for(i=0;i<Tind; i++)
    {
      Pob[n+1][i] = Ind_real[i];
    }
  }

  /*printf("inicio poblacion generada\n" );
  for(i=0; i<Tpob;i++)
  {
    for(j=0;j<Tind;j++)
    {
      printf("%f ",Pob[i][j] );
    }
    printf("\n");
  }
  printf("fin poblacion generada\n" );*/

  //Step 1.4 Inicializar z = (z1, ..., zm)T por un método específico del problema.

  if(r==0)
  {
    for(i=0;i<obj;i++)
    {
      z[i] = 401; //un número grande
    }
    //t_disc = n;
  }


  //imprimir al individuo 455
  /*printf("inicio individuo n\n" );
  //for(i=0; i<Tpob;i++)
  //{
    for(j=0;j<Tind;j++)
    {
      printf("%f\n",Pob[n][j] );
    }
    //printf("\n");
  //}
  printf("fin individuo n\n\n" );*/
  if(r==0)
  {
    armar_individuo(Pob, Ind_real, n);


    evaluar_individuo(Ind_real, nr, matriz_ind);
    //imprimimos la matriz de comparacion
    fprintf(fd, "inicio matriz comparacion\n");
    printf("inicio matriz comparacion\n");
    for(i=0; i<Tnr;i++)
    {
      for(j=0; j<Tnr;j++)
      {
        printf("%c ", matriz_ind[i][j]);
        fprintf(fd, "%c ", matriz_ind[i][j]);
      }
      printf("\n");
      fprintf(fd, "\n");
    }
    printf("fin matriz comparacion\n\n");
    fprintf(fd, "fin matriz comparacion\n\n");
  }


  //************inicio paso 2************************
  //vamos a mandar llamar las funciones para cada elemento de la población
  for(i=0; i<Tpob-1;i++)
  {
    armar_individuo(Pob, Ind, i);

    evaluar_individuo(Ind, nr, modelo_comp);

    /*printf("inicio matriz individuo generado\n");
    for(j=0;j<Tnr;j++)
    {
      for(k=0;k<Tnr;k++)
      {
        printf("%c ", modelo_comp[j][k]);
      }
      printf("\n");
    }
    printf("fin matriz individuo generado\n\n");*/

    //comparar matrices de comparacion
    //contar las discrepancias modelo-pda
    contar_discrepancias(matriz_ind, modelo_comp, matriz_disc, i);

    total_disc = matriz_disc[i][0] + matriz_disc[i][1] + matriz_disc[i][2] + matriz_disc[i][3];

     /*printf("disc1: %d\n",matriz_disc[i][0]);
     printf("disc2: %d\n",matriz_disc[i][1]);
     printf("disc3: %d\n",matriz_disc[i][2]);
     printf("disc4: %d\n",matriz_disc[i][3]);
     printf("total_disc: %d\n",total_disc);
     printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");*/

    }

    printf("*****************REINICIO %d**********************\n", r);
    fprintf(fd, "*****************REINICIO %d**********************\n", r);
    //ciclo de generaciones
    for(g=0;g<gen;g++)
    {
      printf("*****************GENERACION %d**********************\n", g);
      fprintf(fd, "*****************GENERACION %d**********************\n", g);

      //Step 2 Update:
      //For i = 1, ... N, do
      for(i=0;i<n;i++)
      {
        //printf("\n\ni = %d\n",i );
        //Step 2.1 Reproducción. Seleccione aleatoriamente dos índices k, l de B(i), y luego genere
        //una nueva solución y de xk y xl mediante el uso de operadores genéticos.
        do {
          k = rand() %t;
          l = rand() %t;
        } while(k==l); //asegurarse que k y l no sean iguales

        /*printf("k=%d\n",k );
        printf("l=%d\n",l );*/

        ind_k = b[i][k]; //indices
        ind_l = b[i][l]; //indices

        //printf("ind_k=%d\n",ind_k );
        //printf("ind_l=%d\n",ind_l );


        /*printf("inicio padre k \n" );
        for(j=0;j<Tind;j++)
        {
          printf("%f ",Pob[ind_k][j]);
        }
        printf("fin padre k \n\n" );*/

        //vamos a generar una nueva solucion con el vector lambda o de la poblacion...*
        cruza_individuo(Pob, Ind_cruza, ind_k, ind_l, Pc, nr, matriz_ind);  //cruza y mutación

        //imprimir individuo cruza
        /*printf("inicio individuo cruza \n" );
        for(j=0;j<Tind;j++)
        {
          printf("%f ",Ind_cruza[j]);
        }
        printf("fin individuo cruza \n\n" );*/


        //Step 2.2 Mejora: Aplique una heurística de reparación / mejora específica del problema para producir y'.
        //Mutación
        aleat=(float) (rand() % RAND_MAX)/(RAND_MAX-1);
        if(aleat<=Pm)
        {
          //printf("entro a mutar el individuo\n\n");
          /*printf("inicio individuo cruza \n" );
          for(j=0;j<Tind;j++)
          {
            printf("%f ",Ind_cruza[j]);
          }
          printf("fin individuo cruza \n\n" );*/

          muta_ind(Ind_cruza);
          //imprimir individuo mutado
          /*printf("inicio individuo mutado \n" );
          for(i=0;i<Tind;i++)
          {
            printf("%f\n",Ind_cruza[i] );
          }
          printf("fin individuo mutado \n\n" );*/

        }
        /*else{
          printf("no entro a mutar el individuo\n\n");
        }*/


        //evaluación del individuo cruzado-mutado
        evaluar_individuo(Ind_cruza, nr, cruza_comp);

        //imprimimos la matriz de comparacion
        /*printf("inicio matriz comparacion individuo cruzado\n");
        for(j=0; j<Tnr;j++)
        {
          for(k=0; k<Tnr;k++)
          {
            printf("%c ", cruza_comp[j][k]);
          }
          printf("\n");
        }
        printf("fin matriz comparacion individuo cruzado\n");*/

        //evaluar al individuo cruzado, contar discrepancias
        //comparar matrices de comparacion
        //contar las discrepancias modelo-ind cruzado
        contar_discrepancias(matriz_ind, cruza_comp, disc_c, 0);



        total_disc = disc_c[0][0] + disc_c[0][1] + disc_c[0][2] + disc_c[0][3];
        /*printf("disc1: %d ",disc_c[0][0] );
        printf("disc2: %d ",disc_c[0][1] );
        printf("disc3: %d ",disc_c[0][2] );
        printf("disc4: %d ",disc_c[0][3] );
        printf("total: %d\n", total_disc );
        printf("++++++++++++++++++++++++\n");*/


        //Step 2.3 Actualización de z: Para cada j = , ...m, si zj < fj(y'), entonces zj = fj(y')
        //actualizar
        if(z[0] > disc_c[0][0])
        {
          z[0] = disc_c[0][0];
        }
        if(z[1] > disc_c[0][1])
        {
          z[1] = disc_c[0][1];
        }
        if(z[2] > disc_c[0][2])
        {
          z[2] = disc_c[0][2];
        }
        if(z[3] > disc_c[0][3])
        {
          z[3] = disc_c[0][3];
        }

        //Step 2.4 Actualización de las soluciones vecinas. Por cada indice j que pertenece a B(i), si
        //gte(y'|lamda j, z) <= gte (xj| lamda j, z), entonces set xj = y' y FVj = F(y')

        //printf("t: %d \n", t );


        for(j=0; j<t; j++) //t tamaño del vecindario
        {
          //printf("j=%d\n",j );
          indice_lambda = b[i][j]; //20 vecinos mas cercanos
          gte_y1 = ((disc_c[0][0] - z[0]) * lamda[indice_lambda][0]);
          gte_y2 = ((disc_c[0][1] - z[1]) * lamda[indice_lambda][1]);
          gte_y3 = ((disc_c[0][2] - z[2]) * lamda[indice_lambda][2]);
          gte_y4 = ((disc_c[0][3] - z[3]) * lamda[indice_lambda][3]);

          //calcular el máximo de los gte_y
          gte_y = maximo(gte_y1, gte_y2, gte_y3, gte_y4);
          //no es sumatoria, es tomar el máximo *****************************

          /*printf("gte y'1: %f \n", gte_y1 );
          printf("gte y'2: %f \n", gte_y2 );
          printf("gte y'3: %f \n", gte_y3 );
          printf("gte y'4: %f \n", gte_y4 );*/
          //printf("gte y: %f \n", gte_y );

          //calcular gte x
          gte_x1 = ((matriz_disc[indice_lambda][0] - z[0]) * lamda[indice_lambda][0]);
          gte_x2 = ((matriz_disc[indice_lambda][1] - z[1]) * lamda[indice_lambda][1]);
          gte_x3 = ((matriz_disc[indice_lambda][2] - z[2]) * lamda[indice_lambda][2]);
          gte_x4 = ((matriz_disc[indice_lambda][3] - z[3]) * lamda[indice_lambda][3]);
          gte_x = maximo(gte_x1, gte_x2, gte_x3, gte_x4);

          //printf("gte x: %f \n\n", gte_x );

          if(gte_y <= gte_x)
          {
            //printf("sustituyo al individuo: %d\n",indice_lambda );
            //sustituimos el individuo anterior por el individuo de cruza, xj = y'
            //indice lambda, es el indice del Individuo
            for(k=0;k<Tind;k++)
            {
              Pob[indice_lambda][k] = Ind_cruza[k];
            }

            //FVj = F(y')
            for(k=0;k<obj;k++)
            {
              matriz_disc[indice_lambda][k] = disc_c[0][k];
            }

          }

        }



        //Step 2.5 Actualización de EP
        //Eliminar de EP todos los vectores dominados por F (y')
        //Agregar F(y') a EP si no hay vectores en EP que dominen F(y')

        //ep[n]
        vec_dom = 0;
        for(j=0;j<n;j++)
        {
          no_dom = 0;
          stop = 0;
          for(k=0;k<obj;k++)
          {

            /*if(matriz_disc[j][k] < disc_c[0][k])
            {
              no_dom++;
            }*/

            if(matriz_disc[j][k] < disc_c[0][k])
            {
              no_dom++;
            }


            if(matriz_disc[j][k] != 0)
            {
              stop = stop + 1;
            }
          }


          //if(no_dom > 0 && total_disc < t_disc)
          if(no_dom > 0)
          {
            ep[j]= 1;
            vec_dom = vec_dom + 1;
            //t_disc = total_disc;
            /*total_disc = matriz_disc[j][0] + matriz_disc[j][1] + matriz_disc[j][2] + matriz_disc[j][3];
            printf("Mejor individuo encontrado: ");
            printf("disc1: %d ",matriz_disc[j][0] );
            printf("disc2: %d ",matriz_disc[j][1] );
            printf("disc3: %d ",matriz_disc[j][2] );
            printf("disc4: %d ",matriz_disc[j][3] );
            printf("total: %d\n", total_disc );*/
          }
          else
          {
            ep[j] = 0;
          }
          //printf("ep pos %d: %d\n", j, ep[j] );

          if(stop == 0) //guardamos al individuo
          {
            ind_nodom = j;
          }

        }

        if(stop == 0) //se encontró un individuo con 0 discrepancias
        {
          i = n;
          g = gen; //para que ya no entren al ciclo de nuevo
          r = ren;
        }



      }//fin del paso 2 update


      //imprimir a los mejores individuos de esta generacion
      for(i = 0; i<n;i++)
      {
        if(ep[i] == 1)
        {
          total_disc = matriz_disc[i][0] + matriz_disc[i][1] + matriz_disc[i][2] + matriz_disc[i][3];
          printf("Mejor individuo encontrado: ");
          fprintf(fd, "Mejor individuo encontrado: ");

          printf("disc1: %d ",matriz_disc[i][0] );
          fprintf(fd, "disc1: %d ",matriz_disc[i][0]);

          printf("disc2: %d ",matriz_disc[i][1] );
          fprintf(fd, "disc2: %d ",matriz_disc[i][1] );

          printf("disc3: %d ",matriz_disc[i][2] );
          fprintf(fd, "disc3: %d ",matriz_disc[i][2] );

          printf("disc4: %d ",matriz_disc[i][3] );
          fprintf(fd, "disc4: %d ",matriz_disc[i][3] );

          printf("total: %d\n", total_disc );
          fprintf(fd, "total: %d\n", total_disc );
        }

      }

      if(vec_dom == 0)
      {
        printf("no hay individuos buenos en esta generacion\n" );
        printf("el mejor individuo es f(y')\n" );
        //reemplazamos al primer individuo por el individuo f(y')
        for(j=0;j<Tind; j++)
        {

          Pob[0][j] = Ind_cruza[j];
        }
        for(j=0;j<obj;j++)
        {
          matriz_disc[0][j] = disc_c[0][j];
        }

        //imprimir esta matriz de discrepancias
        total_disc = matriz_disc[0][0] + matriz_disc[0][1] + matriz_disc[0][2] + matriz_disc[0][3];

        printf("disc1: %d ",matriz_disc[0][0] );
        fprintf(fd, "disc1: %d ",matriz_disc[0][0]);

        printf("disc2: %d ",matriz_disc[0][1] );
        fprintf(fd, "disc2: %d ",matriz_disc[0][1] );

        printf("disc3: %d ",matriz_disc[0][2] );
        fprintf(fd, "disc3: %d ",matriz_disc[0][2] );

        printf("disc4: %d ",matriz_disc[0][3] );
        fprintf(fd, "disc4: %d ",matriz_disc[0][3] );

        printf("total: %d\n", total_disc );
        fprintf(fd, "total: %d\n", total_disc );

        ep[0] = 1;

      }


}//fin generaciones

//seleccionar a uno de los mejores individuo para que forme parte de la población de reinicios
for(i = 0; i<n;i++)
{
  if(ep[i] == 1) //pasar al siguiente ciclo de reinicio
  {
    for(j=0;j<Tind; j++)
    {
      Ind_ren[j] = Pob[i][j];
    }
    i = n;
  }
}

//imprimir la poblacion en el reinicio 0, 3, 5, 7 y 10
printf("r = %d\n", r);

if(r == 0 || r == 3 || r == 5 || r == 7)
{
  fprintf(fd, "inicio mejor poblacion del reinicio %d  n\n", r  );
  printf("inicio mejor poblacion del reinicio %d  n\n", r  );
  for(i = 0; i<n;i++)
  {
    if(ep[i] == 1)
    {
      fprintf(fd, "ep[%d] = %d ", i, ep[i]  );
      printf("ep[%d] = %d ", i, ep[i] );
      //imprimimos al individuo
      fprintf(fd, "inicio individuo no dominado  n\n"  );
      printf("inicio individuo no dominado  n\n" );
      for(j=0;j<Tind;j++)
      {
        printf("%f ",Pob[i][j] );
        fprintf(fd, "%f ",Pob[i][j]  );
      }

      printf("\nfin individuo no dominado n\n" );
      fprintf(fd, "\nfin individuo no dominado n\n" );
    }
  }
  fprintf(fd, "fin mejor poblacion del reinicio %d  n\n", r  );
  printf("fin mejor poblacion del reinicio %d  n\n", r  );
}



}//fin reinicios
//Step 3 Stopping Criteria
//Si se satisface el criterix, y, z, w, sumo de parada, entonces detenerse y la salida será EP
//Si no, ir al paso 2.



  //imprimir la poblacion externa o al individuo no dominado
  if(stop == 0) //imprimimos al individuo
  {
    fprintf(fd, "inicio individuo 0 discrepancias  n\n" );
    printf("inicio individuo 0 discrepancias  n\n" );


    for(j=0;j<Tind;j++)
    {
      Ind_ren[j] = Pob[ind_nodom][j];
      printf("%f ",Pob[ind_nodom][j] );
      fprintf(fd, "%f ",Pob[ind_nodom][j] );
    }

    printf("\nfin individuo 0 discrepancias n\n\n" );
    fprintf(fd, "\nfin individuo 0 discrepancias n\n\n" );

  }
  else{
    for(i = 0; i<n;i++)
    {
      if(ep[i] == 1)
      {
        fprintf(fd, "ep[%d] = %d ", i, ep[i]  );
        printf("ep[%d] = %d ", i, ep[i] );
        //imprimimos al individuo
        fprintf(fd, "inicio individuo no dominado  n\n"  );
        printf("inicio individuo no dominado  n\n" );
        for(j=0;j<Tind;j++)
        {
          printf("%f ",Pob[i][j] );
          fprintf(fd, "%f ",Pob[i][j]  );
        }

        printf("\nfin individuo no dominado n\n\n" );
        fprintf(fd, "\nfin individuo no dominado n\n\n" );
      }

    }

    //imprimimos al individuo encontrado
    /*fprintf(fd, "inicio mejor individuo encontrado  n\n"  );
    printf("inicio mejor individuo encontrado n\n" );
    for(j=0;j<Tind;j++)
    {
      printf("%f ",Ind_ren[j] );
      fprintf(fd, "%f ",Ind_ren[j]  );
    }

    printf("\nfin mejor individuo encontrado n\n\n" );
    fprintf(fd, "\nfin mejor individuo encontrado n\n\n" );*/

  }


  //imprimir decisor real y nr
  fprintf(fd, "inicio decisor real  n\n");
  printf("inicio decisor real  n\n" );
  for(j=0;j<Tind;j++)
  {
    fprintf(fd, "%f ",Pob[n][j]);
    printf("%f ",Pob[n][j] );
  }

  printf("\nfin decisor real n\n\n" );
  fprintf(fd, "\nfin decisor real n\n\n");

  imprimir_hora();

  fclose(fd);
  return 0;
}

int imprimir_hora()
{
  time_t t;
  struct tm *tm;
  char fechayhora[100];

  t=time(NULL);
  tm=localtime(&t);
  strftime(fechayhora, 100, "%d/%m/%y %H:%M", tm);
  printf ("Experimento: %s\n\n", fechayhora);

  return 0;
}

float maximo(float val1, float val2, float val3, float val4)
{
  int n = 4, i;
  float max;
  float val[4];

  val[0]=val1;
  val[1]=val2;
  val[2]=val3;
  val[3]=val4;

  max = val[0];
  for(i=0; i<n; i++)
  {
    if(max < val[i])
    {
      max = val[i];
    }
  }

  return max;
}

int ordenar(int n, float*ord_val, int*ord_id)
{
  int i, j;
  float temp, tempid;

  //métdo de la burbuja
  for (i = 0; i < (n - 1); i++)
  {
    for (j = i + 1; j < n; j++)
    {
      if (ord_val[j] < ord_val[i])
      {
        temp = ord_val[j];
        tempid = ord_id[j];

        ord_val[j] = ord_val[i];
        ord_id[j] = ord_id[i];

        ord_val[i] = temp;
        ord_id[i] = tempid;
      }
    }
  }
  return 0;
}

void Pob_ini(float Pob[Tpob][Tind], int t_pob)
{
  //printf("prueba numero de atributos: %d\n", Natr);

  float ST,w[Natr],ro,lambda,lambda_corte,q,p,s,r,d,v;
  int i,j,k,temp,ren,col,salir,n[4],val,valq,valp,vals,valr,vald,valv;

  time_t t;

  for(i=0;i<t_pob;i++)
  {
    ren=i;

    // Inicialización de los parámetros por atributo q,p,s,r,d,v
    for(j=0;j<Natr;j++)
    {
      salir=0;
      while(salir==0)
      {
        valq=rand() % 2;
        valp=rand() % 3;
        vals=rand() % 4;
        valr=rand() % 5;
        vald=rand() % 6;
        valv=rand() % 6;
        if(valp>=valq && vals>=valp && valr>=vals && vald>=valr  && valv>=valr)
        {salir=1;}
      }

      // q
      col=6*j;
      Pob[ren][col]=(float) valq;

      // p
      col=col+1;
      Pob[ren][col]=(float) valp;

      // s
      col=col+1;
      Pob[ren][col]=(float) vals;

      // r
      col=col+1;
      Pob[ren][col]=(float) valr;

      // d
      col=col+1;
      Pob[ren][col]=(float) vald;

      // v
      col=col+1;
      Pob[ren][col]=(float) valv;
    }
    // Fin de la Inicialización de los parámetros por atributo q,p,s,r,d,v
    //printf("aqui 1*****************************\n" );

    // Inicio de la Generación aleatoria de los Pesos entre (0.15 y 0.25)**
    salir=0;
    //int contador = 0;
    while(salir==0)
    {
      //printf("contador = %d   ", contador );

      ST=0;
      for(j=0;j<Natr-1;j++)
      {
        w[j]=rand() % 1001;

        //w[j]=w[j]+2000;
        w[j]=w[j]+1500;
        ST=ST+w[j];
      }


      w[Natr-1]=10000-ST;
      //printf("w[%d] = %f\n\n", (Natr-1),w[Natr-1] );

      //verificación de los pesos
      if(w[Natr-1]>1500 && w[Natr-1]<2500)
      { salir=1; }

      //contador = contador + 1;
    }


    ST=0;
    for(j=0;j<Natr-1;j++)
    { col=j+6*Natr; Pob[ren][col]=(float) w[j]/10000; ST = ST + Pob[ren][col]; }
    col=6*Natr+Natr-1;
    Pob[ren][col]= 1 - ST;
    // Fin de la Generación aleatoria de los Pesos


    // Inicialización de los parámetros generales alfa,beta,gamma,delta

    // generar cuatro números distintos
    salir=0;
    while(salir==0)
    {
      n[0] = 1+rand() % 1000;
      n[1] = 1+rand() % 1000;
      n[2] = 1+rand() % 1000;
      n[3] = 1+rand() % 1000;
      salir=1;
      if(n[0]==n[1] || n[0]==n[2] || n[0]==n[3] || n[1]==n[2] || n[1]==n[3] || n[2]==n[3])
      { salir=0; }
    }


    // ordenarlos
    for(j=0;j<3;j++)
    {
      for(k=j+1;k<4;k++)
      {
        if(n[j]>n[k])
        { temp=n[j]; n[j]=n[k]; n[k]=temp; }
      }
    }
    // Fin del ordenamiento


    for(j=0;j<4;j++)
    { col=(7*Natr)+j; Pob[ren][col]=(float) n[j]/1000; }

    // Fin de la Inicialización de los parámetros generales alfa,beta,gamma,delta


    // Inicialización de los parámetros generales epsilon,zita

    // generar dos números distintos
    salir=0;
    while(salir==0)
    {
      n[0] = 1+rand() % 1000;
      n[1] = 1+rand() % 1000;
      salir=1;
      if(n[0]==n[1])
      { salir=0; }
    }

    // ordenarlos
    if(n[0]>n[1])
    { temp=n[0]; n[0]=n[1]; n[1]=temp; }
    // Fin del ordenamiento

    col=(7*Natr)+4; Pob[ren][col]=(float) n[0]/1000;
    col=(7*Natr)+5; Pob[ren][col]=(float) n[1]/1000;

    // Fin de la Inicialización de los parámetros generales epsilon,zita

    // Inicialización de los parámetros generales ro (-1.74,2.4),lambda (-2,2)
    ro= 1+rand() % 4140;
    ro=((float) ro/1000)-1.75;

    lambda= 1+rand() % 4000;
    lambda=((float) lambda/1000)-2;

    col=(7*Natr)+6; Pob[ren][col]=ro;
    col=(7*Natr)+7; Pob[ren][col]=lambda;
    // Fin de la Inicialización de los parámetros generales ro (-1.74,2.4),lambda (-2,2)

    // Inicialización del parámetro lambda de corte (0.55,0.85)
    lambda_corte=0.55 + (float) (rand() % 301)/1000;
    col=(7*Natr)+8; Pob[ren][col]=lambda_corte;
    // Fin de la Inicialización del parámetro lambda de corte
  }

}

void generar_nr(float nr[Tnr][Natr], int Tnr, int Natr)
{
  float temp;
  int i, j;

  //printf("nucleo de referencia \n");
  for(i=0; i<Tnr;i++)
  {
    for(j=0; j<Natr;j++)
    {
      temp = rand() % 10000;
      nr[i][j] = temp / 1000;
      //printf("%f ", nr[i][j]);
    }
    //printf("\n");
  }

  //printf("fin nucleo de referencia \n\n");

} //como regreso el arreglo... necesito usar punteros ***

void weight_vectors(float lamda[n][obj])
{
  float x, y, z, w, sum;
  int i;
  //vectores de peso uniformemente distribuidos
  //a uniform spread of N weight vectors lamdai ... lamdaN;
  //de momento no es uniforme
  //printf("inicio vectores de peso uniformemente distribuidos\n" );
  for(i=0; i<n;i++)
  {
      x = rand();
      y = rand();
      z = rand();
      w = rand();

      sum = x + y + z + w;

      lamda[i][0] = x / sum;
      lamda[i][1] = y / sum;
      lamda[i][2] = z / sum;
      lamda[i][3] = w / sum;

      /*printf("%f ", lamda[i][0]);
      printf("%f ", lamda[i][1]);
      printf("%f ", lamda[i][2]);
      printf("%f\n", lamda[i][3]);*/

  }
  //printf("fin vectores de peso uniformemente distribuidos\n" );
}

void weight_vectors_2(float lamda[n][obj])
{
  float x, y, z, w, sum;
  int i,j, maximo_id, ind_dist;

  int lim = 5000;
  float random[lim][obj];
  float vectores[obj][obj];
  float distancias[lim][obj];
  float maximo;

  //el vector para medir las distancias
  //1 0 0 0
  //0 1 0 0
  //0 0 1 0
  //0 0 0 1
  for(i=0;i<obj;i++)
  {
    for(j=0;j<obj;j++)
    {
      if(i==j)
      {
        vectores[i][j]=1;
      }
      else{
        vectores[i][j]=0;
      }
    }
  }


  //generar una gran cantidad de números aleatorios
  for(i=0; i<lim;i++)
  {
      x = rand();
      y = rand();
      z = rand();
      w = rand();

      sum = x + y + z + w;

      random[i][0] = x / sum;
      random[i][1] = y / sum;
      random[i][2] = z / sum;
      random[i][3] = w / sum;
  }

  //calcular las distancias euclideanas
  for(i=0; i<lim;i++)
  {
    for(j=0; j<obj;j++)
    {
      distancias[i][j] = sqrt(pow(vectores[j][0]-random[i][0],2) +
                  pow(vectores[j][1]-random[i][1],2) +
                  pow(vectores[j][2]-random[i][2],2) +
                  pow(vectores[j][3]-random[i][3],2));
    }


  }

  for(i=0; i<456;i++)
  {
    if(i<114)
    {
      ind_dist = 0;
    }
    else if(i<228)
    {
      ind_dist = 1;
    }
    else if(i<342)
    {
      ind_dist = 2;
    }
    else{
      ind_dist = 3;
    }

    maximo = 0;
    maximo_id = 0;
    //elegir los mas lejanos
    for(j=0; j<lim;j++)
    {
      if(distancias[j][ind_dist]>maximo)
      {
        maximo = distancias[j][ind_dist];
        maximo_id = j;
        distancias[j][ind_dist]=0; //para que no sea el mismo
      }
    }

    lamda[i][0] = random[maximo_id][0];
    lamda[i][1] = random[maximo_id][1];
    lamda[i][2] = random[maximo_id][2];
    lamda[i][3] = random[maximo_id][3];
  }

  /*printf("inicio vectores de peso uniformemente distribuidos\n" );
  for(i=0; i<n;i++)
  {
    printf("%f ", lamda[i][0]);
    printf("%f ", lamda[i][1]);
    printf("%f ", lamda[i][2]);
    printf("%f\n", lamda[i][3]);
  }
  printf("fin vectores de peso uniformemente distribuidos\n" );*/



}

void distancias_euclideanas(float euc[n][n], float lamda[n][obj])
{
  int i, j;

  for(i=0; i<n;i++)
  {
    for(j=0; j<n;j++)
    {
          euc[i][j] = sqrt(pow(lamda[i][0]-lamda[j][0],2) +
                      pow(lamda[i][1]-lamda[j][1],2) +
                      pow(lamda[i][2]-lamda[j][2],2) +
                      pow(lamda[i][3]-lamda[j][3],2));

    }
  }

}

void generar_vecindario(int b[n][t], float Pob[Tpob][Tind], float euc[n][n])
{
  int i,j, k, ord_id[n];
  float delta, ord_val[n];

  for(i=0; i<n;i++)
  {
    delta = Pob[n][31];
    for(j=0; j<n;j++)
    {
      //preparamos el arreglo para ordenar
      ord_val[j] = euc[i][j];
      ord_id[j] = j;

    }
    ordenar(n, ord_val, ord_id);

    //seleccionamos a los 20 mas cercanos
    //descartamos el 1ero
    delta = Pob[n][31];
    for(k=0; k<t;k++)
    {
      //b[i][k] = ord_val[k+1];
      b[i][k] = ord_id[k+1]; //queremos los id de los vecinos mas cercanos
    }

  }

}

void armar_individuo(float Pob[Tpob][Tind], float Ind[Tind], int ind)
{
  int i;
  for(i=0;i<Tind; i++)
  {
    Ind[i] = Pob[ind][i];
  }
}

//5 atributos
void evaluar_individuo(float Ind[Tind], float nr[Tnr][Natr], char matriz_comp[Tnr][Tnr])
{
  int i, j;
  float q[obj], p[obj], s[obj], r[obj], d[obj], v[obj], w[obj];
  float alfa,beta,gamma,delta,epsilon,zita,ro,lambda,lambda_corte;
  float sigmaaPb, sigmabPa, sigmaaIb, sigmabIa, sigmaaRb, sigmabRa, sigmaaQb, sigmabQa;


  for(i=0;i<Natr;i++)
  {
    //el 455 es el individuo de prueba
    q[i] = Ind[i*6];
    p[i] = Ind[i*6+1];
    s[i] = Ind[i*6+2];
    r[i] = Ind[i*6+3];
    d[i] = Ind[i*6+4];
    v[i] = Ind[i*6+5];

    w[i] = Ind[30+i];

    /*printf("q[%d] = %f\n", i, ind_q[i]);
    printf("p[%d] = %f\n", i, ind_p[i]);
    printf("s[%d] = %f\n", i, ind_s[i]);
    printf("r[%d] = %f\n", i, ind_r[i]);
    printf("d[%d] = %f\n", i, ind_d[i]);
    printf("v[%d] = %f\n", i, ind_v[i]);

    printf("w[%d] = %f\n", i, ind_w[i]);*/
  }

  //el 455 es el individuo de prueba
  alfa = Ind[35];
  beta = Ind[36];
  gamma = Ind[37];
  delta = Ind[38];
  epsilon = Ind[39];
  zita = Ind[40];
  ro = Ind[41];
  lambda = Ind[42];
  lambda_corte = Ind[43];

  for(i=0; i<Tnr;i++)
  {
    for(j=0; j<Tnr;j++)
    {
      sigmaaPb=sigma_aPb(nr[i],nr[j],q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);
      sigmabPa=sigma_aPb(nr[j],nr[i],q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);
      sigmaaIb=sigma_aIb(nr[i],nr[j],q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);
      sigmaaQb=sigma_aQb(nr[i],nr[j],q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);
      sigmabQa=sigma_aQb(nr[j],nr[i],q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);
      sigmaaRb=sigma_aRb(nr[i],nr[j],q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);
      //sigmaaSb=sigma_aSb(nr[i],nr[j],q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);
      //sigmabSa=sigma_aSb(nr[j],nr[i],q,p,w,s,r,v,d,alfa,beta,gamma,delta,epsilon,zita,lambda,ro);

      /*printf("i: %d\n ", i);
      printf("lambda corte %f\n ", lambda_corte);
      printf("sigmaaPb %f\n ", sigmaaPb);
      printf("sigmabPb %f\n ", sigmabPa);
      printf("sigmaaIb %f\n ", sigmaaIb);
      printf("sigmaaQb %f\n ", sigmaaQb);
      printf("sigmabQa %f\n ", sigmabQa);
      printf("sigmaaRb %f\n\n", sigmaaRb);*/

      matriz_comp[i][j]='-';

      //relaciones del decisor
      if(sigmaaQb >= lambda_corte)
      {
        //printf("entro preferencia debil aQb\n");
        matriz_comp[i][j]='Q';
      }
      if(sigmabQa >= lambda_corte)
      {
        //printf("entro preferencia debil bQa\n");
        matriz_comp[i][j]='q';
      }
      if(sigmaaPb >= lambda_corte)
      {
        //printf("entro preferencia aPb\n");
        matriz_comp[i][j]='P';
      }
      if(sigmabPa >= lambda_corte)
      {
        //printf("entro preferencia bPa\n");
        matriz_comp[i][j]='p';
      }
      if(sigmaaRb >= lambda_corte)
      {
        //printf("entro incomparabilidad\n");
        matriz_comp[i][j]='R';
      }
      if(sigmaaIb >= lambda_corte)
      {
        //printf("entro indiferencia\n");
        matriz_comp[i][j]='I';
      }


      if(matriz_comp[i][j]=='-')
      {
        //printf("no entro a ninguna relación\n");

        /*printf("nucleo referencia i=%d, j=%d\n", i, j);

        printf("sigmaaPb %f\n ", sigmaaPb);
        printf("sigmabPb %f\n ", sigmabPa);
        printf("sigmaaIb %f\n ", sigmaaIb);
        printf("sigmaaQb %f\n ", sigmaaQb);
        printf("sigmabQa %f\n ", sigmabQa);
        printf("sigmaaRb %f\n\n", sigmaaRb);*/

        //pondremos R para cuando no arroje ninguna relación*
        matriz_comp[i][j]='R';

      }


    }
  }

}

void contar_discrepancias(char matriz_ind[Tnr][Tnr], char modelo_comp[Tnr][Tnr], int matriz_disc[n][obj], int pos)
{

  int i, j;
  int disc1, disc2, disc3, disc4, conc, total; //pasar a vector
  char d_real, d_gen; //decisor real y decisor generado, para la comparación

  disc1=0, disc2=0, disc3=0, disc4=0, conc = 0;

  for(i=0;i<Tnr;i++)
  {
    for(j=0;j<Tnr;j++)
    {
      d_real = matriz_ind[i][j];
      d_gen = modelo_comp[i][j];

      //printf("d_real = %d\n", d_real);
      //printf("d_gen = %d\n\n", d_gen);

      if(d_real == 'I' && (d_gen == 'Q' || d_gen == 'q'))
      {
        disc1++;
      }
      else if(d_real == 'Q' && d_gen == 'P')
      {
        disc1++;
      }
      if(d_gen == 'I' && (d_real == 'Q' || d_real == 'q'))
      {
        disc1++;
      }
      else if(d_gen == 'Q' && d_real == 'P')
      {
        disc1++;
      }

      else if(d_real == 'I' && (d_gen == 'P' || d_gen == 'p'))
      {
        disc2++;
      }
      else if(d_real == 'Q' && d_gen == 'q')
      {
        disc2++;
      }
      else if(d_gen == 'I' && (d_real == 'P' || d_real == 'p'))
      {
        disc2++;
      }
      else if(d_gen == 'Q' && d_real == 'q')
      {
        disc2++;
      }

      else if((d_real == 'P' && d_gen == 'p') || (d_gen == 'P' && d_real == 'p'))
      {
        disc3++;
      }
      else if((d_real == 'Q' && d_gen == 'p') || (d_gen == 'Q' && d_real == 'p'))
      {
        disc3++;
      }
      else if((d_real == 'q' && d_gen == 'P') || (d_gen == 'q' && d_real == 'P'))
      {
        disc3++;
      }
      else if((d_real == 'q' && d_gen == 'p') || (d_gen == 'q' && d_real == 'p'))
      {
        disc3++;
      }

      else if((d_real == 'R' && d_gen != 'R')|| (d_gen == 'R' && d_real != 'R'))
      {
        disc4++;
      }
      else if(d_real == d_gen)
      {
        conc++;
      }

    }
  }

  //guardamos en la matriz de discrepancias para la función gte
  matriz_disc[pos][0] = disc1;
  matriz_disc[pos][1] = disc2;
  matriz_disc[pos][2] = disc3;
  matriz_disc[pos][3] = disc4;

  total = disc1 + disc2 + disc3 + disc4 + conc;

  /*printf("disc1: %d\n",disc1);
  printf("disc2: %d\n",disc2);
  printf("disc3: %d\n",disc3);
  printf("disc4: %d\n",disc4);
  printf("conc: %d\n",conc);
  printf("total: %d\n",total);
  printf("---------------------\n");*/
}

void cruza_individuo(float Pob[Tpob][Tind], float Ind_cruza[Tind], int ind_k, int ind_l, float Pc, float nr[Tnr][Natr], char matriz_ind[Tnr][Tnr])
{
  int arr_pcruza[] = {5,11, 17, 23, 29, 34, 38, 40, 42, 43};
  //duda... si elige el último índice, es cruza??? debo incluirlo??
  int ps_cruza = 9; //puntos de cruce ** son 10 pero por los índices -1

  int p_cruza; //punto de cruce
  int ind_cruza; //su equivalente en el vector
  int i, j;
  float aleat;
  float p1[Tind], p2[Tind]; //padres
  char matriz_p1[Tnr][Tnr], matriz_p2[Tnr][Tnr];
  int p1_disc[n][obj], p2_disc[n][obj];
  int total_discp1, total_discp2;

  aleat=(float) (rand() % RAND_MAX)/(RAND_MAX-1); //probabilidad de cruza

  if(aleat<=Pc)
  {
    //printf("entro a cruza\n");
    //cruza
    //seleccionamos aleatoriamente el punto de cruza
    p_cruza = rand() % ps_cruza;
    //printf("punto cruza = %d\n",p_cruza);

    ind_cruza = arr_pcruza[p_cruza];
    //printf("punto indice de cruza = %d\n",ind_cruza);


    //imprimir padre k
     /*printf("inicio padre k \n" );
     for(i=0;i<Tind;i++)
     {
       printf("%f ",Pob[ind_k][i]);
     }
     printf("fin padre k \n\n" );*/

    //individuo k
    for(i=0; i<ind_cruza; i++)
    {
      p1[i] = Pob[ind_k][i];
      //Ind_cruza[i] = Pob[ind_k][i];
    }
    for(j=ind_cruza; j<Tind; j++)
    {
      p1[j] = Pob[ind_l][j];
      //Ind_cruza[j] = Pob[ind_l][j];
    }


    for(i=ind_cruza; i<Tind; i++)
    {
      p2[i] = Pob[ind_k][i];
      //Ind_cruza[i] = Pob[ind_k][i];
    }
    //individuo l
    for(j=0; j<ind_cruza; j++)
    {
      p2[j] = Pob[ind_l][j];
      //Ind_cruza[i] = Pob[ind_k][i];
    }


    //imprimir padre l
    /*printf("inicio padre l \n" );
     for(i=0;i<Tind;i++)
     {
       printf("%f ",Pob[ind_l][i]);
     }
     printf("fin padre l \n\n" );*/





  }
  else //no hubo cruza
  {
    //printf("no hubo cruza\n");
    for(i=0;i<Tind;i++)
    {
      p1[i] = Pob[ind_k][i];
      p2[i] = Pob[ind_l][i];

    }


  }


  //seleccion del mejor individuo por torneo (elegir al mejor de la evaluación )
  //evaluar p1 y p2
  evaluar_individuo(p1, nr, matriz_p1);
  contar_discrepancias(matriz_ind, matriz_p1, p1_disc, 0);
  total_discp1 = p1_disc[0][0] + p1_disc[0][1] + p1_disc[0][2] + p1_disc[0][3];
  //p2
  evaluar_individuo(p2, nr, matriz_p2);
  contar_discrepancias(matriz_ind, matriz_p2, p2_disc, 0);
  total_discp2 = p2_disc[0][0] + p2_disc[0][1] + p2_disc[0][2] + p2_disc[0][3];

  //printf("total_disc p1: %d\n",total_discp1 );
  //printf("total_disc p2: %d\n",total_discp2 );

  //imprimir al mejor individuo
  /*printf("inicio padre 1 -cruza- \n" );

  for(j=0;j<Tind;j++)
  {
    printf("%f ",p1[j] );
  }

  printf("fin padre 1 -cruza \n" );*/

  /*printf("inicio padre 2 -cruza- \n" );

  for(j=0;j<Tind;j++)
  {
    printf("%f ",p2[j] );
  }

  printf("fin padre 2 -cruza n\n\n" );*/

  if(total_discp1<total_discp2)
  {
    //elegir p1
    for(i=0;i<Tind;i++)
    {
      Ind_cruza[i] = p1[i];
    }
  }
  else
  {
    //elegir p2
    for(i=0;i<Tind;i++)
    {
      Ind_cruza[i] = p2[i];
    }
  }

  //imprimir al mejor individuo
  /*printf("inicio mejor individuo -cruza- \n" );

  for(j=0;j<Tind;j++)
  {
    printf("%f ",Ind_cruza[j] );
  }

  printf("fin mejor individuo -cruza n\n\n" );*/




}

void muta_ind(float I[Tind])
{

  int i,j,k,u,col,temp,salir,valq,valp,vals,valr,vald,valv,n[4],band;
  float w[Natr],ST,ro,lambda,lambda_corte,q,p,s,r,d,v,wt,acum,acum2,pg[4],epsilon,zita;

  u=rand() % Tind;


  // parámetros por atributo q,p,s,r,d,v
  if(u<6*Natr)
  {
    //printf("entro a mutar q, p, s, r, d, v \n" );
    //Identificación del atributo
    for(i=0;i<Natr;i++)
    {
      if(u>=6*i && u<6*(i+1))
      {
        //asignación de parametros para facilidad de tratamiento
        q=I[6*i];p=I[6*i+1];s=I[6*i+2];r=I[6*i+3];d=I[6*i+4];v=I[6*i+5];

        //Mutación en q
        if(u==6*i)
        {
          if(q==1)
          { q=0; I[u]=q; }
          if(q==0)
          {
            q=1; I[u]=1;
            if(q>p)
            {
              p=q; I[u+1]=p;
              if(p>s)
              {
                s=p; I[u+2]=s;
                if(s>r)
                {
                  r=s; I[u+3]=r;
                  if(r>d)
                  { d=r; I[u+4]=d; }

                  if(r>v)
                  { v=r; I[u+5]=v; }
                }
              }
            }
          }
        }

        //Mutación en p
        if(u==6*i+1)
        {
          band= rand() % 2;
          if(p==0)
          {
            if(band==0)
            { p=1; I[u]=p; }
            else
            { p=2; I[u]=p; }

            if(p>s)
            {
              s=p; I[u+1]=s;
              if(s>r)
              {
                r=s; I[u+2]=r;
                if(r>d)
                { d=r; I[u+3]=d; }

                if(r>v)
                { v=r; I[u+4]=v; }
              }
            }
          }

          if(p==1)
          {
            if(band==0)
            { p=0; q=0; I[u-1]=q; I[u]=p; }
            else
            {
              p=2; I[u]=p;
              if(p>s)
              {
                s=p; I[u+1]=s;
                if(s>r)
                {
                  r=s; I[u+2]=r;
                  if(r>d)
                  { d=r; I[u+3]=d; }

                  if(r>v)
                  { v=r; I[u+4]=v; }
                }
              }
            }
          }

          if(p==2)
          {
            if(band==0)
            { p=0; q=0; I[u-1]=q; I[u]=p; }
            else
            { p=1; I[u]=p; }
          }
        }

        //Mutación en s
        if(u==6*i+2)
        {
          band= rand() % 2;
          if(r-p==0)
          {
            if(band==0)
            {
              s=s-1; p=p-1; I[u]=s; I[u-1]=p;
              if(q>p)
              { q=p; I[u-2]=q; }
            }
            else
            {
              s=s+1; r=r+1; I[u]=s; I[u+1]=r;
              if(r>d)
              { d=r; I[u+2]=d; }

              if(r>v)
              { v=r; I[u+3]=v; }
            }
          }

          if(r-p==1)
          {
            if(s==p)
            { s=r; I[u]=s; }
            if(s==r)
            { s=p; I[u]=s; }
          }

          if(r-p==2)
          {
            if(s==p)
            {
              if(band==0)
              { s=s+1; I[u]=s; }
              else
              { s=s+2; I[u]=s; }
            }
            if(s==p+1)
            {
              if(band==0)
              { s=p; I[u]=s; }
              else
              { s=r; I[u]=s; }
            }

            if(s==p+2)
            {
              if(band==0)
              { s=p; I[u]=s; }
              else
              { s=p+1; I[u]=s; }
            }
          }

          if(r-p==3)
          {
            if(s==p)
            {
              if(band==0)
              { s=p+1; I[u]=s; }
              else
              { s=p+2; I[u]=s; }
            }

            if(s==p+1)
            {
              if(band==0)
              { s=p; I[u]=s; }
              else
              { s=p+2; I[u]=s; }
            }

            if(s>p+1)
            {
              if(band==0)
              { s=p; I[u]=s; }
              else
              { s=p+1; I[u]=s; }
            }
          }
        }

        //Mutación en r
        if(u==6*i+3)
        {
          band= rand() % 2;
          if(r==s)
          {
            r=r+1; I[u]=r;
            if(r>d)
            { d=r; I[u+1]=d; }
            if(r>v)
            { v=r; I[u+2]=v; }
          }

          if(r>s)
          {
            if(band==0)
            { r=r-1; I[u]=r; }
            else
            {
              if(r+1<5)
              {
                r=r+1; I[u]=r;
                if(r>d)
                { d=r; I[u+1]=d; }
                if(r>v)
                { v=r; I[u+2]=v; }
              }
              else
              { r=r-1; I[u]=r; }
            }
          }
        }

        //Mutación en d o v
        if(u==6*i+4 || u==6*i+5)
        {
          if(r==I[u])
          { I[u]=r+1; }
          else
          {
            if(I[u]<5)
            {
              if(band==0)
              { I[u]=I[u]-1; }
              else
              { I[u]=I[u]+1; }
            }
            else
            { I[u]=I[u]-1; }
          }
        }
      }
    }
  }


  // Pesos
  if(u>=6*Natr && u<7*Natr)
  {
    //printf("entro a mutar peso\n" );
    //Mutación
    wt=rand() % 1001;
    //wt=wt+2000;
    wt=wt+1500;
    wt=(float) wt/10000;
    I[u]=wt;

    //asignación de parametros para facilidad de tratamiento
    w[0]=I[6*Natr];
    w[1]=I[6*Natr+1];
    w[2]=I[6*Natr+2];
    w[3]=I[6*Natr+3];
    w[4]=I[6*Natr+4]; //nuevo_prueba

    salir=0;
    while(salir==0)
    {
      acum=0;
      for(i=0;i<Natr;i++)
      { acum=acum+w[i]; }

      acum2=0;
      for(i=0;i<Natr-1;i++)
      { w[i]= (float) w[i]/acum; acum2=acum2+w[i]; }
      w[Natr-1]=1-acum2;

      salir=1;
      for(i=0;i<Natr;i++)
      {
        if(w[i]>=0.25 || w[i]<=0.15)
        { salir=0; w[i]=0.2; }
      }
    }
    for(i=0;i<Natr;i++)
    { I[6*Natr+i]=w[i]; }
  }


  // parámetros generales alfa,beta,gamma,delta
  if(u>=7*Natr && u<8*Natr)
  {
    //printf("entro a mutar alfa,beta, gamma, delta\n" );
    salir=0;
    while(salir==0)
    {
      // Mutación
      wt= 1+rand() % 1000;
      wt= (float) wt/1000;
      I[u]=wt;
      salir=1;
      for(i=0;i<Natr;i++)
      {
        if(I[7*Natr+i]==I[u] && (7*Natr+i)!=u)
        { salir=0; }
      }
    }

    //asignación de parametros para facilidad de tratamiento
    pg[0]=I[7*Natr];pg[1]=I[7*Natr+1];pg[2]=I[7*Natr+2];pg[3]=I[7*Natr+3];

    // ordenarlos
    for(j=0;j<3;j++)
    {
      for(k=j+1;k<4;k++)
      {
        if(n[j]>n[k])
        { temp=pg[j]; pg[j]=pg[k]; pg[k]=temp; }
      }
    }
    // Fin del ordenamiento

    for(j=0;j<4;j++)
    { I[7*Natr+j]=n[j]; }
  }


  // parámetros generales epsilon,zita
  if(u>=8*Natr && u<8*Natr+2)
  {
    //printf("entro a mutar epsilon, zita\n" );
    salir=0;
    while(salir==0)
    {
      // Mutación
      wt= 1+rand() % 1000;
      wt= (float) wt/1000;
      I[u]=wt;
      salir=1;
      if(I[8*Natr]==I[8*Natr+1])
      { salir=0; }
    }

    //asignación de parametros para facilidad de tratamiento
    epsilon=I[8*Natr];zita=I[8*Natr+1];

    // ordenarlos
    if(epsilon>zita)
    { temp=epsilon; epsilon=zita; zita=temp; }
    // Fin del ordenamiento

    I[8*Natr]=(float) epsilon;
    I[8*Natr+1]=(float) zita;
  }


  // ro (-1.74,2.4)
  if(u==8*Natr+2)
  {
    //printf("entro a mutar ro\n" );
    salir=0;
    while(salir==0)
    {
      ro= 1+rand() % 4140;
      ro=((float) ro/1000)-1.75;
      salir=1;
      if(ro==I[u])
      { salir=0; }
    }
    I[u]=ro;
  }

  // lambda (-2,2)
  if(u==8*Natr+3)
  {
    //printf("entro a mutar lambda\n" );
    salir=0;
    while(salir==0)
    {
      lambda= 1+rand() % 4000;
      lambda=((float) lambda/1000)-2;
      salir=1;
      if(lambda==I[u])
      { salir=0; }
    }
    I[u]=lambda;
  }

  // lambda de corte (0.55,0.85)
  if(u==8*Natr+4)
  {
    //printf("entro a mutar lambda corte\n" );
    salir=0;
    while(salir==0)
    {
      lambda_corte=0.55 + (float) (rand() % 301)/1000;
      salir=1;
      if(lambda_corte==I[u])
      { salir=0; }
    }
    I[u]=lambda_corte;
  }

}
