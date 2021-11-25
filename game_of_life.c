#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

int num_rows;
int num_cols;
int iteration;
int death,born;


// read the input from given filename and return a 2D dynamically allocated and populated array
// you can use char type for each cell value or bool from <stdbool.h>
int checkDeadOrAlive(char **state, int currentRow, int currentCol,int totalRows,int totalCols);

char **read_from_file(const char *filename)
{
	
  printf("\nfilename: %s \n",filename);
	FILE* f = fopen(filename,"r");
    	if(f == NULL){
		printf("error!, file cannot be opened");
		exit(1);	
	}
  char line[256],line2[256],line3[256];

  fgets(line, sizeof(line), f);
  iteration = atoi(line);

  fgets(line2, sizeof(line), f);
  num_rows = atoi(line2);

  fgets(line3, sizeof(line), f);
  num_cols = atoi(line3);

	int i,j;
	char** arr = (char**)malloc(num_rows*sizeof(char*));
	for( i = 0; i < num_rows; i++){
		arr[i] = (char*)malloc(num_cols*sizeof(char));
	}

  char dummy;

    for( i = 0; i < num_rows; i++){
      for( j = 0; j < num_cols; j++){
        arr[i][j] = fgetc(f);
      }
      dummy = fgetc(f); //to avoid reading end of line character
    }
	return arr;
}

// given a game step return the next step applying game rules
char **next_state(char **state, int rows, int cols)
{
  death = 0;
  born = 0;
  int i,j;

	int** arr = (int**)malloc(rows*sizeof(int*));
	for( i = 0; i < rows; i++){
		arr[i] = (int*)malloc(cols*sizeof(int));
	}

  for( i = 0; i < rows; i++){
    for( j = 0; j < cols; j++){
      arr[i][j] = checkDeadOrAlive(state,i,j,rows,cols);
    }
  }
   
  // for( i = 0; i < rows; i++){
  //   for( j = 0; j < cols; j++){
  //     printf("%d",arr[i][j]);
  //   }
  //   printf("\n");
  // }
  

  for( i = 0; i < rows; i++){
    for( j = 0; j < cols; j++){
      if(arr[i][j] == 1){
        state[i][j] = 'X';
      }else{
        state[i][j] = '-';
      }
    }
  }
  printf("death: %d\n",death);
  printf("born: %d\n",born);
  return state;
}

int checkDeadOrAlive(char **state, int currentRow, int currentCol,int totalRows,int totalCols){

  int neighborCounter = 0;
  int i,j;
  
  
  for(i= currentRow - 1; i <= currentRow + 1; i++){
    for(j=currentCol - 1 ; j <= currentCol + 1; j++){
      if((i < totalRows && i >= 0) && (j < totalCols && j >= 0)){
        if(state[i][j] == 'X') {
          neighborCounter++;
        }
      }
    }
  }

  if(state[currentRow][currentCol] == 'X'){
    neighborCounter--; //for inclusion of cell itself
    if(neighborCounter < 2 || neighborCounter > 3) {
      death++;
      return 0;
    }else{
      return 1;
    }
  }else {
    if(neighborCounter == 3){
      born++;
      return 1;
    }else {
      return 0;
    }
  }  
}
// bonus task
// return true if the given pattern is an oscillator
bool is_oscillator(char **pattern, int max_steps)
{

}

// print the game state
// after each step you can call this function, add some delay and then clear screen to create a simple game simulation in terminal
void print_state(char **state, int rows, int cols)
{

    int i, j;

    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            printf("%c", state[i][j]);
        }
        printf("\n");
    }
}
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

void write_a_file(char *filename,char** state,int counter){
  char str[10] = "";
  sprintf(str, "%d", counter);
  int len = strlen(filename);
  char str2[len+1];
  int k;
  for(k = 0; k <= len; k++){
    str2[k] = filename[k];
  }
  
  printf("%s\n",str2);
  strcat(str2,str);
  printf("%s\n",str2);

	FILE* f = fopen(str2,"w");
    if(f == NULL){
		  printf("error!, file cannot be opened");
		  exit(1);	
	  }
    fprintf(f,"%d\n",death);
    fprintf(f,"%d\n",born);
    int i,j;
    for(i=0; i<num_rows; i++){
      for(j=0; j<num_cols; j++){
        fprintf(f,"%c",state[i][j]);
      }
        fprintf(f,"\n");
    }
}


int main(int argc, char **argv) 
{

  char const* filename = argv[1];
  char* outputFilename = argv[2];
  
  char** arr = read_from_file(filename);
  print_state(arr,num_rows,num_cols);
  write_a_file(outputFilename,arr,0);
  int i;
  for(i = 0; i < iteration; i++){
    delay(5);
    system("clear");
    arr = next_state(arr, num_rows, num_cols);
    write_a_file(outputFilename,arr,i+1);
    print_state(arr,num_rows,num_cols);
  }

  return 0;
}               
             
