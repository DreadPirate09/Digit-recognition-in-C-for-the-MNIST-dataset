#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#define DATA_SHAPE_M 42000
#define DATA_SHAPE_N 785



struct dataFromFile{
	char** lines;
	int nrlines;
	int nrcols;
};

struct numbersLine {
	int nrValues;
	float value[785];
};
struct initParams{
	float** W1;
	float** W2;
	float** b1;
	float** b2;
};

struct paramsLayerOne{
	float** W1;
	float** b1;
	float** W2;
	float** b2;
};

struct forwardPropData{
	float** Z1;
	float** A1;
	float** Z2;
	float** A2;
};

struct backwordPropData{
	float** dW1;
	float db1;
	float** dW2;
	float db2;
};

float getAccuracy(float *array1, float *array2, int len);
float **giveMeAMatrixNM(int n, int m);
float argmax(float *array, int len);
float getNumber(char* str, int len);
struct numbersLine transformCSVNumbersToFloatsArray(char* line, int len);
float** addMatrix(float** matrix1, float** matrix2, int m1, int n1,int m2, int n2);
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
float** ReLU(float **array, int x, int y);
float** ReLU_deriv(float** array, int x, int y);
float** sumMatrixExp(float **array, int m, int n);
float sumMatrix(float** matrix, int m ,int n);
float** matrixExp(float **array, int m ,int n);
float** softMax(float **array, int m, int n);
float** getTranspose(float **matrix, int n, int m);
float** oneHot(float* Y, int len);
struct dataFromFile readTrain();
struct paramsLayerOne updateParams(float** W1, float** b1,float** W2, float** b2, int m, int n, float** dW1, float db1, float** dW2, float db2, float alpha);
float **giveMeARandomMatrixNM(int n, int m);
struct initParams getInitParams();
struct forwardPropData forwardProp(float** W1, float**b1, float** W2, float** b2, int m1, int n1, int m2, int n2,float** X,int xm,int xn);
struct backwordPropData backwordProp(float** Z1,float ** A1,float** Z2,float** A2,int m,int n,float** W1,float**W2,int wm,int wn,float** X,float* Y,int xm,int xn,int ym);
float getPredictions(float **array, int m);
float makePredictions(float** X, int xm,int xn,float** W1, float** b1, float** W2, float** b2,int m1,int n1,int m2,int n2);
struct paramsLayerOne gradientDesccent(float **X, float* Y,float alpha,int iterations,int mx,int nx,int my);

