# Ground-tracking LED animations for Longboards

This is the repo for my ground tracking underglow light effect for my longboard. I also made a version with Bluetooth support for remotely controlling the LEDs, see [my corresponding repository](https://github.com/LSchlierf/Glowboard-Bluetooth).

## Showcase

You can find videos and pictures of it here:

[Videos of the effects](https://imgur.com/gallery/86cq9q0)

[Pictures of the underside of the board](https://imgur.com/gallery/5WJpUBA)

[Pictures of the second curcuitry I made](https://imgur.com/gallery/PAADjVJ)

[Pictures of the third curcuitry I made](https://imgur.com/gallery/vMbaO5J) (with Bluetooth support)

[Videos of me riding it](https://imgur.com/gallery/xfXjWVt)

## Functionality

The project uses an Arduino nano which is connected to a little board called "Digi-Dot-Booster".
Connected to the booster there are two parallel LED strips with 50 ws2812b each.
Connected to the nano there is a hall pin which reads 4 magnets on the rear left wheel.
The booster board basically handles communication with the LEDs since a little Arduino nano can't handle both tracking the wheel and commanding the LEDs all at the same time.

Every time the wheel spins by 1/8 of its circumference, the nano creates the new image for the LEDs, tells the booster, which in turn then updates the LEDs.

Especially for the wheel tracking hardware, I drew inspiration from [this instructable from 2011](https://www.instructables.com/Ground-Tracking-LED-Longboard-Mod/), however I didn't like the way they used LEDs, so I changed that.

Every connection to the nano (except for the Digi-Dot-Booster) can be configured at the top of the code (LED_COUNT for the length of the LED strip to fit your board, switch_pin for a switch that changes between ground tracking and moving modes, hall_pin for the hall effect sensor, and button_pin for a button to control them all).  
The data pin of the hall effect sensor needs to be pulled up (connected to Vcc via a resistor), and the button pin needs to be pulled down (connected to gnd via a resistor).  
Info on how to connect the booster to the nano can be found [here on page 2](https://www.led-genial.de/mediafiles/Sonstiges/digi-dot-booster.pdf).
(PDF is in german, I couldn't find an english one. Also the image shows an Arduino Uno but the pin numbers are the same as on an Arduino Nano.)  
Don't forget to use a 470Ω resistor between the booster's "ws2812b" pin and the LEDs' "din" pin and a 1000 μF capacitor across Vdd and gnd.

## Contact

Please do not hesitate to reach out to me if you need help, have any questions about this project or found an error.  
I can be reached via Email: [LucasSchlierf@gmail.com](mailto:LucasSchlierf@gmail.com)

Cheers :)  
Lucas
