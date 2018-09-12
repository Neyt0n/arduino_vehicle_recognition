//Variaveis dos botoes
    const int b1A = 2; 
    const int b1B = 4; 
    const int b2A = 5; 
    const int b2B = 6; 
    const int led1 = 7; 
    const int led2 = 8;
    const int led3 = 9;
    const int led4 = 10;
    const int led5 = 11;
    
    //Variavel para ler o status do pushbutton
    int EstadoBotao1A = 0; 
    int EstadoBotao1B = 0; 
    int EstadoBotao2A = 0; 
    int EstadoBotao2B = 0; 
    unsigned long tInicio1;
    unsigned long tFim1;
    unsigned long tempo1 = 0;
    unsigned long tInicio2;
    unsigned long tFim2;
    unsigned long tempo2 = 0;
    boolean motoEnt = false;
    boolean motoEnt2 = false;
    boolean carroEnt = false;
    boolean anterior = false;
    boolean foi = false;
    
void setup() {
      Serial.begin(9600);
  
      pinMode(b1A, INPUT); //Pino com botão será entrada
      pinMode(b1B, INPUT);
      pinMode(b2A, INPUT);
      pinMode(b2B, INPUT);
      pinMode(led1, OUTPUT);
      pinMode(led2, OUTPUT);
      pinMode(led3, OUTPUT);
      pinMode(led4, OUTPUT);
      pinMode(led5, OUTPUT);
  

}

void loop() {
      EstadoBotao1A = digitalRead(b1A); 
      EstadoBotao1B = digitalRead(b1B); 
      EstadoBotao2A = digitalRead(b2A); 
      EstadoBotao2B = digitalRead(b2B);
      //Serial.println(EstadoBotao1B);
      
      //Entrada
      if(EstadoBotao2A == LOW && EstadoBotao2B == LOW){
        if(EstadoBotao1A == HIGH){
          anterior = true;
          //Possivel entrada de carro ou moto abro o timer
          tInicio1 = millis();
          while(tempo1 <= 5000){
            EstadoBotao1B = digitalRead(b1B);
            EstadoBotao2A = digitalRead(b2A);
            EstadoBotao2B = digitalRead(b2B);

            //Testo se é carro
            if(EstadoBotao1B == HIGH){
              //Carro entrou
              carroEntra();   
              foi = true;
              break;       
            }else{
            if(EstadoBotao2A == HIGH){
                 //Entrou moto
                 motoEntra(1);
                 foi = true;
                 break;
              }else{
                //Diagonal
                if(EstadoBotao2B == HIGH){

                  moto_diagonalEnt(1);
                  foi = true;
                  break;
                  }
                }
              }
            
            tFim1 = millis();
            tempo1 = tFim1 - tInicio1;
          }   
                
          }

          if(foi == true){
            foi = false;
            return;
            }
          

          //Agora pra quando aciona o 1B primeiro
          if(EstadoBotao1B == HIGH && anterior == false){
            tInicio1 = millis();

            while(tempo1 <= 5000){
              EstadoBotao1A = digitalRead(b1A);  
              EstadoBotao2B = digitalRead(b2B);
              EstadoBotao2A = digitalRead(b2A);

              if(EstadoBotao1A == HIGH){
                  //Entrada de carro
                  carroEntra();
                  foi = true;
                  break;
                }else{
                    if(EstadoBotao2B == HIGH){
                      //Entrada de moto
                      motoEntra(2);
                      foi = true;
                      break;
                      }else{
                        //Diagonal
                        if(EstadoBotao2A == HIGH){
                          moto_diagonalEnt(2);
                          foi = true;
                          break;
                          }
                        }
                  }
              
              tFim1 = millis();

              tempo1 = tFim1 - tInicio1;
            }
            
            }

            if(foi == true){
              foi = true;
              return;
              }
          
        }

        //para saida dos veiculos
        if(EstadoBotao1A == LOW && EstadoBotao1B == LOW){
          if(EstadoBotao2A == HIGH){
            anterior = true;
            tInicio1 = millis();

            while(tempo1 <= 5000){
            EstadoBotao1A = digitalRead(b1A);
            EstadoBotao1B = digitalRead(b1B);
            EstadoBotao2B = digitalRead(b2B);


              if(EstadoBotao1A == HIGH){
                //motoEnt = true;
                motoSaida(1);
                foi = true;
                break;
                
                }else{
                    if(EstadoBotao2B == HIGH){
                      //carroEnt = true;
                      carroSaida();
                      foi = true;
                      break;
                      }else{
                        if(EstadoBotao1B == HIGH){
                          moto_diagonalSai(1);
                          foi = true;
                          break;
                          }
                        }
                  
                  }
              
              tFim1 = millis();

              tempo1 = tFim1 - tInicio1;
              
              }
              
            }

            if(foi == true){
              foi = false;
              return;
              }

            //Agora pra quando aciona o 2B primeiro
          if(EstadoBotao2B == HIGH && anterior == false){

            tInicio1 = millis();

            while(tempo1 <= 5000){
              EstadoBotao2A = digitalRead(b2A);  
              EstadoBotao1B = digitalRead(b1B);
              EstadoBotao1A = digitalRead(b1A);

              if(EstadoBotao2A == HIGH){
                  //Entrada de carro
                  carroSaida();
                  foi = true;
                  break;
                }else{
                    if(EstadoBotao1B == HIGH){
                      //Entrada de moto
                      motoSaida(2);
                      foi = true;
                      break;
                      }else{
                        if(EstadoBotao1A == HIGH){
                          moto_diagonalSai(2);
                          foi = true;
                          break;
                          }
                        }
                  }
              
              tFim1 = millis();

              tempo1 = tFim1 - tInicio1;
              }
            
            }
          
          }

          if(foi == true){
            foi = false;
            return;
            }

tempo1 = 0;
motoEnt = false;
carroEnt = false;
anterior = false;


}

