
static long num_steps = 100000;
double step;
unsigned long start_time;
unsigned long end_time;
unsigned long execTime_Normal;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    int i;
    double x, pi, sum = 0.0;
    
    start_time = micros();
    step = 1.0/(double) num_steps;
    for (i=0;i< num_steps; i++){
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

void loop() {
  // put your main code here, to run repeatedly:

}
