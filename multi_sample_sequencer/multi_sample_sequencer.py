import time
import pprint # pretty print list on seperate lines
import simpleaudio as sa

kick = sa.WaveObject.from_wave_file("samples/Roland_TR-909/Bassdrum-01.wav")
clap = sa.WaveObject.from_wave_file("samples/Roland_TR-909/Clap.wav")
hat_closed = sa.WaveObject.from_wave_file("samples/Roland_TR-909/Hat_Closed.wav")

bpm = 120

kick_note_durations = []

kick_timestamps = [0,0.5,1,1.5]
clap_timestamps = [0.5,1.5]

def generate_events(timestamps, event_name, instrument):
    events = []
    for timestamp in timestamps:
        event =  {
            'timestamp': timestamp, 
            'name': event_name,
            'instrument': instrument
        }
        events.append(event)
    timestamps.clear()
    return events

def get_timestamp(event):
    return event['timestamp']

kick_events = generate_events(kick_timestamps, 'kick_event', kick)
clap_events = generate_events(clap_timestamps, 'clap_event', clap)

events = kick_events+clap_events
events.sort(key=get_timestamp)
pprint.pprint(events)

startTime = time.time()

def handle_events(events): # TO DO: fix this function, it gives a poop from empty list error
    while events:
        current_event = events.pop(0)
        currentTime = time.time()
        if(currentTime - startTime >= current_event['timestamp']):
            print(current_event['timestamp'])
            print(currentTime-startTime)
            current_event['instrument'].play()
            print(current_event['name'])
            events.pop(0)
        else:
        # short wait to prevent we'll keep the processor busy when there's
        # nothing to do
            time.sleep(0.001)
        
    time.sleep(1) # let the last 'note' ring out


    handle_events(events)


