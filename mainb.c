#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#define DATA_SHAPE_M 42000
#define DATA_SHAPE_N 784


struct Numbers {
	int val;
	int pixels[DATA_SHAPE_M];
};

// struct Numbers readTrain(){
// 	printf("read the dataset\n");
// 	FILE* fp = NULL;
// 	struct Numbers nrs;

// 	char* line = NULL;
// 	size_t len = 0;
// 	ssize_t read;

// 	printf("Try to open\n");
// 	fp = fopen("train.csv","r");
// 	printf("Opened\n");
// 	if(fp == NULL){
// 		printf("The file is open somewhere else\n");
// 		exit(1);
// 	}

// 	int nrlines = 0;

// 	while ((read = getline(&line, &len, fp)) != -1) {
// 		if(nrlines != 0){
// 	        nrs.val[dff.nrlines] = (char*)malloc(sizeof(char)*read+1);
// 	        strncpy(dff.lines[dff.nrlines],line,read);
// 	        dff.lines[dff.nrlines][read] = '\0';
// 	        printf("The nr cols is : %d",read);
// 	        nrlines++;
// 		} else {
// 			nrlines++;
// 		}
//     }

//     printf("Done with the while\n");
//     fclose(fp);
//     if (line)
//         free(line);
//     printf("Done!\n");
//     return dff;
// }

int getStrRetNumbers(char* line){
	char *pch;
	int vals[784];

	pch = strtok(line,",");
	int i = 0;
	while(pch != NULL){
		vals[i++] = stringToInt(pch);
		pch = strtok(NULL,",");
	}
	return vals;
}

int stringToInt(const char *str) {
    int result = 0;
    int sign = 1; // To handle negative numbers
    int i = 0;

    // Skip leading whitespaces
    while (str[i] == ' ') {
        i++;
    }

    // Check for sign
    if (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-') {
            sign = -1;
        }
        i++;
    }

    // Convert characters to integer
    while (str[i] != '\0') {
        if (!isdigit(str[i])) {
            // If the character is not a digit, stop parsing
            break;
        }

        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}


void main(){
	char *c = "asdasd,123,2,2";
	printf("%d",stringToInt(c));
}