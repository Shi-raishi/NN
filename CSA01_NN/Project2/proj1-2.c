(rand()%10000/10001.0)
#define randomize()   srand((unsigned int)time(NULL))
#define step(x)       ((x >= 0.0) ? 1 : -1)

double x[n_sample][N]={
  {10,2,-1},
  {2,-5,-1},
  {-5,5,-1},
};
double d[n_sample][R]={
  {1,-1,-1},
  {-1,1,-1},
  {-1,-1,1},
};
double w[R][N];
double o[R];
double o2[R];

void Initialization(void);
void FindOutput(int);
void PrintResult(void);

int main(){
  int    i,j,p,q=0;
  double Error=DBL_MAX;
  double delta;

  Initialization();
  while(Error>desired_error){
    q++;
    Error=0;
    for(p=0; p<n_sample; p++){
      FindOutput(p);
      for(i=0;i<R;i++){
	Error+=0.5*pow(d[p][i]-o[i],2.0);
      }
      for(i=0;i<R;i++){
	delta=(d[p][i]-o[i])*(1-o[i]*o[i])/2;
	for(j=0;j<N;j++){
	  w[i][j]+=eta*delta*x[p][j];
	}
      }
    }
    printf("Error in the %d-th learning cycle=%f\n",q,Error);
  }
  PrintResult();

  i=0,j=0,p=0,q=0;
  Error=DBL_MAX;

  Initialization();
  while(Error>desired_error){
    q++;
    Error=0;
    for(p=0; p<n_sample; p++){
      FindOutput(p);
      for(i=0;i<R;i++){
	Error+=0.5*pow(d[p][i]-o2[i],2.0);
      }
      for(i=0;i<R;i++){
	delta=(d[p][i] - o2[i]);
	for(j=0;j<N;j++){
	  w[i][j]+=eta*delta*x[p][j];
	}
      }
    }
    printf("Error in the %d-th learning cycle=%f\n",q,Error);
  }
  PrintResult();

}

/*************************************************************/
/* Initialization of the connection weights                  */
/*************************************************************/
void Initialization(void){
  int i,j;
  randomize();
  for(i=0;i<R;i++)
    for(j=0;j<N;j++)
      w[i][j]=frand()-0.5;
}

/*************************************************************/
/* Find the actual outputs of the network                    */
/*************************************************************/
void FindOutput(int p){
  int    i,j;
  double temp;

  for(i=0;i<R;i++){
    temp=0;
    for(j=0;j<N;j++){
      temp+=w[i][j]*x[p][j];
    }
    o[i]=sigmoid(temp);
    o2[i]=step(temp);
  }
}


/*************************************************************/
/* Print out the final result                                */
/*************************************************************/
void PrintResult(void){
  int i,j;

  printf("\n\n");
  printf("The connection weights are:\n");
  for(i=0;i<R;i++){
    for(j=0;j<N;j++)
      printf("%5f ",w[i][j]);
    printf("\n");
  }
  printf("\n\n");

  FindOutput(0);
  printf("Sigmoid:%f Step:%f\n" ,o[0],o2[0]);
  FindOutput(1);
  printf("Sigmoid:%f Step:%f\n" ,o[1],o2[1]);
  FindOutput(2);
  printf("Sigmoid:%f Step:%f\n" ,o[2],o2[2]);

}

~
