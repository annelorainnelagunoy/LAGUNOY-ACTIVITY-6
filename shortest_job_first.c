// Anne Lorainne C. Lagunoy BSCpE 4B
// Shortest Job First Scheduling

int bt[] = {10, 8, 6, 4, 2, 1}; // Burst time inputs
int p[] = {13, 12, 11, 10, 9, 8}; // Processes pin inputs
int size = 6;
float Averagewaitingtime, wt;

void setup() {
  // LEDs Pin configuration
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  ShortestJobFirst(bt, size);
  Serial.begin(9600);
}

void ShortestJobFirst(int a[], int size) { // sorting the task based on the shortest burst time
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size -1; j++) {
      if(a[j] > a[i]){ 
        int btTemp = a[i]; // swap
        int pTemp = p[i]; // swap
        a[i] = a[j];
        a[j] = btTemp;
        p[i] = p[j];
        p[j] = pTemp;
      }
    }
  }
}
void Arrive(int task, int burstTime) {  // function for arrival of the task
  digitalWrite(task, HIGH);
  delay(burstTime * 1000); // LEDS light up to burst time
  digitalWrite(task, LOW);
}

void Wt(int waitingTime) { // function for getting the average waiting time
  wt = wt + waitingTime; 
  Averagewaitingtime = Averagewaitingtime + wt;
}
void loop() {   // driver function
  for ( int i = 0; i < size; i++) {
    Arrive(p[i], bt[i]); // Arrival of task
  	if (i < size - 1) {
      Wt(bt[i]); // Waiting time
  	}
  }
  
  Serial.println("Average Waiting Time : ");
  Serial.println(Averagewaitingtime/size); // Prints the average waiting time during process
  Serial.println("End of process. ");
  delay(10000);
}
