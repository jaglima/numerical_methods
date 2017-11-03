#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NEQS 3 // numero de equacoes do sistema de EDOs
#define TSTART 0 // tempo de inicio de integracao
#define TEND 100 // tempo final de integracao
#define NSTEP 10000 // numero de passos da integracao


/* Funcao que implementa o sistema de EDOs a ser resolvido por runge-kutta de forma que dx/dt = f(x), x[NEQS]. */
/* Entrada: Recebe um ponteiro para um vetor x de dimensao neqs representando um ponto do espaco de fase,  */
/* e um ponteiro para uma vetor dx que armazena o valor das derivadas calculadas neste ponto x. */
/* Saida: Retorna saida vazia. Os valores calculados sao retornados no vetor dx passado na entrada. */

void fun(double x[], double dx[]){

  double ro = 10;
  double r = 28;
  double b = (double) 8/3;
  
  dx[0] = -ro*x[0] + ro*x[1]; 
  dx[1] = r*x[0] - x[1] - x[0]*x[2];
  dx[2] = x[0]*x[1] - b*x[2];
}


/* Funcao que implementa o metodo de integracao de rungeKutta de ordem 4  */
/* Entrada: Recebe como entrada os inteiros representando o numero de equacoes do sistema neqs e o numero de  */
/* passos do metodo nsteps. Recebe um double com o tamanho do passo dt, e ponteiros para o vetor de condicoes  */
/* iniciais x0, o vetor de passos no tempo tout e a matriz de saida xout */
/* Saida: Tem valor de retorno vazio. Os resultados sao  retornados no vetor tout e na matriz xout ao final da integracao. */

void rungeKutta4(int neqs, int nsteps, double dt,  double x0[], double tout[], double **xout){
  int i, j;
  
  double k[3][neqs]; // matriz que armazena os parametros k_i do runge-kutta. Tem dimensao 4 X neqs
  double dx[neqs]; // vetor que armazena os valores das derivadas de x. Dimensao neqs.
  double x[neqs]; // vetor que armazena os valores das solucoes num passo dado. Dimensao neqs.
  double xtemp[neqs]; // vetor de apoio que armazena valores de resultados intermediarios da integracao. Dimensao neqs.
  
  // imprime tamanho do passo no tempo
  printf ("passo no tempo = %f\n", dt);
  
  // inicializa valores iniciais na matriz de resultados
  for ( i = 0; i < neqs; i++){
    xout[0][i] = x0[i];
  }
  
  // inicializa o vetor de tempos como dt
  tout[0] = dt;
  
  // copia valores iniciais para o vetor temporario x
  for ( i = 0; i < neqs; i++){
    x[i] =   xout[0][i];
  }
  
  // inicio do processo de integracao
  for ( j = 1; j < nsteps; j++){
    // calcula as derivadas da funcao fun no ponto x
    fun(x, dx); 
    // calcula o valor de k0 e armazena o valor do novo x em xtemp
    for ( i = 0; i < neqs; i++){
      k[0][i] = dt*dx[i];
      xtemp[i] = x[i] + k[0][i]/2.0;
    }
    
    //calcula as derivadas da funcao fun no ponto (x + k0/2)
    fun(xtemp, dx); 
    // calcula o valor de k1 e armazena o valor do novo x em xtemp
    for ( i = 0; i < neqs; i++){
      k[1][i] = dt*dx[i];
      xtemp[i] = x[i] + k[1][i]/2.0;
    }
    
    //calcula as derivadas da funcao fun no ponto (x + k1/2)
    fun(xtemp, dx);
    // calcula o valor de k2 e armazena o valor do novo x em xtemp
    for ( i = 0; i < neqs; i++){
      k[2][i] = dt*dx[i];
      xtemp[i] = x[i] + k[2][i]/2.0;
    }

    // calcula as derivadas da funcao fun no ponto x + k2
    fun(xtemp, dx);
    // calcula o valor de k3
    for ( i = 0; i < neqs; i++){
      k[3][i] = dt*dx[i];
    }
    
    // faz o calculo final de x_i no tempo t = j.
    for ( i = 0; i < neqs; i++){
      xout[j][i] = x[i] + (k[0][i] + k[3][i] + (k[1][i] + k[2][i])*2.0)/(6.0);
      x[i] = xout[j][i];
    }
    // atualiza o valor do tempo tout para a proxima iteracao. O valor de t nao e necessario ao calculo, 
    // guardado aqui simplesmente para efeitos de plotagem de dados
    tout[j] = dt + tout[j-1] ;
  }
}


//Rotina principal que faz chamada a funcao rungeKutta, e em seguida imprime vetor com saida
int main(){
  
  int i; // variavel dummie
  int neqs; // armazena o numero que equacoes do sistema 
  int nsteps; // armazena o numero de passos utilizados no processo de integracao
  double dt; //armazena o tamanho do passo no tempo
  double *tout; // ponteiro para vetor que guarda o valor de cada passo no tempo
  double *xini; // ponteiro para vetor que armazena a condicao inicial do sistema
  double **xout; // matriz que armazena os valores da integracao a cada tempo t para cada variavel x_i

  
  // inicializacao de variaveis
  neqs = NEQS;  // numero de equacoes do sistema
  nsteps = NSTEP; // numero de passos de integracao
  dt = (TEND - TSTART)/((double)(NSTEP)); // dt calculado localmente de acordo com parametros passados.

  
  // alocando vetores
  tout = (double *) malloc (nsteps*sizeof(double)); // aloca vetor de passos no tempo com dimensao nsteps
  xini = (double *) malloc (neqs*sizeof(double)); // aloca vetor de condicoes iniciais com dimensao neqs
  // aloca matriz de resultados xout com dimensao neqs x nsteps
  xout = (double **) malloc (nsteps*sizeof(double *)); 
  for (i = 0; i < nsteps; i++) {
    xout[i] = (double *) malloc (neqs*sizeof(double));
  }
  
  // inicializando valores iniciais
  xini[0] = 1.0;
  xini[1] = 1.0;
  xini[3] = 1.0;
  
  // faz a chamada a funcao de integracao
  rungeKutta4(neqs, nsteps, dt, xini, tout, xout);  
  
  // imprime resultados na saida padrao
  for (i = 0; i < nsteps; i++){
    printf (" %f    %f    %f    %f\n", tout[i], xout[i][0], xout[i][1], xout[i][2]);
  }
  
  return 0;
} 

