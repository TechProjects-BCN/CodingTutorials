// how long our message will be (how many numbers)
const int msg_len = 4;
int x[msg_len] = {1,2,3,4};

void setup()
{
  Serial.begin(115200); // Serial Communication is starting with 115200 of baudrate speed
}

void loop()
{
  // x is our data. could be string, int, float, ...
  String data = "";
  for (int i = 0; i < msg_len; i++)
  {
    // We convert all the data into a string where each value is separated by commas.
    data = data + String(x[i]) + ",";
  }
  // We send the string to the serial port
  Serial.println(data);
  if (Serial.available())
  {
  String new_x = Serial.readStringUntil('\n'); //Reading a hole string of data
  int xi = 0;
  for (int i = 0; i < (msg_len*2); i = i + 2)
  {
    x[xi] = new_x.substring(i, i + 1).toInt();
    Serial.println(x[xi]);
    xi++;
  }
  }
  delay(1000); // 1s delay
}