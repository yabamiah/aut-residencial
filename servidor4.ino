// =======================================================================
// --- Bibliotecas Auxiliares ---
#include <WiFi.h>                         //inclui biblioteca WiFi
#include <NTPClient.h> //https://github.com/taranais/NTPClient
//#include <AsyncTCP.h> // https://github.com/me-no-dev/AsyncTCP
//#include <ESPAsyncWebServer.h> //https://github.com/me-no-dev/ESPAsyncTCP

//33 32 27 13

// =======================================================================
// --- Mapeamento de Hardware ---
#define   relay1   14                    //pino para controle do relé 1
#define   relay2   25                    //pino para controle do relé 2
#define   relay3   26                    //pino para controle do relé 3
#define   relay4   27                    //pino para controle do relé 4

// =======================================================================
// --- Constantes Auxialires ---
//const char *ssid     = "GAMEJ_2.4GHz";  //atribuir nome da rede WiFi
//const char *password = "20092018"; //atribuir senha da rede

const char *ssid     = "Republica Kalangos 3";  //atribuir nome da rede WiFi
const char *password = "unb@fga1"; //atribuir senha da rede

WiFiUDP ntpUDP;
NTPClient ntp(ntpUDP);

// =======================================================================
// --- Objetos ---
WiFiServer server(80);                    //define a porta que o servidor irá utilizar
//AsyncWebServer server(80);                                          //(normalmente utiliza-se a porta padrão 80)

// =======================================================================
// --- Protótipo das Funções ---
void relay_wifi();                       //função para gerar web server e controlar os relés
                              


// =======================================================================
// --- Variáveis Globais ---
String header;


// Variáveis auxiliares para a saída
String RL1_status = "OFF";
String RL2_status = "OFF";
String RL3_status = "OFF";
String RL4_status = "OFF";

// Variáveis auxiliares para os horários (liga/desliga)
String ONhoraRL1 = "15:00:06";
String OFFhoraRL1 = "15:05:00";
String ONhoraRL2 = "15:01:00";
String OFFhoraRL2 = "15:03:00";
String ONhoraRL3 = "16:54:00";
String OFFhoraRL3 = "16:58:00";
String ONhoraRL4 = "16:57:00";
String OFFhoraRL4 = "17:02:00";

String hora_atual = "00:00:00";

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;


// =======================================================================
// --- Configurações Iniciais ---
void setup() 
{
  Serial.begin(9600);                  //inicializa Serial em 9600 baud rate
  pinMode(relay1, OUTPUT);               //configura saída para o relé 1
  pinMode(relay2, OUTPUT);               //configura saída para o relé 2
  pinMode(relay3, OUTPUT);               //configura saída para o relé 3
  pinMode(relay4, OUTPUT);               //configura saída para o relé 4

  digitalWrite(relay1, LOW);             //relé 1 desligado
  digitalWrite(relay2, LOW);             //relé 2 desligado
  digitalWrite(relay3, LOW);             //relé 3 desligado
  digitalWrite(relay4, LOW);             //relé 4 desligado

  Serial.println();                      //
  Serial.print("Conectando-se a ");      //
  Serial.println(ssid);                  //
  WiFi.begin(ssid, password);            //inicializa WiFi, passando o nome da rede e a senha

  while(WiFi.status() != WL_CONNECTED)   //aguarda conexão (WL_CONNECTED é uma constante que indica sucesso na conexão)
  {
    delay(741);                          //
    Serial.print(".");                   //vai imprimindo pontos até realizar a conexão...
  }

  Serial.println("");                    //mostra WiFi conectada
  Serial.println("WiFi conectada");      //
  Serial.println("Endereço de IP: ");    //
  Serial.println(WiFi.localIP());        //mostra o endereço IP

  server.begin();                        //inicializa o servidor web

  //NTP
  ntp.begin();

  //GMT em segundos
  // +1 = 3600
  // +8 = 28800
  // -1 = -3600
  // -3 = -10800 (BRASIL)
  ntp.setTimeOffset(-10800);
  //ntp.forceUpdate();    /* Atualização */

}


