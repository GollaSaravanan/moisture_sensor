#define MoisturePin 34 // Use any ADC-capable pin like 34, 35, 32, etc.

void setup()
{
  Serial.begin(115200); // ESP32 commonly uses 115200 baud
}

void loop() 
{
  int soilMoistureValue = analogRead(MoisturePin); // Read raw analog value (0-4095 on ESP32)
 Serial.print(soilMoistureValue);
  float p=((soilMoistureValue/4095.0)*100);
  Serial.print("\nPercentage value-->");
  Serial.println(p);
  Serial.println("%\n");
  delay(1000);
}
