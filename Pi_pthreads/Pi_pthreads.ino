#include <pthread.h>
#include <stdio.h>
#include <math.h>

#define NUM_RECT 100000
#define NUMTHREADS 6

double gPi = 0.0;
unsigned long start_time;
unsigned long end_time;
unsigned long execTime_Parrallel ,execTime_Normal;

pthread_mutex_t gLock;

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

   pthread_t threads[NUMTHREADS];
   int tNum[NUMTHREADS],i;

   pthread_mutex_init(&gLock,NULL);
   start_time = micros();
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

}
 
void loop() {
  delay(100);
  
}
