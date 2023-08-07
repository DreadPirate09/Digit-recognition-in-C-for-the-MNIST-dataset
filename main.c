#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct dataFromFile;
struct numbersLine;
struct paramsLayerOne{
	float** W1;
	float** b1;
	float** W2;
	float** b2;
};

float getAccuracy(float *array1, float *array2, int len);
float **giveMeAMatrixNM(int n, int m);
float argmax(float *array, int len);
float getNumber(char* str, int len);
struct numbersLine transformCSVNumbersToFloatsArray(char* line, int len);
float** addMatrix(float** matrix1, float** matrix2, int m, int n);
float** substractMatrix(float** matrix1, float** matrix2, int m, int n);
float** substractMatrixVal(float** matrix1, float val, int m, int n);
float** matrixTimesScalar(float** matrix, float scalar, int m, int n);
float** matrixTimesScalarArray(float** matrix, float* scalar, int m, int n);
struct numbersLine* matrixFromStringToFloat(struct dataFromFile DF);
float **giveMeZeros(int n, int m);
float maxValueFromArray(float *array, int len);
float** dotProduct(float** matrix1, float** matrix2, int m1, int n1, int m2, int n2);
float *giveMeArrayFromStack(float *array,int len);
void printArray(float *array, int len);
void printMatrix(float **matrix, int n, int m);
float* ReLU(float *array, int len);
float* ReLU_deriv(float* array, int len);
float** sumMatrixExp(float **array, int m, int n);
float** matrixExp(float **array, int m ,int n);
float** softMax(float **array, int m, int n);
float** getTranspose(float **matrix, int n, int m);
float** oneHot(float* Y, int len);
struct dataFromFile readTrain();
struct paramsLayerOne updateParams(float** W1, float** b1,float** W2, float** b2, int m, int n, float** dW1, float db1, float** dW2, float db2, float alpha);

int main(){
	float** W1 = giveMeAMatrixNM(3,3);
	float** W2 = giveMeAMatrixNM(3,3);
	float** dW1 = giveMeAMatrixNM(3,3);
	float** dW2 = giveMeAMatrixNM(3,3);

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			W1[i][j] = (j+1);
			dW1[i][j] = (j+1);
			W2[i][j] = (j+1);
			dW2[i][j] = (j+1);
		}
	}

	float** b1 = giveMeAMatrixNM(3,1);
	float** b2 = giveMeAMatrixNM(3,1);

	for(int i=0;i<3;i++){
		b1[i][0] = i+1;
		b2[i][0] = i+1;
	}

	float db1 = 0.5;
	float db2 = 0.5;
	float alpha = 0.1;


	struct paramsLayerOne test;
	test = updateParams(W1,b1,W2,b2,3,3,dW1,db1,dW2,db2,alpha);

	printf("W1:\n");
	printMatrix(test.W1,3,3);
	printf("b1:\n");
	printMatrix(test.b1,3,1);
	printf("W2:\n");
	printMatrix(test.W2,3,3);
	printf("Wb2:\n");
	printMatrix(test.b2,3,1);
	

	return 0;
}







// =================================================================================================================================================================




struct dataFromFile{
	char** lines;
	int nrlines;
	int nrcols;
};

struct numbersLine {
	int nrValues;
	float value[785];
};

float getAccuracy(float *array1, float *array2, int len){
	float sum = 0;
	for(int i=0;i<len;i++){
		sum += array1[i] == array2[i] ? 1 : 0;
	}
	return (float)sum/len;
}

float **giveMeAMatrixNM(int n, int m){
	float ** matrix = (float**)malloc(n*sizeof(float*));
	for(int i=0;i<n;i++){
		matrix[i] = (float*)malloc(m*sizeof(float));
	}
	return matrix;
}

float argmax(float *array, int len){
	float max = 0;
	for(int i=0;i<len;i++){
		max = array[i] > max ? array[i] : max;
	}
	return max;
}

float getNumber(char* str, int len){
	float number = 0.0;
	for(int i=0;i<len;i++){
		number = number * 10 + str[i]-'0';
	}
	return number;
}

