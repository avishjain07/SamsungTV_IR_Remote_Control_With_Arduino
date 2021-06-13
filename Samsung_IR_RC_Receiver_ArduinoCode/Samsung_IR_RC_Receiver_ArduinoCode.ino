/* 
 * ************************ Samsung32 ************************ 
 * Frequency  ->  38 kHz
 * Coding     ->  Pulse distance  
 * Frame      ->  1 start bit + 32 data bits + 1 stop bit
 * 
 * Data       ->  16 address bits + 16 command bits
 * Start Bit  ->  4500us pulse, 4500us pause
 * 0 Bit      ->  550us pulse, 550us pause
 * 1 Bit      ->  550us pulse, 1650us pause
 * 
 * Stop Bit   ->  550us pulse
 * Repetition ->  none
 * Keyboard Repetition  -> Repition after approx. 47msec
 * Bit Order  -> LSB First
 */
 
/*
 * Note:
 * The IR o/p will be reversed as the IR sensor o/p signal is Pulled to HIGH
 * in IDLE state
 */

// Some Macros
#define HIGH_EDGE     1
#define LOW_EDGE      0

//IR sensor pin
const uint8_t IR_Pin = 4;

//Global variables
boolean Recd_packet[32];
unsigned long packet;
unsigned long command;
unsigned long startMicros;

void setup() {

  Serial.begin(9600);
  Serial.println("-----------------------------------------------------------------------------------------------------");
  Serial.println("WELCOME!");
  Serial.println("NO INBUILT LIBRARIES OR FUNCTIONS ARE USED IN THIS PROGRAM EXCEPT micros() & Serial.print()");

  // IR_Pin (Pin 4) will act as IR sensor input
  DDRD &= ~(1 << IR_Pin);
}


unsigned long pulseLen(uint8_t Pin, uint8_t PulseState)
{
  // If the signal is already in PulseState, then wait for the !PulseState
  while( ((PIND >> Pin) & 1) == PulseState );

  // If the signal is in !PulseState, then wait for the PulseState
  while( ((PIND >> Pin) & 1) != PulseState);

  // !PulseState ended, record the time
  startMicros = micros();

  // Wait for the signal to change to !PulseState
  while(((PIND >> Pin) & 1) == PulseState);

  //return the time for which the signal was in PulseState
  return (micros() - startMicros);
}

void loop() {

  Serial.println("-----------------------------------------------------------------------------------------------------");

  packet = 0;
  command = 0;

  //Wait for the Start bit
  while( pulseLen(IR_Pin, LOW_EDGE) < 4000U );

  //Store the subsequent 32 bits following the start bit in the bool array
  for(uint8_t i=0; i<32; i++)
  {
    if( pulseLen(IR_Pin, HIGH_EDGE) > 1000U )
      Recd_packet[i] = 1;
    else
      Recd_packet[i] = 0;
  }

  //From the bool array, store the received frame into packet variable
  for(uint8_t i=0; i<32; i++)
  {
    if(Recd_packet[i])
      packet |= (0x1UL << (31-i));
  }

  //Display the received frame in BIN format
  Serial.print("Recd Frame in BIN format: ");
  for(uint8_t i=0; i<32; i++)
    Serial.print(Recd_packet[i]);

  //Display the received frame in HEX format
  Serial.println();
  Serial.print("Recd Frame in HEX format: ");
  Serial.println(packet, HEX);

  //Store the 8 bit command in the command variable
  Serial.print("Command: ");
  for(uint8_t i=16; i<24; i++)
  {
    if(Recd_packet[i])
      command |= (0x1UL << (i-16));
  }

  //Display the command in the HEX format
  Serial.println(command, HEX);
  Serial.print("Which KEY: ");

  //Map the command value to the corresponding Key and Display the Key pressed
  switch(command)
  {
    case 0x2UL:
      Serial.print("ON/OFF");
      break;
    case 0x4UL:
      Serial.print("NUMERIC KEY 1");
      break;
    case 0x5UL:
      Serial.print("NUMERIC KEY 2");
      break;
    case 0x6UL:
      Serial.print("NUMERIC KEY 3");
      break;
    case 0x7UL:
      Serial.print("VOLUME UP");
      break;
    case 0x8UL:
      Serial.print("NUMERIC KEY 4");
      break;
    case 0x9UL:
      Serial.print("NUMERIC KEY 5");
      break;
    case 0xAUL:
      Serial.print("NUMERIC KEY 6");
      break;
    case 0xBUL:
      Serial.print("VOLUME LOW");
      break;
    case 0xCUL:
      Serial.print("NUMERIC KEY 7");
      break;
    case 0xDUL:
      Serial.print("NUMERIC KEY 8");
      break;
    case 0xEUL:
      Serial.print("NUMERIC KEY 9");
      break;
    case 0xFUL:
      Serial.print("MUTE");
      break;
    default:
      Serial.print("New Key Pressed, not in the database");
  }
  
  Serial.println();
}
