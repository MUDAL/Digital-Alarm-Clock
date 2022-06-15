# Alarm Clock 
Project features:  
1. Time
2. Alarm 
3. Tic-tac-toe game played with an IR remote  
4. Music (3 songs)    
It was developed for a classmate and friend of mine.  

## Hardware  
1. Microcontroller  
2. 20x4 LCD screen  
3. 10k Potentiometer  
4. Passive Buzzer  
5. Switch  
6. Batteries (7.4V)  
7. IR remote     
8. IR receiver (TL1838)    
9. DS3231 RTC module with AT24C32 EEPROM      
10. Tactile buttons   

## Credits (For EEPROM [AT24C32] library implementation)  
1. DroneBot Workshop (https://www.youtube.com/watch?v=ShqvATqXA7g)  
2. https://github.com/cyberp/AT24Cx/tree/master/AT24CX_search_IC  

## Credits (for buzzer music)
1. https://www.youtube.com/watch?v=d-WkHkuYSPQ  
2. https://create.arduino.cc/projecthub/GeneralSpud/passive-buzzer-song-take-on-me-by-a-ha-0f04a8  
3. https://forum.arduino.cc/t/halloween-and-star-wars-on-two-push-botton-and-buzzer/630316  
4. https://docs.arduino.cc/built-in-examples/digital/toneMelody  

## Additional info  
In order to prevent conflict between the tone and IRremote libraries,    
the IRremote library (boarddefs.h) was modified to use TIMER1 instead of TIMER2.  
(TIMER2 is already used by the tone library).    

## Video demonstration  
Link: https://www.youtube.com/playlist?list=PLVOrZvUg2mh9ulOvskMB-cN14TpT2BzGC  







