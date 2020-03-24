#include <pthread.h>
#include <stdio.h>
#include <math.h>

#define NUM_RECT 100000
#define NUMTHREADS 4

double gPi = 0.0;
double step;
unsigned long start_time;
unsigned long end_time;
unsigned long execTime_Parrallel ,execTime_Normal;

pthread_mutex_t gLock;

void Cal_Pi_normal();
void *Area(void *pArg) {
   int myNum = *((int *)pArg);
   double h = 2.0 / NUM_RECT;
   double partialSum = 0.0, x;

   for (int i = myNum; i < NUM_RECT; i += NUMTHREADS){
      x = -1 + (i + 0.5f) * h;
      partialSum += sqrt(1.0 - x*x) * h;
    }
    pthread_mutex_lock(&gLock);
    gPi += partialSum;  
    pthread_mutex_unlock(&gLock);
   
}
 
void setup() {
 
   Serial.begin(115200);

   Cal_Pi_normal();
 
   pthread_t threads[NUMTHREADS];
   int tNum[NUMTHREADS],i;

   start_time = micros();
   pthread_mutex_init(&gLock,NULL);
   for(i=0;i<NUMTHREADS;i++){
    tNum[i] = i;
    pthread_create(&threads[i],
                          NULL,
                          Area,
                          (void*)&tNum[i]);
   }
   for(i=0;i<NUMTHREADS;i++){
    pthread_join(threads[i],NULL);
   }
   gPi *= 2.0;
   end_time = micros();
   execTime_Parrallel = end_time - start_time;
   Serial.println("-------Parallel--------");
   Serial.print("Exec: ");
   Serial.println(execTime_Parrallel);
   Serial.printf("Value of Pi: %0.10f\n",gPi);
   pthread_mutex_destroy(&gLock);

  Serial.println("--------Speedup---------");
  Serial.print("Speedup Using Normal: ");
  Serial.println((float) execTime_Normal / execTime_Normal, 4 );
  Serial.print("Speedup Using Parallel: ");
  Serial.println((float) execTime_Normal / execTime_Parrallel, 4 );
}
 
void loop() {
  delay(100);
  
}
void Cal_Pi_normal(){
  
    int i;
    double x, pi, sum = 0.0;
    
    start_time = micros();
    step = 1.0/(double) NUM_RECT;
    for (i=0;i< NUM_RECT; i++){
            x = (i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
    }
    pi = step * sum;

    end_time = micros();
    execTime_Normal = end_time - start_time;
    Serial.println("--------Normal---------");
    Serial.print("Exec: ");
    Serial.println(execTime_Normal);
    Serial.printf("Value of Pi: %0.10f\n",pi);
}
