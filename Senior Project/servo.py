# Servo Control
import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)

GPIO.SETUP(32,GPIO.OUT)

try:
    while True:
        GPIO.output(32,1)
        time.sleep(0.0015)
        GPIO.output(7,0)

        time.sleep(2)

except KeyboardInterrupt:
    GPIO.cleanup
