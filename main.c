#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

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

	// struct dataFromFile dff = readTrain();
	// printf("nr of lines : %d\n",dff.nrlines);
	// for(int i=0;i<dff.nrlines;i++){
	// 	printf("%s\n",dff.lines[i]);
	// }

	// printf("start\n");
	// struct numbersLine* value = matrixFromStringToFloat(dff);

	// printf("done");

	// float array1[11] = {1,2,13,5,6,5,7,8,9,0,1};
	// float array2[11] = {1,2,3,5,6,5,7,8,9,0,2};
	// printf("%.2f",getAccuracy(array1,array2,11));

	

	return 0;
}