"""
# LES 2

import time
import simpleaudio as sa

rhythm = []

# rhythm list contains delays in seconds
rhythm.append(1)
rhythm.append(2)
rhythm.append(1)
rhythm.append(0.5)
rhythm.append(1)

boop = sa.WaveObject.from_wave_file("python_basics/boop.wav")

for delay in rhythm:
    
    play_obj = boop.play()
    time.sleep(delay)

play_obj.wait_done()

# LES 3
# Comulatieve afwijking

# t_now = time.time()
# t_rel = time.time - t_now

while True:
    t_cur = time.time() - start.time
    if t_cur > ts:
        sample_plop.play()
        if len(time_stamps) > 0:
            ts = time
 

import time

t = time.time()

for i in range(10):
    print("delta t:", time.time() - t)
    t = time.time()
    time.sleep(1)
"""
# LES 4
# Dictionaries

import simpleaudio as sa

"""
# dictionaries
aDictionary = {'sample': 'kick', 'ts': '0.75'}
"""

kick = sa.WaveObject.from_wave_file("python_basics/boop.wav")
snare = sa.WaveObject.from_wave_file("python_basics/boop.wav")

kick_event = { 
    'timestamp': 1000, # msec w.r.t. start of program
    'instrument_name': 'kick', # name of instrument *as text*
    'instrument': kick, # audio sample
    'volume': 71, # numeric MIDI-based, 0-127
}

snare_event = { 
    'timestamp': 2000, # msec w.r.t. start of program
    'instrument_name': 'snare', # name of instrument *as text*
    'instrument': snare, # audio sample
    'volume': 42, # numeric MIDI-based, 0-127
}

events = [kick_event, snare_event] # hoe sorteer je dit? sorteren op timestamp is logisch
print(events)

def get_timestamp(event):
    return event['timestamp']

events.sort(key=get_timestamp, reverse=True) # zo dus
print(events)

def handle_event(event):
    print(event['timestamp'])
    print(event['instrument_name'])
    print(event['volume'])
    event['instrument'].play()

handle_event(kick_event)
handle_event(snare_event)