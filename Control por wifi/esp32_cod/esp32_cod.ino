#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32_Kenartus";
const char* password = "12345678";

WebServer server(80);

int led = 2;

// Pines UART2 (puedes cambiarlos)
#define RXD2 16
#define TXD2 17


//================ FUNCION PARA ENVIAR AL SERIAL2 ================




//================ SETUP =================

void setup()
{
  Serial.begin(115200);

  // Inicializar UART2
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  pinMode(led, OUTPUT);

  WiFi.softAP(ssid, password);

  Serial.println("Red creada");
  Serial.println(WiFi.softAPIP());

  server.on("/comando", recibirComando);
  server.begin();
}


//================ LOOP =================

void loop()
{
  server.handleClient();
}


//================ FUNCION WEB =================

void recibirComando()
{
  String valor = server.arg("valor");

  Serial.println("Recibido desde WEB: " + valor);

  // reenviar al puerto serial 2
  enviarSerial2(valor);

  // solo para prueba con LED
  if(valor == "b" || valor == "c")
  {
    digitalWrite(led, HIGH);
  }

  if(valor == "a")
  {
    digitalWrite(led, LOW);
  }

  if(valor == "e" || valor == "f")
  {
    digitalWrite(led, HIGH);
  }

  if(valor == "d")
  {
    digitalWrite(led, LOW);
  }

  if(valor == "h" || valor == "i")
  {
    digitalWrite(led, HIGH);
  }

  if(valor == "g")
  {
    digitalWrite(led, LOW);
  }

  server.send(200,"text/plain","OK");
}
void enviarSerial2(String comando)
{
  for (int i = 0; i < comando.length(); i++) {
    Serial2.write(comando[i]);
    delay(10); // Puedes ajustar el tiempo según tu necesidad
  }
}
