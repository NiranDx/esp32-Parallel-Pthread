//โปรแกรมบอกค่า arr โดยใช้ Pthread
#include<pthread.h>

#define size_arr 112
#define num_thread 4

int arr[] = { 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220,
              1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220,
              1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220,
              1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220,
              1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220,
              1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220,
              1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220,};
int sum[4] = {0};
int part = 0;

unsigned long start_time;
unsigned long end_time;
unsigned long execTime_Parrallel ,execTime_Normal;

void* sum_arr(void* arg){
  
  int thread_part = part++;
  // คำนวนโดยการแบ่งเป็นส่วนๆ 4 ส่วน
  for(int i=thread_part*(size_arr/4) ;i<(thread_part + 1)*(size_arr/4) ;i++){
    sum[thread_part] += arr[i];
  }
 // Serial.print("Pthread: Executing on core ");
  //Serial.println(xPortGetCoreID());
}
void setup() {

  Serial.begin(115200);
  //บวกค่าแบบปกติ
  start_time = micros();
  int sum_normal = 0;
  for(int i = 0; i<size_arr ; i++){
      sum_normal += arr[i];
  }
  Serial.print("Setup: Executing on core ");
  Serial.println(xPortGetCoreID());
  end_time = micros();
  execTime_Normal = end_time - start_time;
  Serial.println("--------Normal---------");
  Serial.print("Exec: ");
  Serial.println(execTime_Normal);
  Serial.printf("Sum array: %d\n",sum_normal);

  
  start_time = micros();
  pthread_t threads[num_thread];
  //สร้าง Pthread
  for (int i=0;i<num_thread;i++){
    pthread_create(&threads[i],  //thread
                   NULL, //attr
                   sum_arr, 
                   (void*)NULL); //argument passed to start.
  }
  //การ join คือรอให้ 4 thread เสร็จสมบูรณ์ก่อน
  for(int i=0;i<num_thread;i++){
    pthread_join(threads[i],NULL); //thread และ สถานะออกของ thread
  }
  //รวมค่าที่แบ่งเป็น 4 ส่วน
  int total_sum = 0;
  for(int i=0; i<num_thread;i++){
    total_sum += sum[i];
  }
  end_time = micros();
  execTime_Parrallel = end_time - start_time;
  Serial.println("-------Parallel--------");
  Serial.print("Exec: ");
  Serial.println(execTime_Parrallel);
  Serial.printf("Sum array: %d\n",total_sum);

  Serial.println("--------Speedup---------");
  Serial.print("Speedup Using Normal: ");
  Serial.println((float) execTime_Normal / execTime_Normal, 4 );
  Serial.print("Speedup Using Parallel: ");
  Serial.println((float) execTime_Normal / execTime_Parrallel, 4 );
}
void loop() {
  

}
