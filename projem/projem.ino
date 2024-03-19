
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int hareket;
int hareketbildirim;
char auth[] = "a7dYKo1zquZH-qmQWLqtOz29felF5jpg";
char ssid[] = "TurkTelekom_TP35AC_2.4GHz";
char pass[] = "XzNYwJAwDFu9";
const char* host="maker.ifttt.com";

int sicaklikSensor= A0;
float sicaklikdegeri;   //Analog değeri dönüştüreceğimiz sıcaklık değeri 
float olculendeger;   //Ölçeceğimiz analog değer
BlynkTimer timer;
void myTimerEvent()
{
 
  if (hareketbildirim == 1) {
  Blynk.notify("Hareket algilandi!");
  hareketbildirim = 0;
  }
}
void setup() {
  pinMode(A0,INPUT);//sıcaklık sensörü
pinMode(D4,OUTPUT);//ışık
pinMode(D2,INPUT); // hareket sensörü
  digitalWrite(D4,LOW);

 Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  
}
void loop() {
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  // LM35 sıcaklık değeri okuma
olculendeger = analogRead(sicaklikSensor); //A0'den değeri alacak
olculendeger = (olculendeger/1024)*5000;//değeri mV'a dönüştürecek 
sicaklikdegeri = olculendeger /12,0; // mV'u sicakliğa dönüştürecek
sicaklikdegeri=sicaklikdegeri-10;
Serial.print("Sicaklik: "); 
Serial.println(sicaklikdegeri); 
hareket = digitalRead(D2);
int a =digitalRead(D4);
Serial.println(a);

if(sicaklikdegeri<20){

      String url = "/trigger/Mail_transfer/with/key/j_DMbKpnkX_1oqLbQy6AIV3-pO0Ewt1D5IihfFlcIvp";


      Serial.print("Requesting URL: ");
      Serial.println(url);

      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: close\r\n\r\n");
                  
}      

 if(a==1){
  Blynk.notify("ışık açıldı!");a==0;
  }
  delay(1000);
    if (hareket == 1) {
      
      delay(500);
      hareketbildirim = 1;
 timer.setInterval(5000L, myTimerEvent);
      
    }
    else{
    hareketbildirim=0;
      }
    
     Blynk.run();
  timer.run();
}
