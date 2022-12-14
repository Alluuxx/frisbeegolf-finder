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

So, to be able to identify when the disc is actually thrown, we needed to start the coding. Watch X is using Arduino Leonardo so we started to code it in Arduino IDE environment. We used accelerometer as well as gyroscope (MPU6050) data to check that the rotation of the disc is enough to be identified as a throw and that G-Forces are high enough. This way we could prevent the situations where user is for example shaking the disc so it wouldn't beep all the time for nothing. LED:s were integrated to the circuit and we used those in the code light on and light off in the way explained above in "functionalities" text. We also needed the buzzer (ST-0503-3) to make sound helping user to find the disc as well as warn passing by people of the flying disc. Real Time Clock (DS3231MZ+) was used for mesuring the elapsed time. First, we check that after the disc has landed, we wait for 10seconds or more because the disc could keep roling after the landing and the time checking would be interupted because the user can also interupt the time checking by just picking-up the disc. If there are no interupt and the accelometer doesn't sense any significant change in the values after X amount of time, the buzzer will beep as long as the user picks up the disc. 

We had to start measuring some values what gyroscope and accelometer gives. For gyroscope, we just attached the circuit and battery to the disc and the disc to rotary tray. By this we could get some direction for the values. The setup is seen from the picture under this paragraph. To measure accelometer values, we attached the circuit to disc and started to hit the disc to floor, to hand etc. while our program printed values of the accelometer. This way we got some kind of limit values which we could later define more accurately when throwing and testing the disc. 

![IMG_20221018_132022](https://user-images.githubusercontent.com/66247950/207603487-a9581957-ffa4-40c6-ac5f-ade19a055229.jpg)

We used bubble wrap to protect the circuit and battery so we basically capsulated the components with it. Normal tape wasn't enough to attach the component packet under the disc (as a long time solution) so we bought and used this special tape which you can see under this paragraph. We cleaned the disc's centre part, where we wanted to attach the circuit, with alcohol and taped it to the place. Here is also a picture of the circuit and battery inside the bubble wrap. 

![IMG_20221214_165527](https://user-images.githubusercontent.com/66247950/207639486-743c49d9-263e-4b25-b868-54c5719197d2.jpg)

![IMG_20221129_1933201](https://user-images.githubusercontent.com/66247950/207640230-c7cd00fb-c924-4c40-8dfd-fbaa4b373eef.jpg)

Here is a final picture of the attachment to a disc. After dozens and dozens of throws the tape seems to hold on, even though it was very cold when testing it and the disc sank into snow several times. 

![IMG_20221210_2137441](https://user-images.githubusercontent.com/66247950/207641067-cf9bd35f-306e-47ab-9bd6-6b3d158711cd.jpg)

The rest of the project hours went into testing different limit values as well as to debugging. Some times the disc worked well and some times not. One error was related to the time checking and was then fixed. We also implemented on/off button to control the circuit and it didn't work quite as we wanted some times so there were some problems too which were fixed. One thing was also the fact, that when we were testing g-forces in October without snow, the disc worked fine but after the snow our limit values was not specific anymore because the snow cushioned the impact of the ground. There were a lot of this kind of small things which we noticed while testing the disc. A short demo video of the basic functionality is found from the project called "demovideo.mp4". The video is cutted after the disc lands because there were one minute waiting time before the buzzer would start to beep so keep that in mind. Under this paragraph there is one more picture where you can see that the circuit is actually staying lower than sides of the disc which is a good thing. This way it doesn't affect to the trajectory of the disc almost at all. The circuit is also very light so the disc is still easy to throw to long ranges after you get the new touch to your disc.

![IMG_20221210_213812](https://user-images.githubusercontent.com/66247950/207646080-a55b9852-5fb0-4ded-99dc-c4b5dcacacd2.jpg)

Future of the project

At the moment, the product is a functional entity with the specified functionalities that have been given to it within the course.
For the future, we have determined new functionalities and things to be developed to be brought into this product.
There is bluetooth compatibility on the circuit board, so the purpose would be to harness this possibility into practice and implement it
the player's ability to connect to the disc on the phone. Through this connection the player could view for example, the speeds and
lengths of his throws from his phone screen.

The product works with a 3.7 volt battery, so it requires charging from time to time. Currently, the charging takes place as found on the circuit board
via the usb port, but in the future we could use, for example, wireless charging technology, such as the one placed on top of the disc
with the help of a charging film. Another option could be a charging dock in the disc bag, where the disc is placed and in the disc and disc bag
would be small metallic charging buttons, which, when facing each other, would enable the charging process to be successful.

With the help of the components found on the circuit board, it is also possible to look at the weather conditions, for example temperature and air pressure. By utilizing these, with the help of certain limit values, the disc could be made to adapt to different weather conditions. Roughly
for example -5 degrees below zero would indicate to the disc that there may be snow on the ground, in which case hitting the ground
does not necessarily produce such a high G-value, so its sensitivity should be reduced. Temperatures from -5 degrees upwards would correspond to melt
country, in which case the disc values would be default. This is just an emerging consideration and possible functionality in the future.
The limit values presented here are not planned.





