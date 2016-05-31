#ifndef SetupAndLoop_h
#define SetupAndLoop_h

// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ************************* setupGeneral FUNCTION ***************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
void setupGeneral(){
  
    //EEPROM_CONFIG();
    SLOT_CONFIG();
    PINS_CONFIG();
    analogWriteFreq(250);
    analogWriteRange(255);
    //if(usartbridge) 
    //SetAddress(0xCE01, 0xFF00, 0x0000);

// *************************************************************************** 
// *************************** SENSORS INITIALIZE ****************************
// ***************************************************************************

// ---------------------------- DHT BEGIN ------------------------------------
    if(S2 == DHT_SENSOR){
        if(!dht_type)
          dht11.begin();
        else
          dht22.begin();
    }
// ---------------------------- DALLAS BEGIN ---------------------------------
    if(S1 == DALLAS_SENSOR){
        sensors.begin(); //Se inician los sensores DS18B20
    }

// ***************************************************************************    
// ****************************** SETUP SLOTS ********************************
// ***************************************************************************

// ------------------------------ DHT SLOTS ----------------------------------
    if(S2 == DHT_SENSOR){
        Set_Temperature(TEMPERATURE);
        Set_Humidity(HUMIDITY);
    }

// --------------------------- L1-L2-L3 SLOTS --------------------------------
    switch (L1) {  
        case 1:
          Set_SimpleLight(LED1);
          break;
        case 2:
          Set_DimmableLight(LED1);
          break;
        case 4:
          Set_AutoLight(LED1);
          break;
        case 5:
          Set_PulseOutput(LED1);
          break;          
    } 
    switch (L2) {  
        case 1:
          Set_SimpleLight(LED2);
          break;
        case 2:
          Set_DimmableLight(LED2);
          break;
        case 4:
          Set_AutoLight(LED2);
          break;
        case 5:
          Set_PulseOutput(LED2);
          break;          
    }
    switch (L3) {  
        case 1:
          Set_SimpleLight(LED3);
          break;
        case 2:
          Set_DimmableLight(LED3);
          break;
        case 4:
          Set_AutoLight(LED3);
          break;
        case 5:
          Set_PulseOutput(LED3);
          break;          
    }

// ---------------------------- ALARM SLOTS --------------------------------
    if(ALARM_MODE) Set_Antitheft_Main(ALARM);


// ----------------------------- RGB SLOT ----------------------------------      
    if(L1 == RGB_MODE && L2 == RGB_MODE && L3 == RGB_MODE){
        Set_LED_Strip(LEDRGB);
    }          


// ---------------------------- LDR SLOT -----------------------------------  
    if(S3 == LDR_SENSOR){
        Set_T54(LDR);
    }

// -------------------------- DALLAS SLOT ----------------------------------
    if(S1 == DALLAS_SENSOR){
     for(int i=0; i < dallas_qty; i++){
         Set_Temperature(DALLAS + (i*2));
     } 
    }       

// --------------------- BMP180 PRESSURE SLOT ------------------------------
    if(S51 == BMP180){
        //Set_T51(PRESSURE0);
        Set_Pressure(PRESSURE0);
        Set_Temperature(BMP180TEMP);
    }

// -------------------- CAPACITIVE DEBUG SLOTS -----------------------------
    if(cap_debug){
        if(S41 == CAPACITIVE) Set_T51(CAP0);
        if(S42 == CAPACITIVE) Set_T51(CAP1);
        if(S51 == CAPACITIVE) Set_T51(CAP2);
        if(S52 == CAPACITIVE) Set_T51(CAP3);
        if(S41 == CAPACITIVE  || S42 == CAPACITIVE  || S51 == CAPACITIVE  || S52 == CAPACITIVE) Set_T51(THRE);
    }


// ----------------- S51 S52 RELAY RELATED SLOTS ---------------------------
    if(S51 == RELAY || S51 == INVRELAY){
        Set_SimpleLight(RELAY0);
    }
    if(S52 == RELAY || S52 == INVRELAY){
        Set_SimpleLight(RELAY1);
    }   
    
    if(S51 == PULSE_OUTPUT){
        Set_PulseOutput(PULSE0);  
    }
    if(S52 == PULSE_OUTPUT){
        Set_PulseOutput(PULSE1);  
    }
    
    if(S51 == TRIAC){
        Set_DimmableLight(RELAY0);
    }
    if(S52 == TRIAC){
        Set_DimmableLight(RELAY1);
    }      

    if(S51 == GARAGE_DOOR){
        Set_GarageDoor(T2X);
    }

    if(S51 == WINDOW_CURTAIN){
        Set_Windows(T2X);
    }

    if(S51 == OPTO_AND_RELAY){
        Set_SimpleLight(OPTO);
    }


// -------------------------- READSTATE SLOTS ----------------------------------
// ----            Read from EEPROM previous State of SLOTS                 ----
    ReadSTATE();
// -----------------------------------------------------------------------------


// ***************************************************************************    
// **************************** SETUP PIN MODES ******************************
// ***************************************************************************

// ----------------------- S51 S52 RELAY PIN MODES ---------------------------   
    if(S51 == RELAY || S51 == PULSE_OUTPUT || S51 == TRIAC || S51 == GARAGE_DOOR || S51 == WINDOW_CURTAIN){
        digitalWrite(RELAY0P,LOW);
        pinMode(RELAY0P, OUTPUT);
    }
    if(S52 == RELAY || S52 == PULSE_OUTPUT || S52 == TRIAC || S52 == GARAGE_DOOR || S52 == WINDOW_CURTAIN){
        digitalWrite(RELAY1P,LOW);                 
        pinMode(RELAY1P, OUTPUT);
    }

// ----------------- S51 S52 INVERTED RELAY PIN MODES ------------------------
    if(S51 == INVRELAY){
        digitalWrite(RELAY0P,HIGH);
        pinMode(RELAY0P, OUTPUT);
    }
    if(S52 == INVRELAY){
        digitalWrite(RELAY1P,HIGH);                 
        pinMode(RELAY1P, OUTPUT);
    }


// -------------------------- L1 L2 L3 PIN MODES -----------------------------
    if(L1 == ONOFF_MODE || L1 == PWM_MODE || L1 == RGB_MODE || L1 == PIR_MODE || L1 == PULSE_MODE ){
        pinMode(LEDPWMP0, OUTPUT);
    }
    if(L2 == ONOFF_MODE || L2 == PWM_MODE || L2 == RGB_MODE || L2 == PIR_MODE || L2 == PULSE_MODE ){
        pinMode(LEDPWMP1, OUTPUT);        
    }
    if(L3 == ONOFF_MODE || L3 == PWM_MODE || L3 == RGB_MODE || L3 == PIR_MODE || L3 == PULSE_MODE ){        
        pinMode(LEDPWMP2, OUTPUT);
    } 

// -------------------------- L1 L2 L3 PIR MODES -----------------------------
    if(L1 == PIR_MODE){
        if(L1PIR == 0)  pinMode(PIRP1, INPUT);
        else            pinMode(PIRP2, INPUT);
        digitalWrite(LEDPWMP0,LOW);
        SetInput(LED1, Souliss_T1n_AutoCmd);
        Logic_AutoLight(LED1);
        nDigOut(LEDPWMP0, Souliss_T1n_Coil, LED1);
    }    
    if(L2 == PIR_MODE){
        if(L2PIR == 0)  pinMode(PIRP1, INPUT);
        else            pinMode(PIRP2, INPUT);        
        digitalWrite(LEDPWMP1,LOW);
        SetInput(LED2, Souliss_T1n_AutoCmd);
        Logic_AutoLight(LED2);
        nDigOut(LEDPWMP1, Souliss_T1n_Coil, LED2);
    }    
    if(L3 == PIR_MODE){
        if(L3PIR == 0)  pinMode(PIRP1, INPUT);
        else            pinMode(PIRP2, INPUT);      
        digitalWrite(LEDPWMP2,LOW);
        SetInput(LED3, Souliss_T1n_AutoCmd);
        Logic_AutoLight(LED3);
        nDigOut(LEDPWMP2, Souliss_T1n_Coil, LED3);        
    }
    
// -------------------------- L1 L2 L3 RGB MODE ------------------------------
    if(L1 == RGB_MODE && L2 == RGB_MODE && L3 == RGB_MODE){
        pinMode(LEDRP, OUTPUT);
        pinMode(LEDGP, OUTPUT);
        pinMode(LEDBP, OUTPUT);
    }


// ***************************************************************************    
// *************************** BUTTONS PIN MODES *****************************
// ***************************************************************************

// -------------------------- INPUT BUTTONS ----------------------------------
    if(S41 == BUTTONS || S41 == BUTTONS_2_STATE){
        pinMode(BUT0P, INPUT);
    }
    if(S42 == BUTTONS || S42 == BUTTONS_2_STATE){
        pinMode(BUT1P, INPUT);
    } 
    if(S51 == BUTTONS || S51 == BUTTONS_2_STATE){
        pinMode(BUT2P, INPUT);
    }
    if(S52 == BUTTONS || S52 == BUTTONS_2_STATE){
        pinMode(BUT3P, INPUT);
    }      

// ---------------------- INPUT_PULLUP BUTTONS -------------------------------
    if(S41 == BUTTONS_PULLUP || S41 == ALARM_ENDSTOP){
        pinMode(BUT0P, INPUT_PULLUP);
    }
    if(S42 == BUTTONS_PULLUP || S42 == ALARM_ENDSTOP){
        pinMode(BUT1P, INPUT_PULLUP);
    }
    if(S51 == BUTTONS_PULLUP || S51 == ALARM_ENDSTOP){
        pinMode(BUT2P, INPUT_PULLUP);
    }
    if(S52 == BUTTONS_PULLUP || S52 == ALARM_ENDSTOP){
        pinMode(BUT3P, INPUT_PULLUP);
    }


// ----------------- OPTO AND RELAY PIN MODE SETUP ---------------------------
    if(S51 == OPTO_AND_RELAY){
        pinMode(BUT0P, INPUT);
        digitalWrite(RELAY1P,LOW);                 
        pinMode(RELAY1P, OUTPUT);
    }


// ---------------- BMP180 PRESSURE PINMODE SETUP ----------------------------    
    if(S51 == BMP180){
        //Wire.begin(SDAP,SCLP);
        Wire.begin(5,4);
        delay(200);
        if (pressure.begin())
            if(DEBUG_PRESSURE) LOG.print(F("BMP180 init success\r\n"));
        else
        {
            // Oops, something went wrong, this is usually a connection problem,
            // see the comments at the top of this sketch for the proper connections.
            if(DEBUG_PRESSURE) LOG.print(F("BMP180 init fail\r\n"));
        }
    }


// ---------------------- BUTTON GPIO0 SETUP  -------------------------------    
    button0 = true;
    //if (button0) pinMode(0, INPUT);

}


