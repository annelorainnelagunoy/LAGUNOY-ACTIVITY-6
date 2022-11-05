// Anne Lorainne C. Lagunoy BSCpE 4B
// Round Robin Scheduling


int bt[] = {10, 8, 6, 4, 2, 1}; // Burst time inputs
int p[] = {11, 10, 12, 9, 13, 8}; // Processes pin inputs
int temp[6] = {0, 0, 0, 0, 0, 0};
int size = 6, time_quantum = 2, count = 20, t = 0;
float AWT, ft = 0;
// Arrives at time 0

void setup() {
  // LEDs Pin configuration
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}
 

void Arrive(int task, int timeQuantum) {  // function for arrival of the task
  digitalWrite(task, HIGH);
  delay(timeQuantum * 1000); // Lights up to time quantum
  digitalWrite(task, LOW);
}

void Wt(int waitingTime) { // function for getting the average waiting time 
  AWT = AWT + waitingTime;
}
 
void loop() {   // driver function
  while (count != 0) {
    for (int i = 0; i < size; i++) {
      if (bt[i] != 0) {
        if (t < size) {
          temp[t] = bt[i]; // a copy of burst time
          t++;
        }
        if (bt[i] < time_quantum){ // if remaining burst time is less than time quantum
          Arrive(p[i], time_quantum - 1);
          ft = ft + 1;
          Wt(ft - temp[i]); // Finish time - burst time
          bt[i] = 0;
        } else if (bt[i] == time_quantum) { // if remaining burst time is equal to time quantum
          Arrive(p[i], time_quantum);
          ft = ft + 2;
          Wt(ft - temp[i]); // Finish time - burst time
          bt[i] = 0;
        } else if (bt[i] > time_quantum) { // if remaining burst time is greater than time quantum
          bt[i] = bt[i] - time_quantum;
          Arrive(p[i], time_quantum);
          ft = ft + 2; 
        }
      } else {
        count--; // terminator
      }
    }
  }
  
  Serial.println("Average Waiting Time : ");
  Serial.println(AWT/size); // Prints Average Waiting Time
  Serial.println("End of process.");
  delay(10000);
  
}
