# monitor-ambilight-controller
A custom monitor ledstrip-based ambilight controller, with adjustable color temperature and brightness.

It takes input from 2 potentiometers and on the other end it outputs PWM signals for the Red, Green and Blue LEDs.

I'm still working on a stepless color-temperature scale; now it works with 100-folds on the color temperature scale which means you can't set it at 4750K: it's either 4700K or 4800K, with nothing in between.