// =======================================================================
// --- Loop Infinito ---
void loop() 
{


  while(WiFi.status() != WL_CONNECTED)   //aguarda conexão (WL_CONNECTED é uma constante que indica sucesso na conexão)
  {
    WiFi.begin(ssid, password);          //inicializa WiFi, passando o nome da rede e a senha
    Serial.print(".");                   //vai imprimindo pontos até realizar a conexão...

    delay(741);                          //741ms
  }
  ntp.forceUpdate();
  hora_atual = ntp.getFormattedTime(); // NTP 
  
  if(ONhoraRL1 == hora_atual)         //liga Relé 1
            {
              RL1_status = "ON";                           //atualiza status
              digitalWrite(relay1, HIGH);                  //ativa saída
              Serial.println(hora_atual);
             
            } //RL1 ON
  else if(OFFhoraRL1 == hora_atual)   //desliga Relé 1 
            {          
              RL1_status = "OFF";                          //atualiza status
              digitalWrite(relay1, LOW);                   //desativa saída
              Serial.println(hora_atual);
              
            } //end else if RL1 OFF

  if(ONhoraRL2 == hora_atual)         //liga Relé 2
            {
              RL2_status = "ON";                           //atualiza status
              digitalWrite(relay2, HIGH);                  //ativa saída
              Serial.println(hora_atual);
              
            } //RL2 ON
  else if(OFFhoraRL2 == hora_atual)   //desliga Relé 2 
            {          
              RL2_status = "OFF";                          //atualiza status
              digitalWrite(relay2, LOW);                   //desativa saída
              Serial.println(hora_atual);
              
            } //end else if RL2 OFF 

  if(ONhoraRL3 == hora_atual)         //liga Relé 3
            {
              RL3_status = "ON";                           //atualiza status
              digitalWrite(relay3, HIGH);                  //ativa saída
              Serial.println(hora_atual);
              
            } //RL3 ON
  else if(OFFhoraRL3 == hora_atual)   //desliga Relé 3 
            {          
              RL3_status = "OFF";                          //atualiza status
              digitalWrite(relay3, LOW);                   //desativa saída
              Serial.println(hora_atual);
              
            } //end else if RL3 OFF

  if(ONhoraRL4 == hora_atual)         //liga Relé 4
            {
              RL4_status = "ON";                           //atualiza status
              digitalWrite(relay4, HIGH);                  //ativa saída
              Serial.println(hora_atual);
              
            } //RL4 ON
  else if(OFFhoraRL4 == hora_atual)   //desliga Relé 4 
            {          
              RL4_status = "OFF";                          //atualiza status
              digitalWrite(relay4, LOW);                   //desativa saída
              Serial.println(hora_atual);
              
            } //end else if RL4 OFF
  //delay(10000);
  //Serial.println(ntp.getFormattedTime());
  relay_wifi();                                //chama função para controle dos relés por wifi


  
} //end loop

