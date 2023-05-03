# Volvo Pedal Commander

DRAFT

Bought my car (Volvo V50 T5) second hand from a guy who had put a tune in it. This resulted in an amazing car but with a little (too) agrassive gaspedal.

Discoverd a device called "Pedal Commander" exists and by a few diffrent manufacturers: Pedal Commander, Pedal Box, Sprint Booster, 9 Drive, etc.
Thought about buying one of those devices, but because these devices are more aimed at making the gas pedal of a car more agressive. 
With the exeption of a ECO mode on some devices. 
And beacause i have some questions about the way these cheap chinese pedal changing boxes are handeling the redundant signals of the gas pedal.
Made plans to make my own.

I'm sure with proper tuning software you would be able to change the throttle remapping or something, i wanted to try this first.

## The plan:
![mybox](https://raw.githubusercontent.com/michiel249/VolvoPedalCommander/main/mybox.png)

Take a Arduino and a MCP4725 DAC

arduino + MCP4725 DAC + Volvo Gas Pedal connector Male / Female

write code..

make curve in throttle signal. Happy driving

DRAFT


Refrence:
* https://outbackjoe.com/macho-divertissement/macho-articles/sprint-booster-is-it-worth-it/ (One of the best explainations on how these devices. I also used one of his images)
* http://www.evilution.co.uk/wp-content/uploads/info/sprintbooster/sprintbooster.pdf (Amazing in depth study)
* http://excesstext.com/tag/duratec/ - C648 – Accelerator Pedal Unit (Connector pinout ford.. but same as volvo only drawn diagram i found)
* https://autotechnician.co.uk/autologic-case-study-volvo-v50-intermittent-loss-of-power/ (Connector pinout volvo v50)
