# Volvo Pedal Commander

Draft: Bought my car (Volvo V50 T5) second hand from a guy who had put a tune in it. This resulted in an amazing car but with a little (too) agrassive gaspedal.

Discoverd a device called "Pedal Commander" exists and by a few diffrent manufacturers: Pedal Commander, Pedal Box, Sprint Booster, 9 Drive, etc.
Thought about buying one of those devices, but because these devices are more aimed at making the gas pedal of a car more agressive. 
With the exeption of a ECO mode on some devices. 
And beacause i have some questions about the way these cheap chinese pedal changing boxes are handeling the redundant signals of the gas pedal.
Made plans to make my own.

I'm sure with proper tuning software you would be able to change the throttle remapping or something, i wanted to try this first.

## The plan:
![mybox](https://github.com/michiel249/VolvoPedalCommander/blob/67492089d34f845acd16f4b26fc52be74202fe39/mybox.png)

Take a Arduino, a MCP4725 DAC, Volvo Gas Pedal Male and Female connetors slap all of them together.
write code..
make curve in throttle signal. Happy driving

24-07-2023:
![Proto](https://github.com/michiel249/VolvoPedalCommander/blob/67492089d34f845acd16f4b26fc52be74202fe39/Proto01.png)

Working on a version 0.1 with above draft, took few hours for me to get the pedal to spit out PWM, taped it all together. 
Wrote code that should send signals out as they come in (transparent). First challenge!
Gas pedal pulse width modulated signal is 200hz. default PWM signal of my Arduino Nano is not.

Now trying to get my arduino to spit out 200hz PWM :) it is quite a low frequency so it should be no problem.

p.s. Just realized this probably is going to introduce a 0.005+ second delay in from receiving the signal to sending. Dick Bipes mentioned these devices always have the drawback of adding some delay. This is that with the addition of needing to calculats a new signal.

26-07-2023:
Here we go.

![PWM](https://github.com/michiel249/VolvoPedalCommander/blob/516eb263dda29482b0929efddea80dc824a9bf5c/200hz%20PWM.png)

31-07-2023:
Ok. Apparently, the mismatched frequency wasn't the only problem. After trying out my new quite stable 200 Hz signal, it was still not recognized by my car. Then i realized that my Arduino's PWM is meant to drive LEDs and pulse its own 5v to the car. The original pedal on the other hand pulls down the 5v fed by the car to ground in PW-modulated pulses.

So. version 0.2 i have now wired a transistor up, and I am switching ground with that.

02-08-2023:
Finally got the time to test version 0.2 in my car. it works perfectly! Next, I may need to do some calibration of the DAC voltage and when I'm at it i will also look at the duty cycle. If I'm happy with those I will start trying with some adjusted numbers i think. Also thinking about soldering it all up and putting it in a nice box first. Driving with a breadboard on your floor mat?

03-08-2023: Did not much. Worked out i'm going to use "y = (x^i) / (255^(i-1))" where x is input between 0 and 255 in and i is a exponent to change the curve. - [Demo Graph](https://www.desmos.com/calculator/wxqdl0oarm)

08-08-2023
Rewriting some things before i want to continue, i'm now using libraries for pulse length measurement using interrupts because the Arduino pulsein() function uses delay, and was using a library to help with setting Timer1 at the desired frequency.

I wanted to try the thing that everybody is doing these days and asked uncle Chat-GPT to come up with code for me to set up Timer1 for a given frequency. this gave mixed results. most of them wrong.

So i grabbed the datasheet and a cup of tea,
It took me a few hours, but I can do some simple things with timers now. 


![Schematic](https://github.com/michiel249/VolvoPedalCommander/blob/61bcd3356c9bc5942a8e3b6c8b27a815e094d3e8/VolvoPedalCommander_Schema.png)

REPO TODO:
- Readme Spelling
- Readme split / worklog
- Upload code
- ~~Upload schematic~~
- Organize files


Refrence:
* https://www.maxxecu.com/webhelp/wirings-e_pedals.html (pinout)
* https://outbackjoe.com/macho-divertissement/macho-articles/sprint-booster-is-it-worth-it/ (One of the best explainations on how these devices. I also used one of his images)
* http://www.evilution.co.uk/wp-content/uploads/info/sprintbooster/sprintbooster.pdf (Amazing in depth study)
* http://excesstext.com/tag/duratec/ - C648 – Accelerator Pedal Unit (Connector pinout ford.. but same as volvo only drawn diagram i found)
* https://autotechnician.co.uk/autologic-case-study-volvo-v50-intermittent-loss-of-power/ (Connector pinout volvo v50)