int main(){
	// float** W1 = giveMeAMatrixNM(3,3);
	// float** W2 = giveMeAMatrixNM(3,3);
	// float** dW1 = giveMeAMatrixNM(3,3);
	// float** dW2 = giveMeAMatrixNM(3,3);

	// for(int i=0;i<3;i++){
	// 	for(int j=0;j<3;j++){
	// 		W1[i][j] = (j+1);
	// 		dW1[i][j] = (j+1);
	// 		W2[i][j] = (j+1);
	// 		dW2[i][j] = (j+1);
	// 	}
	// }

	// float** b1 = giveMeAMatrixNM(3,1);
	// float** b2 = giveMeAMatrixNM(3,1);

	// for(int i=0;i<3;i++){
	// 	b1[i][0] = i+1;
	// 	b2[i][0] = i+1;
	// }

	// float db1 = 0.5;
	// float db2 = 0.5;
	// float alpha = 0.1;


	// struct paramsLayerOne test;
	// test = updateParams(W1,b1,W2,b2,3,3,dW1,db1,dW2,db2,alpha);

	// printf("W1:\n");
	// printMatrix(test.W1,3,3);
	// printf("b1:\n");
	// printMatrix(test.b1,3,1);
	// printf("W2:\n");
	// printMatrix(test.W2,3,3);
	// printf("Wb2:\n");
	// printMatrix(test.b2,3,1);
	
	// printMatrix(giveMeARandomMatrixNM(10,10),10,10);

	// struct initParams x = getInitParams();
	// printMatrix(x.W1,10,784);
	// float** Ww1 = giveMeAMatrixNM(6,6);
	// float** bb1 = giveMeAMatrixNM(6,1);
	// float** Ww2 = giveMeAMatrixNM(6,6);
	// float** bb2 = giveMeAMatrixNM(6,1);
	// float** Xx = giveMeAMatrixNM(6,10);

	// for(int i=0;i<6;i++){
	// 	bb1[i][0] = (float)(i+1)/10;
	// 	bb2[i][0] = (float)i+1;
	// 	for(int j=0;j<6;j++){
	// 		Ww1[i][j] = (float)(j+1)/10;
	// 		Ww2[i][j] = (float)(j+1)/10;
	// 	}
	// }

	// for(int i=0;i<6;i++){
	// 	for(int j=0;j<10;j++){
	// 		Xx[i][j] = (float)(j+1)/10;
	// 		if( j == 9){
	// 			Xx[i][j] = (float)0.1;
	// 		}
	// 	}
	// }

	// float** z1 = giveMeAMatrixNM(10,10);
	// float** z2 = giveMeAMatrixNM(10,10);
	// float** a1 = giveMeAMatrixNM(10,10);
	// float** a2 = giveMeAMatrixNM(10,10);
	// float** w1 = giveMeAMatrixNM(10,10);
	// float** w2 = giveMeAMatrixNM(10,10);
	// float** x = giveMeAMatrixNM(6,10);
	// float* y = (float*)malloc(sizeof(float)*10);
	// printf("prepare matrixes ... ");
	// for(int i =0; i<10;i++){
	// 	y[i] = i;
	// 	for(int j=0;j<10;j++){
	// 			if(i<6){
	// 				x[i][j] = j;
	// 			}
	// 			z1[i][j] = j != 9 ? j+1 : 0;
	// 			z2[i][j] = j != 9 ? j+1 : 0;
	// 			a1[i][j] = j != 9 ? j+1 : 0;
	// 			a2[i][j] = j != 9 ? j+1 : 0;;
	// 			w1[i][j] = j != 9 ? j+1 : 0;;
	// 			w2[i][j] = j != 9 ? j+1 : 0;;
	// 	}
	// }

	// printf("matrixes prepared\n");

	// struct backwordPropData result = backwordProp(z1,a1,z2,a2,10,10,w1,w2,10,10,x,y,6,10,10);

	// printMatrix(result.dW1,10,6);
	// printf("%f\n",result.db1);
	// printMatrix(result.dW2,10,10);
	// printf("%f\n",result.db2);

	// // struct forwardPropData res = forwardProp(Ww1,bb1,Ww2,bb2,6,6,6,1,Xx,6,10);

	// float** predictionList = giveMeAMatrixNM(10,1);
	// predictionList[0][0] = 4.32969381e-07;
	// predictionList[1][0] = 9.73976793e-01;
	// predictionList[2][0] = 3.55005386e-03;
	// predictionList[3][0] = 4.33718600e-03;

	// printf("Prediction: [%d]",(int)getPredictions(predictionList,4));

	struct dataFromFile dff = readTrain();
	struct numbersLine* numbers = matrixFromStringToFloat(dff);
	for(int i=0;i<DATA_SHAPE_M;i++){
		printf("%f\n",numbers[i].value[0]);
	}

	float** data_dev = giveMeAMatrixNM(1000,DATA_SHAPE_N);
	for(int i=0;i<1000;i++){
		for(int j=0;j<DATA_SHAPE_N;j++){
			data_dev[i][j] = numbers[i].value[j];
		}
	}
	float** data_dev_T = giveMeAMatrixNM(DATA_SHAPE_N,1000);
	data_dev_T = getTranspose(data_dev,1000,DATA_SHAPE_N);
	int data_dev_T_M = DATA_SHAPE_N;
	int data_dev_T_N = 1000;

	float* Y_dev = (float*)malloc(sizeof(float)*data_dev_T_N);
	for(int i=0;i<data_dev_T_N;i++){
		Y_dev[i] = data_dev_T[0][i];
	}

	printf("Y_dev shape: [%d]\n",data_dev_T_N);

	float** X_dev = giveMeAMatrixNM(data_dev_T_M-1,DATA_SHAPE_N);
	for(int i=0;i<data_dev_T_M-1;i++){
		for(int j=0;j<data_dev_T_N;j++){
			X_dev[i][j] = data_dev_T[i+1][j];
			X_dev[i][j] = X_dev[i][j] / 255.0;
		}
	}
	printf("X_dev shape: [%d %d]\n",data_dev_T_M-1,data_dev_T_N);


	float** data_train = giveMeAMatrixNM(DATA_SHAPE_M-1000,DATA_SHAPE_N);
	for(int i=0;i<DATA_SHAPE_M-1000;i++){
		for(int j=0;j<DATA_SHAPE_N;j++){
			data_train[i][j] = numbers[i+1000].value[j];
		}
	}
	float** data_train_T = giveMeAMatrixNM(DATA_SHAPE_N,DATA_SHAPE_M-1000);
	data_train_T = getTranspose(data_train,DATA_SHAPE_M-1000,DATA_SHAPE_N);
	int data_train_T_M = DATA_SHAPE_N;
	int data_train_T_N = DATA_SHAPE_M-1000;

	float* Y_train = (float*)malloc(sizeof(float)*data_train_T_N);
	for(int i=0;i<data_train_T_N;i++){
		Y_train[i] = data_train_T[0][i];
	}
	printf("Y_train shape: [%d]\n",data_train_T_N);

	float** X_train = giveMeAMatrixNM(data_train_T_M-1,data_train_T_N);
	for(int i=0;i<data_train_T_M-1;i++){
		for(int j=0;j<data_train_T_N;j++){
			X_train[i][j] = data_train_T[i+1][j];
			X_train[i][j] = X_train[i][j] / 255.0;
		}
	}

	printf("X_train shape: [%d %d]\n",data_train_T_M-1,data_train_T_N);


	struct paramsLayerOne yep = gradientDesccent(X_train,Y_train,0.10,500,data_train_T_M-1,data_train_T_N,data_train_T_N);
	return 0;
}