struct numbersLine transformCSVNumbersToFloatsArray(char* line, int len){
	printf("transform\n");
	//this si ment to be done on a training set with the shape of 42000x785 so we have min 785x3 size of characters that should be feed to the array 
	char new[785][3];
	struct numbersLine nrValues;
	nrValues.nrValues = 0;
	int nr = 0;
	char* chunk;
	chunk = strtok(line,",");
	while(chunk!=NULL){
		strncpy(new[nr],chunk,strlen(chunk));
		new[nr][strlen(chunk)] = '\0';
		nr++;
		chunk = strtok(NULL,",");
	}
	nrValues.nrValues = nr;
	for(int i=0;i<nr;i++){
		nrValues.value[i] = getNumber(new[i],strlen(new[i]));
	}
	return nrValues;
}

float** addMatrix(float** matrix1, float** matrix2, int m, int n){
	float** sum = giveMeAMatrixNM(m,n);
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			sum[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
	return sum;
}

float** substractMatrix(float** matrix1, float** matrix2, int m, int n){
	float** sum = giveMeAMatrixNM(m,n);
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			sum[i][j] = matrix1[i][j] - matrix2[i][j];
		}
	}
	return sum;
}

float** matrixTimesScalar(float** matrix, float scalar, int m, int n){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			matrix[i][j] = matrix[i][j] * scalar;
		}
	}
	return matrix;
}

float** matrixTimesScalarArray(float** matrix, float* scalar, int m, int n){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			matrix[i][j] = matrix[i][j] * scalar[i];
		}
	}
	return matrix;
}

struct numbersLine* matrixFromStringToFloat(struct dataFromFile DF){
	struct numbersLine* nrValues = malloc(sizeof(struct numbersLine) * DF.nrlines);
	for(int i=1;i<DF.nrlines;i++){
		printf("enter in the loop\n");
		nrValues[i] = transformCSVNumbersToFloatsArray(DF.lines[i], DF.nrcols);
		printf("%lf\n",nrValues[i].value[10]);
	}
	return nrValues;
}

float **giveMeZeros(int n, int m){
	float** zeros = (float**)malloc(sizeof(float*)*n);
	for(int i=0;i<n;i++){
		zeros[i] = (float*)malloc(sizeof(float)*m);
		for(int j=0;j<m;j++){
			zeros[i][j] = 0;
		}
	}
	return zeros;
}

float maxValueFromArray(float *array, int len){
	float max = 0;
	for(int i=0;i<len;i++){
		if(max < array[i])
			max = array[i];
	}
	printf("the max value from array with the len %d is %lf\n",len,max);
	return max;
}


float** dotProduct(float** matrix1, float** matrix2, int m1, int n1, int m2, int n2){
	float** dotProd = giveMeAMatrixNM(m2,n2);
	float sum = 0;
	if(n1 != m2){
		printf("the nr of cols of the first matrix is not equal with the number of rows of the second matrix!\n");
		exit(1);
	}

	for(int i=0;i<m1;i++){
		for(int k=0;k<n2;k++){
			for(int j=0;j<n1;j++){
				sum = sum + matrix1[i][j]*matrix2[j][k];
				// printf("%lf * %lf\n",matrix1[i][j],matrix2[j][k]);
			}
			dotProd[i][k] = sum;
			sum = 0;
		}
	}

	return dotProd;
}

float *giveMeArrayFromStack(float *array,int len){
	float* dynamicArray = (float*)malloc(sizeof(float)*len);
	for(int i=0;i<len;i++){
		dynamicArray[i] = array[i];
	}
	return dynamicArray;
}

void printArray(float *array, int len){
	for(int i=0;i<len;i++){
		printf("%lf ",array[i]);
	}
}

void printMatrix(float **matrix, int n, int m){
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			printf("%.6lf ",matrix[i][j]);
		}
		printf("\n");
	}
}

float* ReLU(float *array, int len){
	float *new = (float*)malloc(len*sizeof(float));
	for(int i = 0; i<len;i++){
		if(array[i] > 0.0){
			new[i] = array[i];
		}else{
			new[i] = 0.0;
		}
	}
	return new;
}