// =======================================================================
// --- relay_wifi ---
void relay_wifi()
{

  WiFiClient client = server.available();      //verifica se existe um cliente conectado com dados a serem transmitidos
 
  if(client)                                   //existe um cliente?
  {                                            //sim                           
    currentTime = millis();                    //atualiza o tempo atual
    previousTime = currentTime;                //armazena tempo atual
    Serial.println("Novo cliente definido");   //informa por serial
    String currentLine = "";                   //string para aguardar entrada de dados do cliente
    
    while(client.connected() && currentTime - previousTime <= timeoutTime)  //executa enquanto cliente conectado
    {   
      currentTime = millis();                  //atualiza tempo atual
      
      if(client.available())                   //existem dados do cliente a serem lidos?
      {                                        //sim
        char c = client.read();                //salva em c
        Serial.write(c);                       //imprime via serial
        header += c;                           //acumula dados do cliente em header
        
        if (c == '\n')                         //é um caractere de nova linha?
        {                                      //sim           
         
          if (currentLine.length() == 0)       //se final da mensagem...
          {
           
            client.println("HTTP/1.1 200 OK");        //HTTP sempre inicia com este código de resposta
            client.println("Content-type:text/html"); //e com este conteúdo sabermos o que está por vir
            client.println();                         //imprime nova linha

             ntp.update();
             hora_atual = ntp.getFormattedTime(); // NTP 
             //client.println(hora_atual); 
             
            // Controle das Saídas do ESP32:
            if((header.indexOf("GET /rl1/on") >= 0) || ONhoraRL1 == hora_atual)         //liga Relé 1
            {
              RL1_status = "ON";                           //atualiza status
              digitalWrite(relay1, HIGH);                  //ativa saída
              
            } //end if RL1 ON
            
            else if((header.indexOf("GET /rl1/off") >= 0) || OFFhoraRL1 == hora_atual)   //desliga Relé 1 
            {          
              RL1_status = "OFF";                          //atualiza status
              digitalWrite(relay1, LOW);                   //desativa saída
              
            } //end else if RL1 OFF
             
            else if((header.indexOf("GET /rl2/on") >= 0) || ONhoraRL2 == hora_atual)    //liga Relé 2
            {            
              RL2_status = "ON";                           //atualiza status
              digitalWrite(relay2, HIGH);                  //ativa saída
              
            } //end else if RL2 ON
            
            else if((header.indexOf("GET /rl2/off") >= 0) || OFFhoraRL2 == hora_atual)   //desliga Relé 2
            {
              RL2_status = "OFF";                          //atualiza status
              digitalWrite(relay2, LOW);                   //desativa saída
            
            } //end if RL2 OFF
            
            else if((header.indexOf("GET /rl3/on") >= 0) || ONhoraRL3 == hora_atual)   //liga o relé 3
            { 
              RL3_status = "ON";                          //atualiza status
              digitalWrite(relay3, HIGH);                 //ativa saída
             
            } //end else if RL3 ON
            
            else if((header.indexOf("GET /rl3/off") >= 0) || OFFhoraRL3 == hora_atual)  //desliga o relé 3
            {
              RL3_status = "OFF";                         //atualiza status
              digitalWrite(relay3, LOW);                  //desativa saída
             
            } //end else if RL3 OFF
            
            else if((header.indexOf("GET /rl4/on") >= 0) || ONhoraRL4 == hora_atual)   //liga o relé 4
            { 
              RL4_status = "ON";                          //atualiza status
              digitalWrite(relay4, HIGH);                 //ativa saída
             
            } //end else if RL4 ON
            
            else if((header.indexOf("GET /rl4/off") >= 0) || OFFhoraRL4 == hora_atual)  //desliga o relé 4
            {
              RL4_status = "OFF";                         //atualiza status
              digitalWrite(relay4, LOW);                  //desativa saída
             
            } //end else if RL4 OFF

            //Salvar a entrada do usuário
            else if (header.indexOf("GET /ONhoraRL1/datetime") >= 0)
            {
              ONhoraRL1 = ONhoraRL1;
              Serial.println(ONhoraRL1);
              }
            
            // Parei aqui
            
            //Gera a página HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
           
            client.println("<style>html { font-family: Verdana; margin: 0px auto; text-align: center; background-color: #F4F4F4;}");
            client.println("#logo {margin-right: 670px; width: 210px; height: 50px;}");
            client.println("h1 {margin-top: 60px; font-size: 36px; font-family: monospace;}");
            client.println("p {font-size: small; color:black;}");
            client.println("#box {margin: 80px auto auto auto; width: 600px; height: 340px; border: 2px solid  black; border-radius: 5px;}");
            client.println("#ctd {margin: auto;}");
            client.println("#ctd ul { list-style: none; display: grid; grid-template-columns: 200px 200px; grid-row: auto auto; grid-column-gap: 120px; grid-row-gap: 40px;}");
            client.println("#ctd input { background-color: rgb(249, 249, 252); border: 1px solid #00000044; border-radius: 5px; width: 70px; height: 1.6em; font-size: 12px; appearance: none; outline: 0; white-space: pre;}");
            client.println(".bts { color: blak; width: 160px; height: 50px; font-size: 17px; line-height: 1.5; text-decoration: none; font-family: monospace; cursor: pointer; border: 1px solid; border-radius: 3px;}");
            client.println(".btOn { background-color: #7dd181; border-color: #7DD181;}");
            client.println(".btOn:hover { background-color: #61b964; border-color: #61b964;}");
            client.println(".btOff { background-color: gray; border-color: gray;}");
            client.println(".btOff:hover { background-color: rgb(97, 96, 96); border-color: rgb(97, 96, 96);}");
            client.println(".status{font-size: 11px;}");
            client.println("#stOn{color: #38b000;}");
            client.println("#stOff{color: #FD0000;}");
            client.println("</style>");
            client.println("<title>EletronJun ESP32 Local</title></head>");
            //client.println("link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\"/");

            client.println("<body>");
            client.println("<img id=\"logo\" src=\"https://i.imgur.com/kvB8XQq.png\">");
            client.println("<h1>EletronJun ESP32 Web Server</h1>");
            
            client.println( "<div id=\"box\">");
            client.println( "<div id=\"ctd\">");
            client.println("<ul>");
            client.println("<li>");
            
            //Imprime status atual do Relé 1
            //client.println("<p>RELAY 1 Status: " + RL1_status + "</p>");
            //client.println("<p class=\"status\"> RELAY 1 Status: <spam id=\"stOn\">"  + RL1_status + "</spam></p>");
            //client.read("<input type=\"time\" id=\"hora\"  name= " + ONhoraRL1 + " placeholder=\"Hora\" step =\"1\">");
            //client.read(OFFhoraRL1);

            //Gera o botão conforme o status do Relé 1
            if(RL1_status=="OFF") {
              client.println("<p class=\"status\"> Relay 1 Status: <spam id=\"stOff\">OFF</spam></p>");
              client.println("<p><a href=\"/rl1/on\"><button class=\"bts btOff\">TURN ON RL1</button></a></p>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"ONhoraRL1\"  placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>"); // liga
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"OFFhoraRL1\" placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>"); // desliga
            }
            else {
              client.println("<p class=\"status\"> Relay 1 Status: <spam id=\"stOn\">ON</spam></p>");
              client.println("<p><a href=\"/rl1/off\"><button class=\"bts btOn\">TURN OFF RL1</button></a></p>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"ONhoraRL1\"  placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"OFFhoraRL1\" placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>");
            }
         
          client.println("</li>");
          
          client.println("<li>");
            //Imprime o status atual do Relé 2
            //client.println("<p>RELAY 2 Status: " + RL2_status + "</p>");
            //client.println("<p class=\"status\"> RELAY 2 Status: <spam id=\"stOn\">"  + RL2_status + "</spam></p>");

            //Gera o botão conforme o status do Relé 2
            if(RL2_status=="OFF"){
              client.println("<p class=\"status\"> Relay 2 Status: <spam id=\"stOff\">OFF</spam></p>");
              client.println("<p><a href=\"/rl2/on\"><button class=\"bts btOff\">TURN ON RL2</button></a></p>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"ONhoraRL2\"  placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"OFFhoraRL2\" placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>");
            }
            else {
              client.println("<p class=\"status\"> Relay 2 Status: <spam id=\"stOn\">ON</spam></p>");
              client.println("<p><a href=\"/rl2/off\"><button class=\"bts btOn\">TURN OFF RL2</button></a></p>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"ONhoraRL2\"  placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"OFFhoraRL2\" placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>");
            }

            client.println("</li>");

            client.println("<li>");
            //Imprime o status atual do Relé 3
            //client.println("<p>RELAY 3 Status: " + RL3_status + "</p>");
            //client.println("<p class=\"status\"> RELAY 3 Status: <spam id=\"stOn\">"  + RL3_status + "</spam></p>");

            //Gera o botão conforme o status do Relé 3
            if(RL3_status=="OFF"){
              client.println("<p class=\"status\"> Relay 3 Status: <spam id=\"stOff\">OFF</spam></p>");
              client.println("<p><a href=\"/rl3/on\"><button class=\"bts btOff\">TURN ON RL3</button></a></p>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"ONhoraRL3\"   placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"OFFhoraRL3\"  placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>");
            }
            else {
              client.println("<p class=\"status\"> Relay 3 Status: <spam id=\"stOn\">ON</spam></p>");
              client.println("<p><a href=\"/rl3/off\"><button class=\"bts btOn\">TURN OFF RL3</button></a></p>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"ONhoraRL3\"  placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"OFFhoraRL3\" placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>");
            }
            client.println("</li>");

            client.println("<li>");
            //Imprime o status atual do Relé 4
            //client.println("<p class=\"status\"> RELAY 4 Status: <spam id=\" + cor +">"  + RL4_status + "</spam></p>");

            //Gera o botão conforme o status do Relé 4
            if(RL4_status=="OFF"){
              client.println("<p class=\"status\"> Relay 4 Status: <spam id=\"stOff\">OFF</spam></p>");
              client.println("<p><a href=\"/rl4/on\"><button class=\"bts btOff\">TURN ON RL4</button></a></p>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"ONhoraRL4\"  placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"OFFhoraRL4\" placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>");
            }
            else {
              client.println("<p class=\"status\"> Relay 4 Status: <spam id=\"stOn\">ON</spam></p>");
              client.println("<p><a href=\"/rl4/off\"><button class=\"bts btOn\">TURN OFF RL4</button></a></p>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"ONhoraRL4\"  placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>");
              client.println("<form action=\"/get\"><input type=\"datetime\" id=\"hora\" name=\"OFFhoraRL4\" placeholder=\"hh:mm:ss\"><input type=\"submit\" value=\"Enviar\"></form>");
              //client.println("<input type=\"datetime\" id=\"hora\" name=\"hora\" placeholder=\"hh:mm:ss\">");
            }
            client.println("</li>");

            client.println("</ul>");
            
            client.println("</div>");
            client.println("</div>");
            
            //Definir horario para ligar
            //Relé 1
            //Relé 2

            client.println("</body></html>");
            client.println();
            break;
          } 
          
          else currentLine = ""; //senão, impede string de fizer com espaços em branco
            
        } //end if c
        
        else if (c != '\r')  
          currentLine += c;      //adiciona caractere como parte da mensage
 

      } //end if client.available
      
    } //end while client.connected
    
    header = "";                              //limpa header
   
    client.stop();                            //finaliza conexão
    Serial.println("Cliente desconectado");   //
    Serial.println("");                       //
    
  } //end if client
  
  
} //end relay_wifi
