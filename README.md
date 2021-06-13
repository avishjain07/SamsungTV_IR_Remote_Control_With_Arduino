# SamsungTV_IR_Remote_Control_With_Arduino

## Introduction
We use IR Remote controls daily. Home appliances like TV, AC, Audio/Video Systems, nowadays smart appliances like Fans, Water Coolers, etc., comes with a Remote Control. 

<p align="center" width="100%">
    <img width="45%" src="https://user-images.githubusercontent.com/40300359/121795567-a513ce80-cc2f-11eb-9d98-31cbc9613959.png">
</p>

### Ever wondered how an IR Remote Control works? 

IR Remote Control uses Infrared light to transmit data. Now, that's too obvious, I know.

<p align="center" width="100%">
    <img width="70%" src="https://user-images.githubusercontent.com/40300359/121795980-24ef6800-cc33-11eb-8186-b30eb44e07f5.png">
</p>

<br />

It sends pulses of IR light to the receiver, usually modulated (PWM) at around 38kHz, to avoid interference. Each key on the remote has a different code, and different manufacturers use different codes.

<p align="center" width="100%">
    <img width="70%" src="https://user-images.githubusercontent.com/40300359/121796088-0e95dc00-cc34-11eb-9a29-7cdef625693f.png">
</p>

#### The Samsung TV Remote Control at my home uses Samsung32 protocol.

## Samsung32 IR Remote Control Protocol 

<p align="center" width="100%">
    <img width="90%" src="https://user-images.githubusercontent.com/40300359/121796416-75b49000-cc36-11eb-99d8-3f449317dc24.PNG">
</p>

* **Frame:** 1 start bit + 8 bit address + 8 bit address + 8 bit command + inverse of 8 bit command + stop bit

## Capturing Signal with a Logic Analyser

I used a Hantek6022BL DSO-LA and an IR Receiver to capture the signal from the Remote Control.
<br />

<p align="center" width="100%">
    <img width="100%" src="https://user-images.githubusercontent.com/40300359/121796596-d98b8880-cc37-11eb-9f7b-03b3ca750a21.png">
</p>

* **Frame received from pressing ON/OFF key:** start bit + 11100000 11100000 01000000 10111111 + stop bit
**The signal contains:**
* **Address:** 
   * LSB First: 11100000 or 0xE0
   * MSB First: 00000111 or 0x0E
* **Data:**
   * LSB First: 01000000 or 0x40
   * MSB First: 00000010 or 0x02

## Capturing and Decoding the Signal using Arduino

<p align="center" width="100%">
    <img width="50%" src="https://user-images.githubusercontent.com/40300359/121797412-aea43300-cc3d-11eb-8f70-456a8a2d1f92.png">
</p>

I used an Arduino Uno and an IR Receiver to receive the signal and developed an Arduino program *(no inbuilt libraries and functions used, except micros() and Serial.print())* to capture and display the frame in Binary and Hex format. 

Further, I decoded it to display the command and the Key pressed.

<p align="center" width="100%">
    <img width="100%" src="https://user-images.githubusercontent.com/40300359/121797496-2f632f00-cc3e-11eb-8406-1783e1fc99dd.png">
</p>

## Code Walkthrough

## References
1. [Image1 Source](https://www.raspberry-pi-geek.com/var/rpi/storage/images/archive/2014/03/controlling-your-pi-with-an-infrared-remote/abbildung-1/7053-1-eng-US/Abbildung-1_lightbox.png)
2. [Image2 Source](https://coolcosmos.ipac.caltech.edu/system/media_files/binaries/43/large/EMspectrum.jpg?1374800583)
3. [Image2 Source](https://blog.tclaverie.eu/img/ir-mod.png)
4. [Image2 Source](https://www.mikrocontroller.net/articles/IRMP_-_english#SAMSUNG32)
