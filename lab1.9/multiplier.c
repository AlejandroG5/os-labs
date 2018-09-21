#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>

#define NUM_ROWS 2000
#define NUM_COLUMNS 2000
#define NUM_DATA NUM_COLUMNS*NUM_ROWS
#define MAX_LINE 80
#define A_PATH "matA.dat"
#define B_PATH "matB.dat"
#define nchar 255
#define NUM_THREADS 10
#define NUM_CYCLES NUM_ROWS/NUM_THREADS

typedef struct {
	int id;
	long * mat1;
	long * mat2;
}threads;

long* readMatrix(char*);
long* getColumn(int, long*);
long* getRow(int, long*);
int getLock(void);
int releaseLock(int);
long dotProduct(long *vec1, long *vec2);
long * multiply(long *matA, long *matB);
int saveResultMatrix(long  * result);
void * runner(void* row);

int NUM_BUFFERS;
long **buffers;
long * mresult;
char args[MAX_LINE /2 + 1];
long * matrix_4m;
long * matrix_2k;
pthread_mutex_t * mutexes;


long * matrix1;
long * matrix2;

long * multiply(long * matA, long * matB){
	int j;
	int limit,k;
	pthread_t tid [NUM_ROWS]; 	/* the thread identifier */
	pthread_attr_t attr; 		
	pthread_attr_init(&attr);
	memcpy(matrix1,matA,NUM_DATA*sizeof(long));
	memcpy(matrix2,matB,NUM_DATA*sizeof(long));
	limit=0;
	do{
		for (j = 0; j<NUM_THREADS; j++){ 
			pthread_create(&tid[j],&attr,runner,(void*)k);
			//printf("%d \n",k);
			k++;
		}
		for (j = 0; j <NUM_THREADS; j++){ 
			pthread_join(tid[j], NULL);
		}
	}while(limit++<(NUM_ROWS/NUM_THREADS)-1);
	free(matrix1);
	free(matrix2);
	printf("%ld \n",mresult[0]);	
	printf("%ld \n",mresult[NUM_DATA-1]);
	printf("salio");
	return 0;
}

void *runner(void *param){	
	int mutex_id,p,h,j,k;
	while(-1==(mutex_id=getLock()));
	long *row,*column;
	p=(int) param;
	//printf("hola %d  :",mutex_id);
	row=malloc(NUM_ROWS*sizeof(long));
	column=malloc(NUM_ROWS*sizeof(long));
	memcpy(row,getRow(p,matrix1),NUM_ROWS*sizeof(long));
	printf("%d \n",p);
	for(h=0;h<NUM_ROWS;h++){
		memcpy(column,getColumn(h,matrix2),NUM_ROWS*sizeof(long));
		//printf("%ld \n",dotProduct(row,column));
		buffers[mutex_id][h]=dotProduct(row,column);
	}
	for(j=0;j<NUM_ROWS;j++){
		mresult[NUM_ROWS*p+j]=buffers[mutex_id][j];
	}
	free(row);
	free(column);
	releaseLock(mutex_id);
	pthread_exit(0);
}

long * readMatrix(char *filename){
	int j;
	FILE *fp;
	char buff[nchar];
	fp=fopen(filename, "r");
	for(j=0;j<NUM_DATA;j++){
		fgets(buff,nchar,(FILE*)fp);
		matrix_4m[j]=(long)atoi(buff);     //saves .dat in the array of 4 000 000 values
	}
	fclose(fp);
	return matrix_4m;
}

long * getColumn(int col, long * matrix){	
	int j;
	for(j=0;j<NUM_COLUMNS;j++)matrix_2k[j]=matrix[j*NUM_COLUMNS+col];
	return(matrix_2k);
}

long * getRow(int row, long * matrix){
	int j;
	for(j=0;j<NUM_ROWS;j++)matrix_2k[j]=matrix[j+row*NUM_ROWS];
	return(matrix_2k);
}

int getLock(){
	int jl;
	for(jl=0;jl<NUM_BUFFERS;jl++){
		if(0==(pthread_mutex_trylock(&mutexes[jl]))){
			return jl;
		}
	}
	return -1;
}

int releaseLock(int a){
	if(0==(pthread_mutex_unlock(&mutexes[a]))){
		return 0;
	}	
	else {
		return -1;	
	}
}

int saveResultMatrix(long *result){
	int j;
	FILE *fp = fopen("result.dat","w");
	for(j=0;j<NUM_DATA;j++){
		fprintf(fp,"%ld\n",result[j]);
	}
	fclose(fp);
	return 0;
}

long dotProduct(long * vec1, long * vec2){
	int j;
	long dotp;
	dotp=0;
	for(j=0;j<NUM_ROWS;j++)dotp+=vec1[j]*vec2[j];
	return dotp;
}


int main (void){
	int i;
	long *matrixA,*matrixB,*matrixtest,*matrixtest2;
	printf("Introduce how many buffers you want: ");
	fgets(args, MAX_LINE ,stdin);
	NUM_BUFFERS=atoi(args);	
	matrixA=malloc(NUM_DATA*sizeof(long));				//Allocation for variables
	matrix_4m=malloc(NUM_DATA*sizeof(long));
	matrixB=malloc(NUM_DATA*sizeof(long));
	matrix1=malloc(NUM_DATA*sizeof(long));
	matrix2=malloc(NUM_DATA*sizeof(long));
	mresult=malloc(NUM_DATA*sizeof(long));
	matrix_2k=malloc(NUM_ROWS*sizeof(long));
	matrixtest=malloc(NUM_ROWS*sizeof(long));
	matrixtest2=malloc(NUM_ROWS*sizeof(long));
	buffers=malloc(NUM_BUFFERS*sizeof(long*));
	mutexes=malloc(NUM_BUFFERS*sizeof(pthread_mutex_t));
	//printf("%d \n",NUM_BUFFERS);
	for(i=0;i<NUM_BUFFERS;i++){
		buffers[i]=malloc(NUM_ROWS*sizeof(long));
	}
	memcpy(matrixA,readMatrix(A_PATH),NUM_DATA*sizeof(long));
	memcpy(matrixB,readMatrix(B_PATH),NUM_DATA*sizeof(long));
	memcpy(matrixtest,getRow(0,matrixA),NUM_ROWS*sizeof(long));
	memcpy(matrixtest2,getColumn(0,matrixB),NUM_ROWS*sizeof(long));
	//memcpy(matrixtest,getRow(1999,matrixA),NUM_ROWS*sizeof(long));
	printf("%ld \n",matrixA[0]);
	printf("%ld \n",matrixB[0]);
	printf("%ld \n",dotProduct(matrixtest,matrixtest2));
	memcpy(matrixtest,getRow(1999,matrixA),NUM_ROWS*sizeof(long));
	memcpy(matrixtest2,getColumn(1999,matrixB),NUM_ROWS*sizeof(long));
	printf("%ld \n",dotProduct(matrixtest2,matrixtest));
	multiply(matrixA,matrixB);
	memcpy(matrix_4m,mresult,NUM_DATA*sizeof(long));
	saveResultMatrix(matrix_4m);
	pthread_mutex_destroy(mutexes);
	pthread_mutex_destroy(mutexes);
}

