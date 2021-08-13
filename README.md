#Ground-tracking LED animations for Longboards

This is the repo for my ground tracking underglow light effect for my longboard. 
You can find videos and pictures of it here:



Videos of the effects:                    https://imgur.com/gallery/86cq9q0

Pictures of the underside of the board:   https://imgur.com/gallery/5WJpUBA

Videos of me riding it:                   https://imgur.com/gallery/xfXjWVt



The project uses an Arduino nano which is connected to a little board called "Digi-Dot-Booster".
Connected to the booster there are two parallel LED strips with 50 ws2812b each.
Connected to the nano there is a hall pin which reads 4 magnets on the rear left wheel.
The booster board basically handles communication with the LEDs since a little Arduino nano can't handle both tracking the wheel and commanding the LEDs all at the same time.


Everytime the wheel spins by 1/8 of its circumference, the nano creates the new image for the LEDs, tells the booster, which in turn updates the LEDs.


If you want to use my code, feel free to do so for personal, non-commercial projects.


Every connection to the nano can be configured at the top of the code. 
(LED_COUNT for the length of the LED strip to fit your board, switch_pin for a switch that changes between ground tracking and moving modes, hall_pin for the hall effect sensor, and button_pin for a button to control them all) 
The data pin of the hall effect sensor needs to be pulled up (connected to Vcc via a resistor), and the button pin needs to be pulled down (connected to gnd via a resistor).
Info on how to connect the booster to the nano can be found here: https://www.led-genial.de/mediafiles/Sonstiges/digi-dot-booster.pdf on page 2.
(PDF is in german, I couldn't find an english one)
Don't forget to use a 470Ω resistor between the booster's "ws2812b" pin and the LEDs' "din" pin and a 1000 μF capacitor across Vdd and gnd.


Please let me know if you attempt this project, I'm really excited about other people doing it. Also let me know if I can be of any help.


Cheers
Lucas
