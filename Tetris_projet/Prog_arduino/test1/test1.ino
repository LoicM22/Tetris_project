int data;

void setup() {
  Serial.begin(9600);
}

void loop() {
  data =3;
  Serial.println(data); // données a envoyer
  delay(1000);
}
