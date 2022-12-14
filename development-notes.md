Development Notes

In this project we used the circuit of Watch X to help finding your frisbeegolf disc. The idea was to attach the circuit under the disc as the weight of it was low enough to not affect to the disc too much.


Motivation of the project

We participated to a course named Repurposing Electronics here in University of Oulu. The basic idea of the course was to brainstorm how to reuse some electronic device or components and invent some new purpose for it. In our case, we came up with an idea to use some kind of electronic device to help finding the disc. Our teacher was kind enough to give us his Watch X (smart watch) which is programmable. Frisbeegolf is popular hobby here in Finland so we thought that it would be cool and somewhat relevant project idea to make it easier to find your frisbeegolf disc.


Functionalities

Following requirements were identified when planning the project:
- When the disc lands and user doesn't pick it up or move it, after X minutes the buzzer of the circuit will start to beep
- When the disc is picked up, the beeping will stop 
- The buzzer will also beep as long as the disc is flying to warn other people around
- The leds of the circuit will be turned on to the duration of the fly but will turn off after the landing

Workflow

So, to be able to identify when the disc is actually thrown, we needed to start the coding. Watch X is using Arduino Leonardo so we started to code it in Arduino IDE environment. We used accelerometer as well as gyroscope (MPU6050) data to check that the rotation of the disc is enough to be identified as a throw and that G-Forces are high enough. This way we could prevent the situations where user is for example shaking the disc so it wouldn't beep all the time for nothing. LED:s were integrated to the circuit and we used those in the code light on and light off in the way explained above in "functionalities" text. We also needed the buzzer (ST-0503-3) to make sound helping user to find the disc as well as warn passing by people of the flying disc. Real Time Clock (DS3231MZ+) was used for mesuring the elapsed time. First, we ch
