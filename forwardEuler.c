#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NEQS 3 // numero de equacoes do sistema de EDOs
#define TSTART 0 // tempo de inicio de integracao
#define TEND 2000 // tempo final de integracao
#define NSTEP 200000 // numero de passos da integracao


/* Funcao que implementa o sistema de EDOs a ser resolvido por runge-kutta de forma que dx/dt = f(x), x[NEQS]. */
/* Entrada: Recebe um ponteiro para um vetor x de dimensao neqs representando um ponto do espaco de fase,  */
/* e um ponteiro para uma vetor dx que armazena o valor das derivadas calculadas neste ponto x. */
/* Saida: Retorna saida vazia. Os valores calculados sao retornados no vetor dx passado na entrada. */

void fun(double x[], double dx[]){
  double A = -0.553;
  double B = 0.451;
  double C = 0.051;
  
  dx[0] = A*x[1]*x[2];
  dx[1] = B*x[0]*x[2];
  dx[2] = C*x[0]*x[1];
}


void forwardEuler (int neqs, int nsteps, double dt, double x0[], double tout[], double **xout){

  int i, j, k, l, m;
  double A = -0.553;
  double B = 0.451;
  double C = 0.051;
  double D[neqs][neqs];
  double xtemp[neqs];
  
  // imprime tamanho do passo no tempo
  printf ("passo no tempo = %f\n", dt);
  
  // inicializa o vetor de tempos como dt
  tout[0] = dt;
  
  for ( i = 0; i < neqs; i++){
    xtemp[i] = x0[i];
    xout[0][i] = 0;
  }

  for ( i = 0; i < nsteps; i++ ){
    for ( j = 0; j < neqs; j++){
      xout[i][j] = 0;
    }
  }
  
  // inicio do processo de integracao
  for ( j = 1; j < nsteps; j++){
    
    // Define propagador discretizado e linearizado do modelo de Lorenz
    D[0][0] = 1;
    D[0][1] = A*dt*xtemp[2];
    D[0][2] = A*dt*xtemp[1];
    D[1][0] = B*dt*xtemp[3];
    D[1][1] = 1;
    D[1][2] = B*dt*xtemp[0];
    D[2][0] = C*dt*xtemp[1];
    D[2][1] = C*dt*xtemp[0];
    D[2][2] = 1;

    // realiza uma multiplicacao de matriz entre x(k) e D e calcula valor de x(k+1)t
    for ( k = 0; k < neqs; k++){
      for ( l = 0; l < neqs; l++){
	xout[j][k] += D[k][l] * xtemp[l];
	//	printf ("xout[%d][%d] = %f\n", j, k, xout[j][k]);
      }
    }

    
    // atualiza o valor do tempo tout para a proxima iteracao. O valor de t nao e necessario ao calculo, 
    // guardado aqui simplesmente para efeitos de plotagem de dados
    tout[j] = dt + tout[j-1];
    
    for ( i = 0; i < neqs; i++){
      xtemp[i] = xout[j][i];
    }
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
  xini[1] = 0.1;
  xini[3] = 0.0;
  
  // faz a chamada a funcao de integracao
  //  orwardEuler (int neqs, int nsteps, double dt, double x0[], double tout[], double **xout){
    forwardEuler(neqs, nsteps, dt, xini, tout, xout);  

  for ( i = 0; i < nsteps; i++){
    printf (" %f    %f    %f    %f\n", tout[i], xout[i][0], xout[i][1], xout[i][2]);
  }
  
  return 0;
} 