void carroEntra(){
  //Testa a logica do carro
  carroEnt = false;
  tempo1 = 0;
  tFim1 = 0;
  tInicio1 = 0;
  tInicio1 = millis();

  while(tempo1 <= 5000){
    EstadoBotao1A = digitalRead(b1A);
    EstadoBotao1B = digitalRead(b1B);
    EstadoBotao2A = digitalRead(b2A);
    EstadoBotao2B = digitalRead(b2B);

    if(EstadoBotao2A == HIGH && EstadoBotao2B == HIGH){
      //Entrada de carro
      carroEnt = true;
      break;
      }else{
          if(EstadoBotao1A == LOW && EstadoBotao1B == LOW){
            //Desistiu volta do inicio
            carroEnt = false;
            break;
            }
        }

    tFim1 = millis();

    tempo1 = tFim1 - tInicio1;
    }

    if(carroEnt == true){
      tempo1 = 0;
      tFim1 = 0;
      tInicio1 = 0;
      tInicio1 = millis();

      while(tempo1 <= 5000){
        EstadoBotao1A = digitalRead(b1A);
        EstadoBotao1B = digitalRead(b1B);
        EstadoBotao2A = digitalRead(b2A);
        EstadoBotao2B = digitalRead(b2B);

        if(EstadoBotao2A == LOW && EstadoBotao2B == LOW){
          //Volta pro inicio
            carroEnt = false;
            break;
          }else{
              if(EstadoBotao1A == LOW && EstadoBotao1B == LOW){
                //Entrando
                carroEnt = true;
                break;
                }
            }


        tFim1 = millis();

        tempo1 = tFim1 - tInicio1;
        }

        if(carroEnt == true){
          tempo1 = 0;
          tFim1 = 0;
          tInicio1 = 0;
          tInicio1 = millis();

          while(tempo1 <=  5000){
            EstadoBotao1A = digitalRead(b1A);
            EstadoBotao1B = digitalRead(b1B);
            EstadoBotao2A = digitalRead(b2A);
            EstadoBotao2B = digitalRead(b2B);

            if(EstadoBotao2A == LOW && EstadoBotao2B == LOW){
              //Entrada confirmada
              Serial.print(1);
              digitalWrite(led2,HIGH);
              delay(1000);
              digitalWrite(led2,LOW);
              break;
              }else{
                    if(EstadoBotao1A == HIGH && EstadoBotao1B == HIGH){
                      //Erro
                      Serial.print(3);
                      digitalWrite(led3,HIGH);
                      delay(1000);
                      digitalWrite(led3,LOW);
                      break;
                      }
                }
            
            tFim1 = millis();

            tempo1 = tFim1 - tInicio1;
            }
          }
      }
              
  
  }