// =================================================================================================================================================================



float sumMatrix(float** matrix, int m ,int n){
	float sum = 0;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			sum += matrix[i][j];
		}
	}
	return sum;
}

struct initParams getInitParams(){
	struct initParams x;
	x.W1 = substractMatrixVal(giveMeARandomMatrixNM(10,784),0.5,10,784);
	x.b1 = substractMatrixVal(giveMeARandomMatrixNM(10,1),0.5,10,1);
	x.W2 = substractMatrixVal(giveMeARandomMatrixNM(10,784),0.5,10,784);
	x.b2 = substractMatrixVal(giveMeARandomMatrixNM(10,1),0.5,10,1);
	return x;
}


float getAccuracy(float *array1, float *array2, int len){
	float sum = 0;
	for(int i=0;i<len;i++){
		sum += array1[i] == array2[i] ? 1 : 0;
	}
	return (float)sum/len;
}

float getPredictions(float **array, int m){
	float* inj = (float*)malloc(sizeof(float)*m);
	for(int i=0;i<m;i++){
			inj[i] = array[i][0];
	}
	return argmax(inj,m);
}

float makePredictions(float** X, int xm,int xn,float** W1, float** b1, float** W2, float** b2,int m1,int n1,int m2,int n2){
	struct forwardPropData result = forwardProp(W1, b1, W2, b2, m1, n1, m2, n2,X,xm,xn);
	float prediction = getPredictions(result.A2,m1);
	return prediction;
}

float **giveMeAMatrixNM(int n, int m){
	float ** matrix = (float**)malloc(n*sizeof(float*));
	for(int i=0;i<n;i++){
		matrix[i] = (float*)malloc(m*sizeof(float));
	}
	return matrix;
}

float **giveMeARandomMatrixNM(int n, int m){
	float ** matrix = (float**)malloc(n*sizeof(float*));
	srand(time(NULL));
    // Generate a random number between 0 and 1
    double randomValue = (double)rand() / RAND_MAX;
	for(int i=0;i<n;i++){
		matrix[i] = (float*)malloc(m*sizeof(float));
		for(int j=0;j<m;j++){
			matrix[i][j] = randomValue;
			randomValue =  (double)rand() / RAND_MAX;
		}
	}
	return matrix;
}

