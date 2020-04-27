#include<pthread.h>

#define _size 4
#define num_thread 4 

int matA[_size][_size]; 
int matB[_size][_size]; 
int matC[_size][_size]; 

int part = 0;

void randomValues();
void showValuesofMatrix();

void* calMatrix(void* arg) 
{ 
    int thread_part = part++; 
    
    // Each thread computes 1/4th of matrix multiplication 
    for (int i = thread_part * _size / 4; i < (thread_part + 1) * _size / 4; i++){  
        for (int j = 0; j < _size; j++){  
            for (int k = 0; k < _size; k++){  
                matC[i][j] += matA[i][k] * matB[k][j]; 
            }
        }
    }
}
void setup() {
  // put your setup code here, to run once:
  
    Serial.begin(115200);
    
    randomValues();
    showValuesofMatrix();
    
    // declaring four threads 
    pthread_t threads[num_thread]; 
    // Creating four threads
    for (int i = 0; i < num_thread; i++) { 
        int* p; 
        pthread_create(&threads[i], //thread
                        NULL, //attr
                        calMatrix, 
                        (void*)(p)); 
    }
     
    // joining and waiting for all threads to complete 
    for (int i = 0; i < num_thread; i++){  
        pthread_join(threads[i], NULL);  
    }   
  
    // show the result of matrix 
    Serial.println("-----Multiplication of Matrix A and Matrix B-------"); 
    for (int i = 0; i < _size; i++) { 
        for (int j = 0; j < _size; j++){  
            Serial.printf("%d",matC[i][j]);
            Serial.print(" ");
        }         
        Serial.println();
    }

}
void loop() {
  // put your main code here, to run repeatedly:
  //nothing....
}
void randomValues(){
  
  for (int i = 0; i < _size; i++) { 
        for (int j = 0; j < _size; j++) { 
            matA[i][j] = rand() % 10;  //ramdom value no more than 10
            matB[i][j] = rand() % 10;  //ramdom value no more than 10
        } 
    } 
}
void showValuesofMatrix(){
  
  // show matrix a 
    Serial.println("-----------Matrix A-----------");
    for (int i = 0; i < _size; i++) { 
        for (int j = 0; j < _size; j++){  
            Serial.printf("%d",matA[i][j]);
            Serial.print(" "); 
        }
        Serial.println();
    } 
  
    // show matrix b 
    Serial.println("-----------Matrix B------------");
    for (int i = 0; i < _size; i++) { 
        for (int j = 0; j < _size; j++){  
             Serial.printf("%d",matB[i][j]);
             Serial.print(" ");
        }        
        Serial.println();
    } 
}