void moto_diagonalEnt(int a){
  if(a == 1){
    //Moto entra 1A
    motoEnt = false;
    tempo1 = 0;
    tFim1 = 0;
    tInicio1 = 0;
    tInicio1 = millis();
    EstadoBotao1A = 0;
    EstadoBotao2A = 0;
    while(tempo1 <= 5000){
    EstadoBotao1A = digitalRead(b1A);
    EstadoBotao2B = digitalRead(b2B);
    //Continua a entrada
    if(EstadoBotao1A == LOW && EstadoBotao2B == HIGH){
      motoEnt = true;
      
      break;
      }
      //Desistiu volta pro inicio
      if(EstadoBotao2B == LOW && EstadoBotao1A == HIGH){
          motoEnt = false;
          break;
        }
       

        tFim1 = millis();
        tempo1 = tFim1 - tInicio1;
    }
    //Continuou a entrada
    if(motoEnt == true){

      tempo1 = 0;
      tInicio1 = millis();
      while(tempo1 <= 5000){
        EstadoBotao1A = digitalRead(b1A);
        EstadoBotao2B = digitalRead(b2B);

        if(EstadoBotao2B == LOW && EstadoBotao1A == LOW){
          //Entrou, pode registrar
          Serial.print(5);
         digitalWrite(led5,HIGH);
         delay(1000);
         digitalWrite(led5,LOW);
          return;
          }else{
              if(EstadoBotao1A == HIGH){
                //Erro

                Serial.print(4);
                 digitalWrite(led3,HIGH);
                 delay(1000);
                 digitalWrite(led3,LOW);
                break;
                }
            }

          tFim1 = millis();

          tempo1 = tFim1 - tInicio1;
        }
      
      }

    
  
    
  }else{
      //Moto entra 1B
      //Testo moto agora
          motoEnt = false;
          tempo1 = 0;
          tFim1 = 0;
          tInicio1 = 0;
          tInicio1 = millis();
          while(tempo1 <= 5000){
          EstadoBotao1B = digitalRead(b1B);
          EstadoBotao2A = digitalRead(b2A);
          //Continua a entrada
          if(EstadoBotao1B == LOW && EstadoBotao2A == HIGH){
            motoEnt = true;
            
            break;
            }else{
                //Desistiu volta pro inicio
                if(EstadoBotao2A == LOW && EstadoBotao1B == HIGH){
                    motoEnt = false;
                    break;
                  }
              }

              tFim1 = millis();
              tempo1 = tFim1 - tInicio1;
          }
          //Continuou a entrada
          if(motoEnt == true){

            tempo1 = 0;
            tInicio1 = millis();
            while(tempo1 <= 5000){
              EstadoBotao1B = digitalRead(b1B);
              EstadoBotao2A = digitalRead(b2A);

              if(EstadoBotao2A == LOW && EstadoBotao1B == LOW){
                //Entrou, pode registrar
                Serial.print(5);
               digitalWrite(led5,HIGH);
               delay(1000);
               digitalWrite(led5,LOW);
                break;
                }else{
                    if(EstadoBotao1B == HIGH && EstadoBotao2A == LOW){
                      //Erro
                      Serial.print(4);
                       digitalWrite(led3,HIGH);
                       delay(1000);
                       digitalWrite(led3,LOW);
                      break;
                      }
                  }

                tFim1 = millis();

                tempo1 = tFim1 - tInicio1;
              }
            
            }
              
      }
  
  }