float argmax(float *array, int len){
	float max = 0;
	float index = 0;
	for(int i=0;i<len;i++){
		if(max<array[i]){
			max = array[i];
			index = i;
		}
	}
	return index;
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

float** addMatrix(float** matrix1, float** matrix2, int m1, int n1, int m2, int n2){
	float** sum = giveMeAMatrixNM(m1,n1);
	if( n2 == 1 ){
		for(int i=0;i<m1;i++){
			for(int j=0;j<n1;j++){
				sum[i][j] = matrix1[i][j] + matrix2[i][0];
			}
		}
	} else {
		for(int i=0;i<m1;i++){
			for(int j=0;j<n1;j++){
				sum[i][j] = matrix1[i][j] + matrix2[i][j];
			}
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

float** ReLU(float **array, int x, int y){
	float **new = (float**)malloc(x*sizeof(float*));
	for(int i = 0; i<x;i++){
		new[i] = (float*)malloc(sizeof(float)*y);
		for(int j=0;j<y;j++){
			if(array[i][j] > 0.0){
				new[i][j] = array[i][j];
			}else{
				new[i][j] = 0.0;
			}
		}
	}
	return new;
}

float** ReLU_deriv(float** array, int x, int y){
	float **new = giveMeAMatrixNM(x,y);
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
				new[i][j] = array[i][j] > 0 ? 1 : 0;
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

float** matrixTimesMatrix(float **matrix1,float **matrix2, int m ,int n){
	float** new = giveMeAMatrixNM(m,n);
	for(int i = 0;i<m;i++){
		for(int j=0;j<n;j++){
				new[i][j] = matrix1[i][j] * matrix2[i][j];
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
        dff.lines[dff.nrlines] = (char*)malloc(sizeof(char)*read+1);
        strncpy(dff.lines[dff.nrlines],line,read);
        dff.lines[dff.nrlines][read] = '\0';
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

struct forwardPropData forwardProp(float** W1, float**b1, float** W2, float** b2, int m1, int n1, int m2, int n2,float** X,int xm,int xn){
	struct forwardPropData result;

	result.Z1 = addMatrix(dotProduct(W1,X,m1,n1,xm,xn),b1,m1,xn,m1,1);
	result.A1 = ReLU(result.Z1,m1,xn);
	result.Z2 = addMatrix(dotProduct(W2, result.A1,m1,m1,m1,xn),b2,m1,xn,m1,1);
	result.A2 = softMax(result.Z2, xm,xn);

	return result;
}

// /W1, b1, W2, b2, dW1, db1, dW2, db2, alpha

// Z1 : (10, 41000)
// A1 : (10, 41000)
// Z2 : (10, 41000)
// A2 : (10, 41000)
// W1 : (10, 784)
// W2 : (10, 10)
// X : (784, 41000)
// Y : (41000,)

// --------------------

// one_hot_Y :  (10, 41000)
// dZ2 : (10, 41000)
// dW2 : (10, 10)
// db2 : ()
// dZ1 : (10, 41000)

struct backwordPropData backwordProp(float** Z1,float ** A1,float** Z2,float** A2,int m,int n,float** W1,float**W2,int wm,int wn,float** X,float* Y,int xm,int xn,int ym){
	float** one_hot_y = oneHot(Y,ym);
	float** dZ2 = substractMatrix(A2,one_hot_y,m,n);
	float** dW2 = matrixTimesScalar(dotProduct(dZ2, getTranspose(A1,m,n), m, n, n ,m), (float)1/DATA_SHAPE_M, m, m);
	float db2 = 1.0 / DATA_SHAPE_M * sumMatrix(dZ2,m,n);
	float** dZ1 = matrixTimesMatrix(dotProduct(getTranspose(W2, wm, wn), dZ2,wn,wm,m,n), ReLU_deriv(Z1,m ,n), m,n);
	float** dW1 = matrixTimesScalar(dotProduct(dZ1, getTranspose(X,xm,xn), m, n, n,m), (float)1/DATA_SHAPE_M, m, m);
	float db1 = 1.0 / DATA_SHAPE_M * sumMatrix(dZ1,m,n);
	struct backwordPropData data;
	data.dW1 = dW1;
	data.db1 = db1;
	data.dW2 = dW2;
	data.db2 = db2;
	return data;
}


struct paramsLayerOne gradientDesccent(float **X, float* Y,float alpha,int iterations,int mx,int nx,int my){
	struct initParams initValues = getInitParams();
	struct paramsLayerOne result;
	result.W1 = initValues.W1;
	result.W2 = initValues.W2;
	result.b1 = initValues.b1;
	result.b2 = initValues.b2;
	for(int i=0;i<iterations;i++){
		printf("The sizes choosed:\n");
		printf("W1 size: %d %d, b1 size: %d, W2 size: %d %d, b2 size: %d, X size: %d %d",mx,nx,mx,nx,mx,nx);
		struct forwardPropData forwardData = forwardProp(result.W1, result.b1, result.W2, result.b2, 10, mx, 10, 10,X,mx,nx);
		struct backwordPropData backwordData = backwordProp(forwardData.Z1,forwardData.A1,forwardData.Z2,forwardData.A2,mx,nx,result.W1,result.W2,mx,nx,X,Y,mx,nx,my);
		result = updateParams(result.W1,result.b1,result.W2, result.b2, mx, nx, backwordData.dW1, backwordData.db1, backwordData.dW2, backwordData.db2, alpha);
	}
	return result;
}