float* ReLU_deriv(float* array, int len){
		float *new = (float*)malloc(len*sizeof(float));
	for(int i = 0; i<len;i++){
		if(array[i] > 0.0){
			new[i] = 1;
		}else{
			new[i] = 0.0;
		}
	}
	return new;
}

float** sumMatrixExp(float **array, int m, int n){
	float** new = giveMeAMatrixNM(1,n);
	for(int i=0;i<n;i++){
		new[0][i] = 0;
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			new[0][j] = new[0][j] + exp((float)array[i][j]);
		}
	}

	return new;
}

float** matrixExp(float **array, int m ,int n){
	float** new = giveMeAMatrixNM(m,n);
	for(int i = 0;i<m;i++){
		for(int j=0;j<n;j++){
			new[i][j] = exp((float)array[i][j]);
		}
	}
	return new;
}

float** softMax(float **array, int m, int n){
	float** new = (float**)malloc(m*sizeof(float*));
	float** matrix_Exp = matrixExp(array,m,n);
	float** sum_Matrix_Exp = sumMatrixExp(array,m,n);
	printMatrix(matrix_Exp,m,n);
	printMatrix(sum_Matrix_Exp,1,n);
	for(int i=0;i<m;i++){
		new[i] = (float*)malloc(n*sizeof(float));
		for(int j = 0; j < n; j++){
			new[i][j] = matrix_Exp[i][j]/sum_Matrix_Exp[0][j];
		}
	}
	return new;
}


float** getTranspose(float **matrix, int n, int m){
	float **transpose = (float**)malloc(m*sizeof(float *));
	for(int i=0;i<m;i++){
		transpose[i] = (float*)malloc(n*sizeof(float));
		for(int j=0;j<n;j++){
			transpose[i][j] = matrix[j][i];
		}
	}
	return transpose;
}

float** oneHot(float* Y, int len){
	float** one_hot_y = giveMeZeros(len, maxValueFromArray(Y, len));
	for(int i=0;i<len;i++){
		one_hot_y[i][(int)Y[i]] = 1;
	}
	return getTranspose(one_hot_y,len,len);
}

struct dataFromFile readTrain(){
	printf("read the dataset\n");
	FILE* fp = NULL;
	struct dataFromFile dff;
	dff.nrlines = 0;
	dff.nrcols = 0;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	printf("Try to open\n");
	fp = fopen("train.csv","r");
	printf("Opened\n");
	if(fp == NULL){
		printf("The file is open somewhere else\n");
		exit(1);
	}

	dff.lines = (char**)malloc(sizeof(char*)*42004);

	while ((read = getline(&line, &len, fp)) != -1) {
		printf("Start while\n");
        dff.lines[dff.nrlines] = (char*)malloc(sizeof(char)*read+1);
        strncpy(dff.lines[dff.nrlines],line,read);
        printf("here we go\n");
        dff.lines[dff.nrlines][read] = '\0';
        printf("PA\n");
        dff.nrcols = read;
        dff.nrlines++;
    }
    printf("Done with the while\n");
    fclose(fp);
    if (line)
        free(line);
    printf("Done!\n");
    return dff;
}

float** substractMatrixVal(float** matrix1, float val, int m, int n){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			matrix1[i][j] = matrix1[i][j] - val;
		}
	}
	return matrix1;
}


struct paramsLayerOne updateParams(float** W1, float** b1,float** W2, float** b2, int m, int n, float** dW1, float db1, float** dW2, float db2, float alpha){
	W1 = substractMatrix(W1, matrixTimesScalar(dW1, alpha, m, n), m, n);
	b1 = substractMatrixVal(b1, (alpha * db1), m, 1);
	W2 = substractMatrix(W2, matrixTimesScalar(dW2, alpha, m, n), m, n);
	b2 = substractMatrixVal(b2, (alpha * db2), m, 1);

	struct paramsLayerOne pack;
	pack.W1 = W1;
	pack.b1 = b1;
	pack.W2 = W2;
	pack.b2 = b2;
	return pack;
}