void motoEntra(int a){

  if(a == 1){
    //Moto entra 1A
    motoEnt = false;
    tempo1 = 0;
    tFim1 = 0;
    tInicio1 = 0;
    tInicio1 = millis();
    EstadoBotao1A = 0;
    EstadoBotao2A = 0;
    while(tempo1 <= 3000){
    EstadoBotao1A = digitalRead(b1A);
    EstadoBotao2A = digitalRead(b2A);
    //Continua a entrada
    if(EstadoBotao1A == LOW && EstadoBotao2A == HIGH){
      motoEnt = true;
      
      break;
      }

        tFim1 = millis();
        tempo1 = tFim1 - tInicio1;
    }
    //Continuou a entrada
    if(motoEnt == true){

      tempo1 = 0;
      tInicio1 = millis();
      while(tempo1 <= 5000){
        EstadoBotao1A = digitalRead(b1A);
        EstadoBotao2A = digitalRead(b2A);

        if(EstadoBotao2A == LOW && EstadoBotao1A == LOW){
          //Entrou, pode registrar
          Serial.print(5);
         digitalWrite(led5,HIGH);
         delay(1000);
         digitalWrite(led5,LOW);
          return;
          }else{
              if(EstadoBotao1A == HIGH){
                //Erro

                Serial.print(4);
                 digitalWrite(led3,HIGH);
                 delay(1000);
                 digitalWrite(led3,LOW);
                break;
                }
            }

          tFim1 = millis();

          tempo1 = tFim1 - tInicio1;
        }
      
      }

    
  
    
  }else{
      //Moto entra 1B
      //Testo moto agora
          motoEnt = false;
          tempo1 = 0;
          tFim1 = 0;
          tInicio1 = 0;
          tInicio1 = millis();
          while(tempo1 <= 3000){
          EstadoBotao1B = digitalRead(b1B);
          EstadoBotao2B = digitalRead(b2B);
          //Continua a entrada
          if(EstadoBotao1B == LOW && EstadoBotao2B == HIGH){
            motoEnt = true;
            
            break;
            }

              tFim1 = millis();
              tempo1 = tFim1 - tInicio1;
          }
          //Continuou a entrada
          if(motoEnt == true){

            tempo1 = 0;
            tInicio1 = millis();
            while(tempo1 <= 5000){
              EstadoBotao1B = digitalRead(b1B);
              EstadoBotao2B = digitalRead(b2B);

              if(EstadoBotao2B == LOW && EstadoBotao1B == LOW){
                //Entrou, pode registrar
                Serial.print(5);
               digitalWrite(led5,HIGH);
               delay(1000);
               digitalWrite(led5,LOW);
                break;
                }else{
                    if(EstadoBotao1B == HIGH && EstadoBotao2B == LOW){
                      //Erro
                      Serial.print(4);
                       digitalWrite(led3,HIGH);
                       delay(1000);
                       digitalWrite(led3,LOW);
                      break;
                      }
                  }

                tFim1 = millis();

                tempo1 = tFim1 - tInicio1;
              }
            
            }
              
      }
  
  }

