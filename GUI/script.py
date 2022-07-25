import serial
import time
import string
#import pynmea2
from pubnub.pnconfiguration import PNConfiguration
from pubnub.pubnub import PubNub
from pubnub.exceptions import PubNubException
import numpy as np
import time
pnChannel = "raspi-tracker"

coor = np.genfromtxt("coordsResuMP.txt", delimiter = " ", skip_header = 1)
pnconfig = PNConfiguration()
pnconfig.publish_key = "pub-c-538b35ba-c872-43c7-8d00-6e6b98ce8d18"
pnconfig.subscribe_key = "sub-c-700df5b3-5efa-4d2a-89d6-f51d59e758a2"
pnconfig.uuid = "boat"
pnconfig.ssl = False

pubnub = PubNub(pnconfig)
pubnub.subscribe().channels(pnChannel).execute()

if __name__ == "__main__":
    cont = 0
    while True:
        if len(coor) > cont:
            lat = coor[cont, 0]
            lng = coor[cont, 1]
            try:
                envelope = pubnub.publish().channel(pnChannel).message({
                    'lat': lat,
                    'lng': lng
                }).sync()
                print("publish timetoken: %d" % envelope.result.timetoken)
            except PubNubException as e:
                print(e)
            cont += 1
        time.sleep(00.1)

