 //Gera a página HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
           
            client.println("<style>html {font-family: Verdana;text-align: center;background-color: #F4F4F4;}");
            client.println("#logo{ margin-right: 670px; width: 210px; height: 50px;}");
            client.println("h1 { margin-top: 60px; font-size: 36px; font-family: monospace;}");
            client.println("p {	font-size: small; color:black;}");
            client.println("#box{ margin: 80px auto auto auto; width: 600px; height: 340px; border: 2px solid  black; border-radius: 5px;}");
            client.println("#ctd {margin: auto;}");
            client.println("#ctd ul { list-style: none; display: grid; grid-template-columns: 200px 200px; grid-row: auto auto; grid-column-gap: 120px; grid-row-gap: 40px;}");
            client.println("#ctd input { background-color: rgb(249, 249, 252); border: 1px solid #00000044; border-radius: 5px; width: 70px; height: 1.6em; font-size: 12px; appearance: none; outline: 0; white-space: pre;}");
            client.println(".bts { color: blak; width: 160px; height: 50px; font-size: 23px; line-height: 1.5; text-decoration: none; font-family: monospace; cursor: pointer; border: 1px solid; border-radius: 3px;}");
            client.println(".btOn { background-color: #7dd181; border-color: #7DD181;}");
            client.println(".btOn:hover { background-color: #61b964; border-color: #61b964;}");
            client.println(".btOff { background-color: gray; border-color: gray;}");
            client.println(".btOff:hover { background-color: rgb(97, 96, 96); border-color: rgb(97, 96, 96);}");
            client.println(".status{font-size: 11px;}");
            client.println("#stOn{color: #38b000;}");
            client.println("#stOff{color: #FD0000;}");
            client.println("</style>");
            client.println("<title>EletronJun ESP32 Local</title></head>");
            
            client.println("<body><h1>EletronJun ESP32 Web Server</h1>");
            
            //Imprime status atual do Relé 1
            client.println("<p>RELAY 1 Status: " + RL1_status + "</p>");
            //client.read("<input type=\"time\" id=\"hora\"  name= " + ONhoraRL1 + " placeholder=\"Hora\" step =\"1\">");
            //client.read(OFFhoraRL1);

            //Gera o botão conforme o status do Relé 1
            if(RL1_status=="OFF") 
              client.println("<p><a href=\"/rl1/on\"><button class=\"bts btOn\">TURN ON RL1</button></a></p>");
            else 
              client.println("<p><a href=\"/rl1/off\"><button class=\"bts btOff\">TURN OFF RL1</button></a></p>");
         
            //Imprime o status atual do Relé 2
            client.println("<p>RELAY 2 Status: " + RL2_status + "</p>");

            //Gera o botão conforme o status do Relé 2
            if(RL2_status=="OFF")
              client.println("<p><a href=\"/rl2/on\"><button class=\"bts btOn\">TURN ON RL2</button></a></p>");
            else 
              client.println("<p><a href=\"/rl2/off\"><button class=\"bts btOff\">TURN OFF RL2</button></a></p>");
            
            //Imprime o status atual do Relé 3
            client.println("<p>RELAY 3 Status: " + RL3_status + "</p>");

            //Gera o botão conforme o status do Relé 3
            if(RL3_status=="OFF")
              client.println("<p><a href=\"/rl3/on\"><button class=\"bts btOn\">TURN ON RL3</button></a></p>");
            else 
              client.println("<p><a href=\"/rl3/off\"><button class=\"bts btOff\">TURN OFF RL3</button></a></p>");

            //Imprime o status atual do Relé 4
            client.println("<p>RELAY 4 Status: " + RL4_status + "</p>");

            //Gera o botão conforme o status do Relé 4
            if(RL4_status=="OFF")
              client.println("<p><a href=\"/rl4/on\"><button class=\"bts btOn\">TURN ON RL4</button></a></p>");
            else 
              client.println("<p><a href=\"/rl4/off\"><button class=\"bts btOff\">TURN OFF RL4</button></a></p>");
              

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