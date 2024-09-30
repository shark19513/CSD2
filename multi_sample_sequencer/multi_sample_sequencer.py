import time
import pprint # pretty print list on seperate lines
import simpleaudio as sa

kick = sa.WaveObject.from_wave_file("samples/Roland_TR-909/Bassdrum-01.wav")
clap = sa.WaveObject.from_wave_file("samples/Roland_TR-909/Clap.wav")
hat_closed = sa.WaveObject.from_wave_file("samples/Roland_TR-909/Hat_Closed.wav")

bpm = 120

kick_note_durations = [1, 1, 1, 1, 1, 1, 1, 1]
clap_note_durations = [2, 2, 2, 2]
hat_closed_note_durations = [0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5]

#function that converts note durations to timestamps in 16ths
def durations_to_16ths(noteDurations): # got help from ChatGPT for this
    sixteenths = []
    current_timestamp = 0
    for duration in noteDurations:
        sixteenths.append(current_timestamp)
        current_timestamp += duration * 4
    return sixteenths

kick_notes_16th = durations_to_16ths(kick_note_durations)
clap_notes_16th = durations_to_16ths(clap_note_durations)
hat_closed_notes_16th = durations_to_16ths(hat_closed_note_durations)

#function that converts timestamps to time
def sixteenths_to_timestamps(timestamps, BPM):
    quarterNoteDuration = 60 / BPM
    sixteenthNoteDuration = quarterNoteDuration / 4.0
    stamps = []
    for timestamp in timestamps:
        stamps.append(timestamp * sixteenthNoteDuration)
    return stamps

kick_timestamps = sixteenths_to_timestamps(kick_notes_16th, bpm)
clap_timestamps = sixteenths_to_timestamps(clap_notes_16th, bpm)
hat_closed_timestamps = sixteenths_to_timestamps(hat_closed_notes_16th, bpm)

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