// *********************************************************************************
// *********************************************************************************
// *********************************************************************************
// ************************** fastGeneral FUNCTION *********************************
// *********************************************************************************
// *********************************************************************************
// *********************************************************************************


void fastGeneral(){
    yield();
      
 //     if (button0) {
 //       if(millis()>60000) {
 //          button0 = true;
 //          pinMode(0, INPUT);
 //          LOG.println(F("Button GPIO ENABLED"));
 //       }
 //     }
      
      FAST_50ms() { 
        // ************************************************************************
        // ***************************** RELAYS LOGIC *****************************
        // ************************************************************************  
        // ----------------------------- S51 S52 RELAYS ---------------------------
            if(S51 == RELAY){
                if(Logic_SimpleLight(RELAY0) == Souliss_TRIGGED) StoreSTATE();
                DigOut(RELAY0P, Souliss_T1n_Coil,RELAY0);
            }
            if(S52 == RELAY){
                if( Logic_SimpleLight(RELAY1) == Souliss_TRIGGED) StoreSTATE();
                DigOut(RELAY1P, Souliss_T1n_Coil,RELAY1);
            }


        // ------------------------- S51 S52 INVERTED RELAYS ----------------------
            if(S51 == INVRELAY){
                if(Logic_SimpleLight(RELAY0) == Souliss_TRIGGED) StoreSTATE();
                LowDigOut(RELAY0P, Souliss_T1n_Coil,RELAY0);
            }
            if(S52 == INVRELAY){
                if( Logic_SimpleLight(RELAY1) == Souliss_TRIGGED) StoreSTATE();
                LowDigOut(RELAY1P, Souliss_T1n_Coil,RELAY1);
            }

        // ---------------------------- S51 S52 TRIAC ----------------------------
            if(S51 == TRIAC){
                Logic_DimmableLight(RELAY0);
                analogWrite(RELAY0P, mOutput(RELAY0+1));
            }
            if(S52 == TRIAC){
                Logic_DimmableLight(RELAY1);
                analogWrite(RELAY1P, mOutput(RELAY1+1));
            }  

        // ************************************************************************
        // ***************************** BUTTONS LOGIC ****************************
        // ************************************************************************ 

        // ------------------------------ S41 BUTTONS -----------------------------

            if(L1 == PWM_MODE || L1 == PIR_MODE || L1 == ONOFF_MODE || L1 == PULSE_MODE){
                if(S41 == BUTTONS){
                    DigIn(BUT0P, Souliss_T1n_ToggleCmd, LED1);
                }
                if(S41 == BUTTONS_PULLUP){
                    LowDigIn(BUT0P, Souliss_T1n_ToggleCmd, LED1);
                }
                if(S41 == BUTTONS_2_STATE){
                    DigIn2State(BUT0P, Souliss_T1n_OnCmd, Souliss_T1n_OffCmd, LED1);
                }
            }

        // ------------------------------ S42 BUTTONS -----------------------------
            if(L2 == PWM_MODE || L2 == PIR_MODE || L2 == ONOFF_MODE || L2 == PULSE_MODE){
                if(S42 == BUTTONS){
                    DigIn(BUT1P, Souliss_T1n_ToggleCmd, LED2);
                }
                if(S42 == BUTTONS_PULLUP){
                    LowDigIn(BUT1P, Souliss_T1n_ToggleCmd, LED2);
                }
                if(S42 == BUTTONS_2_STATE){
                    DigIn2State(BUT1P, Souliss_T1n_OnCmd, Souliss_T1n_OffCmd, LED2);
                }
            }

        // ------------------------------ S51 BUTTONS -----------------------------
            if(L3 == PWM_MODE || L3 == PIR_MODE || L3 == ONOFF_MODE || L3 == PULSE_MODE){
                if(S51 == BUTTONS){
                    DigIn(BUT2P, Souliss_T1n_ToggleCmd, LED3);
                }
                if(S51 == BUTTONS_PULLUP){
                    LowDigIn(BUT2P, Souliss_T1n_ToggleCmd, LED3);
                }
                if(S51 == BUTTONS_2_STATE){
                    DigIn2State(BUT2P, Souliss_T1n_OnCmd, Souliss_T1n_OffCmd, LED3);
                }
            }

         // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         // **********  FALTA!!! BOTONES EN S52 ********  NO SE QUE FUNCION DARLE *********
         // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

 

      // **********  FALTA!!! BOTONES EN S52 ********  NO SE QUE FUNCION DARLE *********
                        
            if(L3 == PWM_MODE || L3 == PIR_MODE || L3 == ONOFF_MODE){
              if(button0) LowDigIn(0, Souliss_T1n_ToggleCmd, LED3); 
            }
 


      // ************************************************************************
      // ********************** CAPACITIVE BUTTONS LOGIC ************************
      // ************************************************************************

            if(L1 == PWM_MODE && S41 == CAPACITIVE){
                    Souliss_CapSense(LED1,Souliss_T1n_ToggleCmd,Souliss_T1n_BrightSwitch, BUT0P, cap_thresold, 1500);
                    if(DEBUG_CAPSENSE_ALL) LOG.println("");
            } 

            if(L2 == PWM_MODE && S42 == CAPACITIVE){
                    Souliss_CapSense(LED2,Souliss_T1n_ToggleCmd,Souliss_T1n_BrightSwitch, BUT1P, cap_thresold, 1500);
                    if(DEBUG_CAPSENSE_ALL) LOG.println("");
            }
            
            if(L3 == PWM_MODE && S51 == CAPACITIVE){
                    Souliss_CapSense(LED3,Souliss_T1n_ToggleCmd,Souliss_T1n_BrightSwitch, BUT2P, cap_thresold, 1500);
                    if(DEBUG_CAPSENSE_ALL) LOG.println("");
            }

 // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 // **********  FALTA!!! BOTONES EN S52 ********  NO SE QUE FUNCION DARLE *********
 // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            if(L3 == PWM_MODE && S52 == CAPACITIVE){
                    Souliss_CapSense(LED3,Souliss_T1n_ToggleCmd,Souliss_T1n_BrightSwitch, BUT3P, cap_thresold, 1500);
                    if(DEBUG_CAPSENSE_ALL) LOG.println("");
            }             
     

      // ************************************************************************
      // ********************* IR INFRARED BUTTONS LOGIC ************************
      // ************************************************************************

            if(L1 == ONOFF_MODE || L2 == ONOFF_MODE || L3 == ONOFF_MODE){
                if(IR_ENABLE){
                   irButtons(ir_ONOFF);
                }
            }
            if(L1 == PWM_MODE || L2 == PWM_MODE || L3 == PWM_MODE){
                if(IR_ENABLE){
                  irButtons(ir_PWM);
                }
            }    
           

      // ************************************************************************
      // ************************** L1 L2 L3 LOGICS  ****************************
      // ************************************************************************
            switch (L1) {
                case 1:
                  if (Logic_SimpleLight(LED1) == Souliss_TRIGGED) StoreSTATE();
                  DigOut(LEDPWMP0, Souliss_T1n_Coil,LED1);
                  break;
                case 2:
                  Logic_DimmableLight(LED1);
                  analogWrite(LEDPWMP0, mOutput(LED1+1));
                  break;
                case 4:
                  Logic_AutoLight(LED1);
                  nDigOut(LEDPWMP0, Souliss_T1n_Coil,LED1);
                  break; 
            }
            switch (L2) {
                case 1:
                  if (Logic_SimpleLight(LED2) == Souliss_TRIGGED) StoreSTATE();
                  DigOut(LEDPWMP1, Souliss_T1n_Coil,LED2);
                  break;
                case 2:
                  Logic_DimmableLight(LED2);
                  analogWrite(LEDPWMP1, mOutput(LED2+1));
                  break;
                case 4:
                  Logic_AutoLight(LED2);
                  nDigOut(LEDPWMP1, Souliss_T1n_Coil,LED2);
                  break; 
            }
            switch (L3) {
                case 1:
                  if (Logic_SimpleLight(LED3) == Souliss_TRIGGED) StoreSTATE();
                  DigOut(LEDPWMP2, Souliss_T1n_Coil,LED3);
                  break;
                case 2:
                  Logic_DimmableLight(LED3);
                  analogWrite(LEDPWMP2, mOutput(LED3+1));
                  break;
                case 4:
                  Logic_AutoLight(LED3);
                  nDigOut(LEDPWMP2, Souliss_T1n_Coil,LED3);
                  break; 
            } 


      // ************************************************************************
      // ********************** PIR L1 L2 L3 LOGICS  ****************************
      // ************************************************************************

            if(L1 == PIR_MODE || L2 == PIR_MODE || L3 == PIR_MODE){
              if(ALARM_MODE && mOutput(ALARM) == Souliss_T4n_Antitheft ){   //  IF Alarm is Armed
                  if(L1PIR == 1 || L2PIR == 1 || L3PIR == 1) 
                       DigIn(PIRP1,Souliss_T4n_Alarm,ALARM);     //  Handle the PIR to the Antitheft  
                  if(L1PIR == 2 || L2PIR == 2 || L3PIR == 2)
                       DigIn(PIRP2,Souliss_T4n_Alarm,ALARM);  
              } else {
                if(L1PIR == 1 || L2PIR == 1 || L3PIR == 1){
                  if(L1PIR == 1) {
                    if(DigIn(PIRP1, LIGHT_ON_CYCLE, LED1)){
                        if(L2PIR == 1) mInput(LED2) = LIGHT_ON_CYCLE;
                        if(L3PIR == 1) mInput(LED3) = LIGHT_ON_CYCLE;  
                    }
                  }
                  if(L2PIR == 1) {
                    if(DigIn(PIRP1, LIGHT_ON_CYCLE, LED2)){
                        if(L1PIR == 1) mInput(LED1) = LIGHT_ON_CYCLE;
                        if(L3PIR == 1) mInput(LED3) = LIGHT_ON_CYCLE;  
                    }
                  }
                  if(L3PIR == 1) {
                    if(DigIn(PIRP1, LIGHT_ON_CYCLE, LED3)){
                        if(L1PIR == 1) mInput(LED1) = LIGHT_ON_CYCLE;
                        if(L2PIR == 1) mInput(LED2) = LIGHT_ON_CYCLE;  
                    }
                  }                             
                }
                if(L1PIR == 2 || L2PIR == 2 || L3PIR == 2){
                  if(L1PIR == 2) {
                    if(DigIn(PIRP2, LIGHT_ON_CYCLE, LED1)){
                        if(L2PIR == 2) mInput(LED2) = LIGHT_ON_CYCLE;
                        if(L3PIR == 2) mInput(LED3) = LIGHT_ON_CYCLE;  
                    }
                  }
                  if(L2PIR == 2) {
                    if(DigIn(PIRP2, LIGHT_ON_CYCLE, LED2)){
                        if(L1PIR == 2) mInput(LED1) = LIGHT_ON_CYCLE;
                        if(L3PIR == 2) mInput(LED3) = LIGHT_ON_CYCLE;  
                    }
                  }
                  if(L3PIR == 2) {
                    if(DigIn(PIRP2, LIGHT_ON_CYCLE, LED3)){
                        if(L1PIR == 2) mInput(LED1) = LIGHT_ON_CYCLE;
                        if(L2PIR == 2) mInput(LED2) = LIGHT_ON_CYCLE;  
                    }
                  }                             
                }
              }              
            }            
 

      // ************************************************************************
      // ***************************** ALARM LOGICS  ****************************
      // ************************************************************************
           
            if(ALARM_MODE || S41 == ALARM_ENDSTOP || S42 == ALARM_ENDSTOP || S51 == ALARM_ENDSTOP || S52 == ALARM_ENDSTOP) {
                if(mOutput(ALARM) == Souliss_T4n_Antitheft){
                  if(S41 == ALARM_ENDSTOP) {
                    LowDigIn(BUT0P, Souliss_T4n_Alarm, ALARM);                  //  Handle the Endstop to the Antitheft  
                  }
                  if(S42 == ALARM_ENDSTOP) {
                    LowDigIn(BUT1P, Souliss_T4n_Alarm, ALARM);                  //  Handle the Endstop to the Antitheft  
                  }
                  if(S51 == ALARM_ENDSTOP) {
                    LowDigIn(BUT2P, Souliss_T4n_Alarm, ALARM);                  //  Handle the Endstop to the Antitheft  
                  }
                  if(S52 == ALARM_ENDSTOP) {
                    LowDigIn(BUT3P, Souliss_T4n_Alarm, ALARM);                  //  Handle the Endstop to the Antitheft  
                  }
                }
                Logic_Antitheft_Main(ALARM);
            }
 

      // ************************************************************************
      // ***************************** RGB LOGICS *******************************
      // ************************************************************************

      // ---------------------- CAPACITIVE BUTTONS FOR RGB ----------------------          
            if(L1 == RGB_MODE && L2 == RGB_MODE && L3 == RGB_MODE){
                if(button0) LowDigIn(0, Souliss_T1n_ToggleCmd, LEDRGB);
                if(S41 == CAPACITIVE){
                    Souliss_CapSense(LEDRGB,Souliss_T1n_ToggleCmd,Souliss_T1n_BrightSwitch,BUT0P, cap_thresold, 1500);
                }
                if(S42 == CAPACITIVE){
                    Souliss_CapSense(LEDRGB,Souliss_T1n_ToggleCmd,Souliss_T1n_BrightSwitch,BUT1P, cap_thresold, 1500);
                }
                if(S51 == CAPACITIVE){
                    Souliss_CapSense(LEDRGB,Souliss_T1n_ToggleCmd,Souliss_T1n_BrightSwitch,BUT2P, cap_thresold, 1500);
                }
                if(S52 == CAPACITIVE){
                    Souliss_CapSense(LEDRGB,Souliss_T1n_ToggleCmd,Souliss_T1n_BrightSwitch,BUT3P, cap_thresold, 1500);
                }  

      // --------------------------- BUTTONS FOR RGB ---------------------------
                if(S41 == BUTTONS){
                    DigIn(BUT0P, Souliss_T1n_ToggleCmd, LEDRGB);
                }
                if(S42 == BUTTONS){
                    DigIn(BUT1P, Souliss_T1n_BrightSwitch, LEDRGB);
                }
                if(S51 == BUTTONS){
                    DigIn(BUT2P, Souliss_T1n_ToggleCmd, LEDRGB);
                }
                if(S52 == BUTTONS){
                    DigIn(BUT3P, Souliss_T1n_BrightSwitch, LEDRGB);
                }

      // ------------------------ PULLUP BUTTONS FOR RGB -----------------------                
                if(S41 == BUTTONS_PULLUP){
                    LowDigIn(BUT0P, Souliss_T1n_ToggleCmd, LEDRGB);
                }
                if(S42 == BUTTONS_PULLUP){
                    LowDigIn(BUT1P, Souliss_T1n_BrightSwitch, LEDRGB);
                }
                if(S51 == BUTTONS_PULLUP){
                    LowDigIn(BUT2P, Souliss_T1n_ToggleCmd, LEDRGB);
                }
                if(S52 == BUTTONS_PULLUP){
                    LowDigIn(BUT3P, Souliss_T1n_BrightSwitch, LEDRGB);
                }
               

      // ---------------------- IR BUTTONS FOR RGB ----------------------                
                if(IR_ENABLE){
                    irButtons(ir_RGB);
                } 
                             
     

      // -------------------- LOGIC AND OUTPUT RGB ----------------------                 
                Logic_LED_Strip(LEDRGB);

                analogWrite(LEDRP, mOutput(LEDRGB+1));
                analogWrite(LEDGP, mOutput(LEDRGB+2));
                analogWrite(LEDBP, mOutput(LEDRGB+3));       
            }

      // ************************************************************************
      // ********************** OPTO AND RELAY LOGIC ****************************
      // ************************************************************************
          
            if(S51 == OPTO_AND_RELAY){
                //CODE MISSING get from here:
                //https://github.com/juanpintom/Souliss_Examples/blob/master/E00_Souliss_Wall_Switch_with_PLC_Reading.ino
                SoulissPLC_Read(OPTO, 0, BUT0P, RELAY1P);  //CHANGE PIN 0 TO OTHER PIN!!!
                Logic_SimpleLight(OPTO);  
            }
                
        }


      // ************************************************************************
      // ***************** CAPACITIVE DEBUG LOGIC AND READS *********************
      // ************************************************************************
        
        FAST_110ms(){
                    
          if(cap_debug){
            if(S41 == CAPACITIVE){
              temp = readCapacitivePin(BUT0P);
              if(temp>0) Souliss_ImportAnalog(memory_map, CAP0, &temp); 
            }
            if(S42 == CAPACITIVE){
              temp = readCapacitivePin(BUT1P);
              if(temp>0) Souliss_ImportAnalog(memory_map, CAP1, &temp); 
            }
            if(S51 == CAPACITIVE){
              temp = readCapacitivePin(BUT2P);
              if(temp>0) Souliss_ImportAnalog(memory_map, CAP2, &temp); 
            }
            if(S52 == CAPACITIVE){
              temp = readCapacitivePin(BUT3P);
              if(temp>0) Souliss_ImportAnalog(memory_map, CAP3, &temp); 
            }
            if(S41 == CAPACITIVE || S42 == CAPACITIVE || S51 == CAPACITIVE || S52 == CAPACITIVE){       
              temp = cap_thresold;
              Souliss_ImportAnalog(memory_map, THRE, &temp);       
            }
          }          
        }

        FAST_510ms(){ 
           if(cap_debug){          
              if(S41 == CAPACITIVE) Read_T51(CAP0);
              if(S42 == CAPACITIVE) Read_T51(CAP1);
              if(S51 == CAPACITIVE) Read_T51(CAP2);
              if(S52 == CAPACITIVE) Read_T51(CAP3);
              if(S41 == CAPACITIVE || S42 == CAPACITIVE || S51 == CAPACITIVE || S52 == CAPACITIVE) Read_T51(THRE);
           }
           
      // ************************************************************************
      // *************** GARAGE DOOR AND CURTAIN LOGIC **************************
      // ************************************************************************


           if(S51 == GARAGE_DOOR){
                //*** ENDSTOPS TEST MISSING ***
                LowDigIn(BUT0P, Souliss_T2n_LimSwitch_Open,  T2X);
                LowDigIn(BUT1P, Souliss_T2n_LimSwitch_Close, T2X);
                Logic_GarageDoor(T2X);
                DigOut(RELAY0P, Souliss_T2n_Coil_Open,  T2X);    
                DigOut(RELAY1P, Souliss_T2n_Coil_Close, T2X);                
            }

            if(S51 == WINDOW_CURTAIN){
                Logic_Windows(T2X);
                DigOut(RELAY0P, Souliss_T2n_Coil_Open,  T2X);    
                DigOut(RELAY1P, Souliss_T2n_Coil_Close, T2X);
            }
        }

      // ************************************************************************
      // ********************** PULSE OUTPUT LOGICS *****************************
      // ************************************************************************

        FAST_x10ms(PULSE_TIMER/10){
            
            if(L1 == PULSE_MODE){
                Logic_PulseOutput(LED1);
                DigOut(LEDPWMP0, Souliss_T1n_Coil,LED1);            
            }
            if(L2 == PULSE_MODE){
                Logic_PulseOutput(LED2);
                DigOut(LEDPWMP1, Souliss_T1n_Coil,LED2);             
            }
            if(L3 == PULSE_MODE){
                Logic_PulseOutput(LED3);
                DigOut(LEDPWMP2, Souliss_T1n_Coil,LED3);              
            }                       

            if(S51 == PULSE_OUTPUT){
                Logic_PulseOutput(PULSE0);
                DigOut(RELAY0P, Souliss_T1n_Coil,PULSE0);     
            }
            if(S52 == PULSE_OUTPUT){
                Logic_PulseOutput(PULSE1);
                DigOut(RELAY1P, Souliss_T1n_Coil,PULSE1);     
            }
        }

      // ************************************************************************
      // *********************** DALLAS SENSOR LOGIC ****************************
      // ************************************************************************
 

        FAST_9110ms()    {

            if(S1 == DALLAS_SENSOR){ 
                  // Acquire temperature from the microcontroller ADC
                  sensors.requestTemperatures(); //Prepara el sensor para la lectura
                  for(int i=0; i < dallas_qty; i++){
                      float dallas = sensors.getTempCByIndex(i);
                      if(DEBUG_DALLAS){
                        LOG.print("Dallas "); LOG.print(i); LOG.print(": ");
                        LOG.println(dallas);
                      }
                      Souliss_ImportAnalog(memory_map, DALLAS + (i*2), &dallas);
                      //String stringDallas = "Dallas_sensor_";
                      //stringDallas += i;
                      //if(Send_Emon) SendEmoncms(stringDallas, DALLAS + (i*2));
                  }
                  
            } 
            
        }


      // ************************************************************************
      // **************** SENSORS LOGIC AND SEND TO EMONCMS *********************
      // ************************************************************************


        FAST_2110ms()
        {

      // -------------------- DHT LOGIC AND SEND TO EMONCMS ---------------------
            if(S2 == DHT_SENSOR){
                  if( Logic_Temperature(TEMPERATURE) == Souliss_TRIGGED && Send_Emon ) SendEmoncms("DHT_Temp_Sensor", TEMPERATURE);
                  if( Logic_Humidity(HUMIDITY) == Souliss_TRIGGED && Send_Emon ) SendEmoncms("DHT_Hum_Sensor", HUMIDITY);
                  //if((Logic_Temperature(TEMPERATURE) == Souliss_TRIGGED || Logic_Humidity(HUMIDITY) == Souliss_TRIGGED) && Send_Emon ){
                    //SendThingspeak(TEMPERATURE, HUMIDITY);  
                  //}
                  
            }

      // -------------------------- LDR TO EMONCMS -------------------------------
            
            if(S3 == LDR_SENSOR){
                  if( Logic_T54(LDR) == Souliss_TRIGGED && Send_Emon ) SendEmoncms("Lux_Sensor", LDR);
            }
      
      // ----------------- DALLAS LOGIC AND SEND TO EMONCMS -----------------------
      
            if(S1 == DALLAS_SENSOR){
             for(int i=0; i < dallas_qty; i++){
                  String stringDallas = "Dallas_sensor_";
                  stringDallas += i;
                  if( Logic_Temperature(DALLAS + (i*2)) == Souliss_TRIGGED && Send_Emon ) SendEmoncms(stringDallas, DALLAS + (i*2));
             }
            }                 

      // ----------------- BMP180 LOGIC AND SEND TO EMONCMS------------------------           
            if(S51 == BMP180){
                  if( Logic_Pressure(PRESSURE0) == Souliss_TRIGGED && Send_Emon ) SendEmoncms("BMP180_Pressure", PRESSURE0); 
                  if( Logic_Temperature(BMP180TEMP) == Souliss_TRIGGED && Send_Emon ) SendEmoncms("BMP180_Temp", BMP180TEMP);   
            }
        }

 

     // ----------------------------- LDR LOGIC  ----------------------------------        
        FAST_x10ms(50)
        { 
            if(S3 == LDR_SENSOR){
                float ldr_read = Souliss_GetLux(in, out, SIZEOF)*10.0;  //ORIGINAL
                if(DEBUG_GETLUX){
                    LOG.print("ldrlead: "); 
                    LOG.println(ldr_read);
                }
                if (ldr_read == 0) ldr_read = 0.01;
                Souliss_ImportAnalog(memory_map, LDR, &ldr_read);
                //if(Send_Emon) SendEmoncms("Lux_Sensor", LDR);
            }
        }

 

      // ************************************************************************
      // ***************************** TIMERS ***********************************
      // ************************************************************************

      // ----------------------- WINDOWS TIMER  ---------------------------------        
        FAST_x10ms(WINDOW_TIMER) { 
            if(S51 == WINDOW_CURTAIN){
                Timer_Windows(T2X);               
            }
        }
    
}