void carroSaida(){
  carroEnt = false;
  tempo1 = 0;
  tFim1 = 0;
  tInicio1 = 0;
  tInicio1 = millis();

  while(tempo1 <= 5000){
    EstadoBotao1A = digitalRead(b1A);
    EstadoBotao1B = digitalRead(b1B);
    EstadoBotao2A = digitalRead(b2A);
    EstadoBotao2B = digitalRead(b2B);

    if(EstadoBotao1A == HIGH && EstadoBotao1B == HIGH){
      //Entrada de carro
      carroEnt = true;
      break;
      }else{
          if(EstadoBotao2A == LOW && EstadoBotao2B == LOW){
            //Desistiu volta do inicio
            carroEnt = false;
            break;
            }
        }

    tFim1 = millis();

    tempo1 = tFim1 - tInicio1;
    }

    if(carroEnt == true){
      tempo1 = 0;
      tFim1 = 0;
      tInicio1 = 0;
      tInicio1 = millis();

      while(tempo1 <= 5000){
        EstadoBotao1A = digitalRead(b1A);
        EstadoBotao1B = digitalRead(b1B);
        EstadoBotao2A = digitalRead(b2A);
        EstadoBotao2B = digitalRead(b2B);

        if(EstadoBotao1A == LOW && EstadoBotao1B == LOW){
          //Volta pro inicio
            carroEnt = false;
            break;
          }else{
              if(EstadoBotao2A == LOW && EstadoBotao2B == LOW){
                //Entrando
                carroEnt = true;
                break;
                }
            }


        tFim1 = millis();

        tempo1 = tFim1 - tInicio1;
        }

        if(carroEnt == true){
          tempo1 = 0;
          tFim1 = 0;
          tInicio1 = 0;
          tInicio1 = millis();

          while(tempo1 <=  5000){
            EstadoBotao1A = digitalRead(b1A);
            EstadoBotao1B = digitalRead(b1B);
            EstadoBotao2A = digitalRead(b2A);
            EstadoBotao2B = digitalRead(b2B);

            if(EstadoBotao1A == LOW && EstadoBotao1B == LOW){
              //Entrada confirmada
              Serial.print(2);
              digitalWrite(led1,HIGH);
              delay(1000);
              digitalWrite(led1,LOW);
              break;
              }else{
                    if(EstadoBotao2A == HIGH && EstadoBotao2B == HIGH){
                      //Erro
                      Serial.print(3);
                      digitalWrite(led3,HIGH);
                      delay(1000);
                      digitalWrite(led3,LOW);
                      break;
                      }
                }
            
            tFim1 = millis();

            tempo1 = tFim1 - tInicio1;
            }
          }
      }
         
  }


void moto_diagonalSai(int a){
  
  if(a == 1){
    //Testo moto agora
    motoEnt = false;  
    tempo1 = 0;
    tFim1 = 0;
    tInicio1 = 0;
    tInicio1 = millis();
    while(tempo1 <= 3000){
    EstadoBotao1B = digitalRead(b1B);
    EstadoBotao2A = digitalRead(b2A);
    //Continua a entrada
    if(EstadoBotao2A == LOW && EstadoBotao1B == HIGH){
      motoEnt = true;
      
      break;
      }
        tFim1 = millis();
        tempo1 = tFim1 - tInicio1;
    }
    //Continuou a entrada
    if(motoEnt == true){

      tempo1 = 0;
      tInicio1 = millis();
      while(tempo1 <= 5000){
        EstadoBotao1B = digitalRead(b1B);
        EstadoBotao2A = digitalRead(b2A);

        if(EstadoBotao2A == LOW && EstadoBotao1B == LOW){
          //Entrou, pode registrar
          Serial.print(6);
         digitalWrite(led4,HIGH);
         delay(1000);
         digitalWrite(led4,LOW);
          break;
          }else{
              if(EstadoBotao2A == HIGH){
                //Erro
                //Serial.print("Erro");
                Serial.print(4);
                 digitalWrite(led3,HIGH);
                 delay(1000);
                 digitalWrite(led3,LOW);
                break;
                }
            }

          tFim1 = millis();

          tempo1 = tFim1 - tInicio1;
        }

  }
    
    }else{

      //Testo moto agora
      motoEnt = false;
      tempo1 = 0;
      tFim1 = 0;
      tInicio1 = 0;
      tInicio1 = millis();
      while(tempo1 <= 3000){
      EstadoBotao1A = digitalRead(b1A);
      EstadoBotao2B = digitalRead(b2B);
      //Saida a entrada
      if(EstadoBotao2B == LOW && EstadoBotao1A == HIGH){
        motoEnt = true;
        
        break;
      }

          tFim1 = millis();
          tempo1 = tFim1 - tInicio1;
      }
      //Continuou a saida
      if(motoEnt == true){

        tempo1 = 0;
        tInicio1 = millis();
        while(tempo1 <= 5000){
          EstadoBotao1A = digitalRead(b1A);
          EstadoBotao2B = digitalRead(b2B);

          if(EstadoBotao1A == LOW && EstadoBotao2B == LOW){
            //Entrou, pode registrar
            Serial.print(6);
           digitalWrite(led4,HIGH);
           delay(1000);
           digitalWrite(led4,LOW);
            break;
            }else{
                if(EstadoBotao2B == HIGH && EstadoBotao1A == LOW){
                  //Erro
                  Serial.print(4);
                   digitalWrite(led3,HIGH);
                   delay(1000);
                   digitalWrite(led3,LOW);
                  break;
                  }
              }

            tFim1 = millis();

            tempo1 = tFim1 - tInicio1;
          }
        
        }

      }
  
}
                    

