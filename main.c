#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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

float **giveMeAMatrixNM(int n, int m){
	float ** matrix = (float**)malloc(n*sizeof(float*));
	for(int i=0;i<n;i++){
		matrix[i] = (float*)malloc(m*sizeof(float));
	}
	return matrix;
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
				printf("%lf * %lf\n",matrix1[i][j],matrix2[j][k]);
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
			printf("%.2lf ",matrix[i][j]);
		}
		printf("\n");
	}
}
int* ReLU(float *array, int len){
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

float sumExp(float *array, int len){
	float summed = 0;
	for(int i=0;i<len;i++){
		summed = summed + exp(array[i]);
	}
	return summed;
}

float* softMax(float *array, int len){
	float *new = (float*)malloc(len*sizeof(float));
	for(int i=0;i<len;i++){
		new[i] = exp((float)array[i]) / sumExp(array,len);
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

int main(){

	float array[10] = {0.63,-0.41,-0.22,0.53,-0.14,0.61,0.82,-0.22,-0.11,-0.32};
	float xxarray[10] = {1,4,3,2,5,6,7,8,9,0};
	float *dyn = giveMeArrayFromStack(xxarray,10);

	float *x = ReLU(array,10);
	float *softmax = softMax(array, 10);

	// printArray(softmax, 10);

	// float **arrayMatrix = giveMeAMatrixNM(2,3);
	// for(int i=0;i<2;i++){
	// 	for(int j=0;j<3;j++){
	// 		arrayMatrix[i][j] = j;
	// 	}
	// }

	// printMatrix(arrayMatrix, 2,3);
	// printMatrix(getTranspose(arrayMatrix,1,3),3,1);

	// printMatrix(giveMeZeros(31,33),31,33);

	float **dotMatrix1 = giveMeAMatrixNM(3,3);
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			dotMatrix1[i][j] = j+1;
		}
	}

	printMatrix(dotMatrix1,3,3);

	float **dotMatrix2 = giveMeAMatrixNM(3,2);

	for(int i=0;i<3;i++){
		for(int j=0;j<2;j++){
			dotMatrix2[i][j] = j+1;
		}
	}

	// printMatrix(oneHot(dyn,10),10,10);
	
	printMatrix(dotProduct(dotMatrix1,dotMatrix2,3,3,3,2),3,2);
	

	return 0;
}