void slowGeneral(){
  
    SLOW_10s() {  // Read temperature and humidity from DHT every 110 seconds  

      // ----------------------- RELAY TIMER  ---------------------------------        
        if(S51 == RELAY || S51 == INVRELAY){
            Timer_SimpleLight(RELAY0);
        }
        if(S52 == RELAY || S52 == INVRELAY){
            Timer_SimpleLight(RELAY1);
        }


      // ----------------------- TRIAC TIMER  ---------------------------------        
        if(S51 == TRIAC){
            Timer_DimmableLight(RELAY0);
        }
        if(S52 == TRIAC){
            Timer_DimmableLight(RELAY1);
        }
 

      // -------------------- L1 L2 L3 TIMERS ---------------------------------               
        switch (L1) {
          case 1:
            Timer_SimpleLight(LED1);
            break;
          case 2:
            Timer_DimmableLight(LED1);
            break;
          case 4:
            Timer_AutoLight(LED1);
            break;                     
        }
        switch (L2) {
          case 1:
            Timer_SimpleLight(LED2);
            break;
          case 2:
            Timer_DimmableLight(LED2);
            break;
          case 4:
            Timer_AutoLight(LED2);
            break;                                  
        }
        switch (L3) {
          case 1:
            Timer_SimpleLight(LED3);
            break;
          case 2:
            Timer_DimmableLight(LED3);
            break;
          case 4:
            Timer_AutoLight(LED3);
            break;                                   
        }

      // ----------------------- ALARM TIMER  ---------------------------------         
        if(ALARM_MODE || S41 == ALARM_ENDSTOP || S42 == ALARM_ENDSTOP || S51 == ALARM_ENDSTOP || S52 == ALARM_ENDSTOP) {
            Timer_Antitheft_Main(ALARM);

      // ----------------------- RGB  TIMER  ---------------------------------        
        }
        if(L1 == RGB_MODE && L2 == RGB_MODE && L3 == RGB_MODE){
            Timer_LED_Strip(LEDRGB);
        }

      // ------------------- GARAGE DOOR TIMER  ------------------------------             
        if(S51 == GARAGE_DOOR){
            Timer_GarageDoor(T2X);
        }
    }           

    // ************************************************************************
    // *********************** SENSORS READING ********************************
    // ************************************************************************

    SLOW_x10s(3) {
        
        //SendThingspeakAll();
        if(S51 == BMP180){          
            Souliss_GetPressure_BMP180(PRESSURE0,BMP180TEMP); 
        }
        if(S2 == DHT_SENSOR){
            Souliss_GetDHT(TEMPERATURE, HUMIDITY, true);
        }   
    }

}

#endif
