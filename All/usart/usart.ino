void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  char c = 'A';
  int cnt = 0;
  Serial.print('.');

  if(Serial.available() > 0)
  {
    String data = Serial.readString();
    Serial.print('\n');
    Serial.print(data);
  }

  Serial.write(c);
  delay(500);

}
