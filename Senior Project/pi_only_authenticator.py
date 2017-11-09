# Download the twilio-python library from http://twilio.com/docs/libraries
from twilio.rest import TwilioRestClient 
import random
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

MATRIX = [['1','2','3','A'],
	['4','5','6','B'],
	['7','8','9','C'],
	['*','0','#','D']]

ROW = [7,11,13,15] #GPIO [4,17,27,22]
COL = [12,16,18,22] #GPIO [18,23,24,25]

for j in range(4):
    GPIO.setup(COL[j], GPIO.OUT)
    GPIO.output(COL[j], 1)

for i in range(4):
    GPIO.setup(ROW[i], GPIO.IN, pull_up_down = GPIO.PUD_UP)

#GREEN LED GPIO6
GPIO.setup(31, GPIO.OUT)
GPIO.output(31, GPIO.LOW)

#RED LED GPIO19
GPIO.setup(35, GPIO.OUT)
GPIO.output(35, GPIO.LOW)

#SERVO MOTOR GPIO12
GPIO.setup(32,GPIO.OUT)
p = GPIO.PWM(32,50)
p.start(2.5) #2.5 0, 7.5 N, 12.5 180 

# Find these values at https://twilio.com/user/account
ACCOUNT_SID = "ACb10d5fa32c4e40731dbfb0cc7121d472" 
AUTH_TOKEN = "1ca8cde4bbd55e134605692fd4cdaf7e" 
from_number = "+19494080188"
client = TwilioRestClient(ACCOUNT_SID, AUTH_TOKEN) 

# Put in phone number to send the message to
# to_number = "+**********" 
to_number = "+***********"

# Filename to store and read password
filename = 'pw.txt'

# Media file to create
media = "https://images-na.ssl-images-amazon.com/images/I/81w-W0SVkoL._SL1500_.jpg"

# Example message
# message = client.messages.create(to_number, 
#				   from_number,
#                                  body="Hello there!")

# Creates the confirmation code and sends it to the number
def send_confirmation_code(to_number):
    verification_code = generate_code()
    send_sms(to_number , verification_code)
    return verification_code

# Generate random code
def generate_code():
    return str(random.randrange(100000, 999999))

# Creates the message to send
def send_sms(to_number, body):
    client = TwilioRestClient(ACCOUNT_SID, AUTH_TOKEN) 
    client.messages.create(to_=to_number, from_=from_number, body=body)

def send_mms():
    client = TwilioRestClient(ACCOUNT_SID, AUTH_TOKEN) 
    client.messages.create(to_=to_number, from_=from_number, media_url=media)

# Compares 2 strings and returns boolean
def compare_code(str1, str2):
    if(str1 == str2):
            return True
    else:
            return False

# Change password in txt file
def new_password(file, new_pass):
    with open(file, 'w') as f:
        f.write(new_pass)

# Obtain password from txt file
def getpassword(file):
    with open(file, 'r') as f:
        temp = f.readline().rstrip()
    return temp

# Obtain keypad input
def keypad():
    while(True):
        for j in range(4):
            GPIO.output(COL[j],0)
	    for i in range(4):
		if GPIO.input(ROW[i]) == 0:
		    return MATRIX[i][j]
		    while(GPIO.input(ROW[i]) == 0):
			pass
						
	    GPIO.output(COL[j],1)

#Obtain a string from keypad and '#' is used as "Enter"
def get_keypad_code():
    temp_password = ''
    while(True):
	temp = keypad()
	print temp
	for j in range(4):
		GPIO.output(COL[j],1)
	#print temp
	if(temp == '#'):  
		print temp_password
		return temp_password
	else:
		temp_password += temp
		time.sleep(0.3)

# controls the servo motor
def unlock_servo():
    p.ChangeDutyCycle(2.5)
    time.sleep(0.5)
    #p.ChangeDutyCycle(7.5)
    #time.sleep(1)
    p.ChangeDutyCycle(12.5)
    #time.sleep(1)

def lock_servo():
    p.ChangeDutyCycle(12.5)
    time.sleep(0.5)
    #p.ChangeDutyCycle(7.5)
    #time.sleep(1)
    p.ChangeDutyCycle(2.5)
    #time.sleep(1)

# blinks the green led
def green_led():
    GPIO.output(31, GPIO.HIGH)
    time.sleep(2)
    GPIO.output(31, GPIO.LOW)

# blinks the red led
def red_led():
    GPIO.output(35, GPIO.HIGH)
    time.sleep(2)
    GPIO.output(35, GPIO.LOW)

# cleans up the GPIO and resets the servo
def clean_up():
    p.ChangeDutyCycle(2.5)
    p.stop()
    GPIO.cleanup

# Main function
def main():
  try:
    print("Please enter password: ")
    temp_password = get_keypad_code()
    if(compare_code(temp_password, getpassword(filename))):
	    print("Correct Password")
	    green_led()
            random_code = send_confirmation_code(to_number)
      	    print("Please enter the code sent to your phone number: ")
	    input_code = get_keypad_code()
            if(compare_code(random_code, input_code)):
                print("Correct")
		unlock_servo()
		green_led()
		send_mms()
		print("Press '*' to lock")
		while(True):
		    temp = keypad()
		    if(temp=='*'):
			lock_servo()
			break
                #change = raw_input("Would you like to change password?(y/n): ")
                #if(change == 'y'):
                #        new_pass = raw_input("Please enter new password: ")
                #        new_password(filename, new_pass)
                #        print("Password Changed")
                #        print("Box Unlocked")
                #        send_mms()
                #else:
                #        print("Box Unlocked")
                #        send_mms()
            else:
	    	print("Incorrect Password")
	    	red_led()
	    	clean_up()
                #      print("Incorrect")
                send_sms(to_number, "Failed attempt to unlock")
    else:
	    print("Incorrect Password")
	    red_led()
	    clean_up()
  
  except KeyboardInterrupt:
    clean_up()
		
# Calls the main function
if __name__ == '__main__': 
    main()
