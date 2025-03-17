'''
When using gdx.open_ble(), note that there are a few options:

gdx.open_ble() - When there are no arguments, the function finds all available Go Direct
                ble devices, prints the list to the terminal, and prompts the user
                to select the device to connect.

gdx.open_ble("GDX-FOR 071000U9") - Use your device's name as the argument. The function will
                search for a ble device with this name. If found it will connect it. If connecting
                to multiple devices simply separate the names with a comma, such as
                gdx.open_ble("GDX-FOR 071000U9, GDX-HD 151000C1")

gdx.open_ble("proximity_pairing") - Use "proximity_pairing" as the argument and the function will
                find the ble device with the strongest rssi (signal strength) and connect that
                device.

Below is a simple starter program that uses the gdx functions to collect data from a Go Direct device
connected via Bluetooth.
gdx.open_ble("GDX-RB 0K203841"), gdx.select_sensors([1]), gdx.start(100)
gdx.select_sensors()
gdx.start()
'''

"""Added from Small example OSC client
"""
import argparse
from pythonosc import udp_client
from gdx import gdx

gdx = gdx.gdx()

gdx.open_ble(), gdx.select_sensors([1]), gdx.start(100)

if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument("--ip", default="127.0.0.1",
      help="The ip of the OSC server")
  parser.add_argument("--port", type=int, default=9008,
      help="The port the OSC server is listening on")
  args = parser.parse_args()

  client = udp_client.SimpleUDPClient(args.ip, args.port)


# Data Collection:
print ('Collecting Data...')

collection_complete=False
while not collection_complete:
    try:
        time = 0
# old timer
#for i in range(0,5000):
        measurements = gdx.read()
        if measurements == None:
            break
        print(measurements)
        client.send_message("/juce/breath", measurements)

# gdx.stop()
# gdx.close()

    except KeyboardInterrupt:
        collection_complete=True
        gdx.stop() #Stop sensor readings
        gdx.close() #Disconnect the device
        print ('data  collection stopped by keypress')
