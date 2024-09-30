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
hat_closed_timestamps = [0,0.25,0.5,0.75,1,1.25,1.5]

# function that generates events from a list of timestamps, an event name and an instrument
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
hat_closed_events = generate_events(hat_closed_timestamps, 'hat_closed_event', hat_closed)

events = kick_events+clap_events+hat_closed_events
events.sort(key=get_timestamp) # sort the events by timestamps
pprint.pprint(events)

# function that plays events according to their timestamps and empties the events list
def handle_events(events):
    startTime = time.time()
    while events:
        current_event = events[0]
        currentTime = time.time()
        if(currentTime - startTime >= current_event['timestamp']):
            print(current_event['timestamp'])
            print(currentTime-startTime)
            current_event['instrument'].play()
            print(current_event['name'])
            events.pop(0)
        else:
        # short sleep to keep my computer from turning into a jet engine
            time.sleep(0.001)
        
    time.sleep(1) # let the last 'note' ring out

handle_events(events)


