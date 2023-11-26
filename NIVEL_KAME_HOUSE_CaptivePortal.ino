#include <WiFi.h>
#include <DNSServer.h>
#include "data.h"
#define MAXSIZE 6 
//#include "data1.h"
const byte DNS_PORT = 53;
IPAddress apIP(8, 8, 4, 4); // The default Android DNS
DNSServer dnsServer;
WiFiServer server(80);

// Pines de los LEDs
//const int numLEDs = MAXSIZE;
int Nivel[MAXSIZE - 1];
static unsigned short int inputs[MAXSIZE] = {26, 33, 27, 14, 12, 13};  // Actualiza los pines de acuerdo a tu configuración

// Variables Cliente
char linebuf[80];
int charcount = 0;
float nivel;
void setup() {
  Serial.begin(115200);
  
  for (int i = 0; i < MAXSIZE - 2; i++) {
    pinMode(inputs[i], INPUT);
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAP("KAME_HOUSE");
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

  dnsServer.start(DNS_PORT, "*", apIP);
  server.begin();
}


void loop() {
   for (int i = 0; i < MAXSIZE - 1; i++) {
    Nivel[i] = digitalRead(inputs[i]);
  }
  if (!Nivel[0] and !Nivel[1] and !Nivel[2] and !Nivel[3] and !Nivel[4]) //inicia el algebra boleana
  {
    nivel = 0;
    //Nivel[2] = 'A';
  }

  if (Nivel[0] == 1)
  {
    nivel = 0.2;
    //Nivel[2] = 'B';
  }
  if (Nivel[1] == 1)
  {
    nivel = 0.4;
    //Nivel[2] = 'C';
  }
  if (Nivel[2] == 1)
  { nivel = 0.6;
    //Nivel[2] = 'D';
  }

  if (Nivel[3] == 1)
  { nivel = 0.8;
    //Nivel[2] = 'E';
  }
  if (Nivel[4] == 1)
  { nivel = 1;
    //Nivel[2] = 'F';
  }
  if (!((Nivel[0] and Nivel[1] and Nivel[2] and Nivel[3] and Nivel[4]) or
        (Nivel[0] and Nivel[1] and Nivel[2] and Nivel[3] and !Nivel[4]) or
        (Nivel[0] and Nivel[1] and Nivel[2] and !Nivel[3] and !Nivel[4]) or
        (Nivel[0] and Nivel[1] and !Nivel[2] and !Nivel[3] and !Nivel[4]) or
        (Nivel[0] and !Nivel[1] and !Nivel[2] and !Nivel[3] and !Nivel[4]) or
        (!Nivel[0] and !Nivel[1] and !Nivel[2] and !Nivel[3] and !Nivel[4])  ) )
  {
    nivel = 2; // USAR LOGICA DE JAVA SRIP PARA EL CODIGO ERROR
    
  }
   
    // Esperamos a que se conecte un cliente
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Nuevo Cliente");
    memset(linebuf, 0, sizeof(linebuf));
    charcount = 0;
    // Una petición http termina con línea en blanco.
    boolean currentLineIsBlank = true;

      while (client.connected()) {  //Mientras que el cliente está conectado
      if (client.available()) {   //Si se recibe algun dato del cliente.
        char c = client.read();
        Serial.write(c);
        //Lee caracter por caracter la petición http
        linebuf[charcount] = c;
        if (charcount < sizeof(linebuf) - 1) charcount++;
        // si se recibe un caracter de nueva línea (/n) y la siguiente línea
        // es una líne en blanco entonces la petición http ha terminado y podemos
        // responder al cliente

        if (c == '\n' && currentLineIsBlank) {
          // enviar un encabezado de respuesta http estándar
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html"); // usar dos variables con for para imprimir html y href botones
          client.println("Connection: close");  // la conexión se cerrará después de completar la respuesta
          client.println();
client.print(responseHTML);//jalo la pagina html por medio de: const char *html = R"====( 
client.print(nivel);
client.print(responseHTML1);          
          break;
        }
        //Para monitorear salida
        //delay(500);
        //Serial.println(" ");
        //Serial.println(nivel);
          // Empieza una nueva línea
         
      }
    }
    delay(1);  // Esperamos un poco para que el navegador reciba los datos.
    // Cerramos la conexión con el cliente
    client.stop();
    Serial.println("Cliente desconectado");
    
  }

 
}