void motoSaida(int a){
  
  if(a == 1){
    //Testo moto agora
    motoEnt = false;  
    tempo1 = 0;
    tFim1 = 0;
    tInicio1 = 0;
    tInicio1 = millis();
    while(tempo1 <= 3000){
    EstadoBotao1A = digitalRead(b1A);
    EstadoBotao2A = digitalRead(b2A);
    //Continua a entrada
    if(EstadoBotao2A == LOW && EstadoBotao1A == HIGH){
      motoEnt = true;
      
      break;
      }

        tFim1 = millis();
        tempo1 = tFim1 - tInicio1;
    }
    //Continuou a entrada
    if(motoEnt == true){

      tempo1 = 0;
      tInicio1 = millis();
      while(tempo1 <= 5000){
        EstadoBotao1A = digitalRead(b1A);
        EstadoBotao2A = digitalRead(b2A);

        if(EstadoBotao2A == LOW && EstadoBotao1A == LOW){
          //Entrou, pode registrar
          Serial.print(6);
         digitalWrite(led4,HIGH);
         delay(1000);
         digitalWrite(led4,LOW);
          break;
          }else{
              if(EstadoBotao2A == HIGH){
                //Erro
                //Serial.print("Erro");
                Serial.print(4);
                 digitalWrite(led3,HIGH);
                 delay(1000);
                 digitalWrite(led3,LOW);
                break;
                }
            }

          tFim1 = millis();

          tempo1 = tFim1 - tInicio1;
        }

  }
    
    }else{

      //Testo moto agora
      motoEnt = false;
      tempo1 = 0;
      tFim1 = 0;
      tInicio1 = 0;
      tInicio1 = millis();
      while(tempo1 <= 3000){
      EstadoBotao1B = digitalRead(b1B);
      EstadoBotao2B = digitalRead(b2B);
      //Saida a entrada
      if(EstadoBotao2B == LOW && EstadoBotao1B == HIGH){
        motoEnt = true;
        
        break;
        }

          tFim1 = millis();
          tempo1 = tFim1 - tInicio1;
      }
      //Continuou a saida
      if(motoEnt == true){

        tempo1 = 0;
        tInicio1 = millis();
        while(tempo1 <= 5000){
          EstadoBotao1B = digitalRead(b1B);
          EstadoBotao2B = digitalRead(b2B);

          if(EstadoBotao1B == LOW && EstadoBotao2B == LOW){
            //Entrou, pode registrar
            Serial.print(6);
           digitalWrite(led4,HIGH);
           delay(1000);
           digitalWrite(led4,LOW);
            break;
            }else{
                if(EstadoBotao2B == HIGH && EstadoBotao1B == LOW){
                  //Erro
                  Serial.print(4);
                   digitalWrite(led3,HIGH);
                   delay(1000);
                   digitalWrite(led3,LOW);
                  break;
                  }
              }

            tFim1 = millis();

            tempo1 = tFim1 - tInicio1;
          }
        
        }

      }
  
  }

  
