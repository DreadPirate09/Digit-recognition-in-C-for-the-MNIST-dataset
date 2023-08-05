#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct dataFromFile{
	char** lines;
	int nrlines;
	int nrcols;
};

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
			printf("%.6lf ",matrix[i][j]);
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

int* ReLU_deriv(float* array, int len){
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
	FILE* fp;
	struct dataFromFile dff;
	dff.nrlines = 0;
	dff.nrcols = 0;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen("train.csv","r");

	dff.lines = (char**)malloc(sizeof(char*)*42004);

	while ((read = getline(&line, &len, fp)) != -1) {
        dff.lines[dff.nrlines] = (char*)malloc(sizeof(char)*(int)read);
        strncpy(dff.lines[dff.nrlines],line,read);
        dff.nrcols = read;
        dff.nrlines++;
    }
    fclose(fp);
    if (line)
        free(line);
    return dff;
}

int main(){

	// float array[10] = {0.63,-0.41,-0.22,0.53,-0.14,0.61,0.82,-0.22,-0.11,-0.32};
	// float xxarray[10] = {1,4,3,2,5,6,7,8,9,0};
	// float *dyn = giveMeArrayFromStack(xxarray,10);

	// float *x = ReLU(array,10);

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

	// float **dotMatrix1 = giveMeAMatrixNM(3,3);
	// for(int i=0;i<3;i++){
	// 	for(int j=0;j<3;j++){
	// 		dotMatrix1[i][j] = j+1;
	// 	}
	// }

	// printMatrix(dotMatrix1,3,3);

	// float **dotMatrix2 = giveMeAMatrixNM(2,5);
	// float matrixSoft[2][5] = {{3,-3,-0.3,2,3},{1,2,0,-2,3}};

	// for(int i=0;i<2;i++){
	// 	for(int j=0;j<5;j++){
	// 		dotMatrix2[i][j] = matrixSoft[i][j];
	// 	}
	// }
	// printMatrix(softMax(dotMatrix2,2,5),2,5);
	// printMatrix(oneHot(dyn,10),10,10);
	
	// printMatrix(dotProduct(dotMatrix1,dotMatrix2,3,3,3,2),3,2);

	struct dataFromFile dff = readTrain();
	printf("nr of lines : %d\n",dff.nrlines);
	for(int i=0;i<dff.nrlines;i++){
		printf("%s\n",dff.lines[i]);
	}

	

	return 0;
}