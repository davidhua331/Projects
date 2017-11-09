# Download the twilio-python library from http://twilio.com/docs/libraries
from twilio.rest import TwilioRestClient 
import random
import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import time
import spidev
import os
import os.path

#Setup for NRF
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
pipes = [[0xE8, 0xE8, 0xF0, 0xF0, 0xE1], [0xF0, 0xF0, 0xF0, 0xF0, 0xE1]]
radio = NRF24(GPIO, spidev.SpiDev())
radio.begin(0, 17)

# Find these values at https://twilio.com/user/account
ACCOUNT_SID = "ACb10d5fa32c4e40731dbfb0cc7121d472" 
AUTH_TOKEN = "1ca8cde4bbd55e134605692fd4cdaf7e" 
from_number = "+19494080188"
client = TwilioRestClient(ACCOUNT_SID, AUTH_TOKEN) 

# Put in phone number to send the message to
# to_number = "+**********" 
to_number = "+**********"

# Media file to create (Sample)
# media = "https://images-na.ssl-images-amazon.com/images/I/81w-W0SVkoL._SL1500_.jpg"

# Example message
# message = client.messages.create(to_number, from_number, body="Hello there!")

# Creates the confirmation code and sends it to the number
def send_confirmation_code(to_number):
    verification_code = generate_code()
    send_sms(to_number , verification_code)
    return verification_code

def setup_rf():
    radio.setPayloadSize(32)
    radio.setChannel(0x76)
    radio.setDataRate(NRF24.BR_1MBPS)
    radio.setPALevel(NRF24.PA_HIGH)

    radio.setAutoAck(False)
    radio.enableDynamicPayloads()
    radio.enableAckPayload()

    radio.openReadingPipe(1, pipes[1])
    radio.printDetails()
    radio.startListening()

# Creates the message to send
def send_sms(to_number, body):
    client = TwilioRestClient(ACCOUNT_SID, AUTH_TOKEN) 
    client.messages.create(to_=to_number, from_=from_number, body=body)

def send_mms():
    client = TwilioRestClient(ACCOUNT_SID, AUTH_TOKEN) 
    client.messages.create(to_=to_number, from_=from_number, media_url=media)

# Main function
def main():
  try:
    setup_rf()
    while(1):
        
        while not radio.available(0):
            time.sleep(1 / 100)

        receivedMessage = []
        radio.read(receivedMessage, radio.getDynamicPayloadSize())
        print("Received: {}".format(receivedMessage))
        send_sms(to_number, receivedMessage)
        
  except KeyboardInterrupt:
    clean_up()
		
# Calls the main function
if __name__ == '__main__': 
    main()
