import time
import pprint # pretty print list on seperate lines
import simpleaudio as sa

kick = sa.WaveObject.from_wave_file("samples/Roland_TR-909/Bassdrum-01.wav")
clap = sa.WaveObject.from_wave_file("samples/Roland_TR-909/Clap.wav")
hat_closed = sa.WaveObject.from_wave_file("samples/Roland_TR-909/Hat_Closed.wav")

bpm = 120

kick_note_durations = [1, 1, 1, 1, 1, 1, 1, 1]
kick_note_offset = 0

clap_note_durations = [2, 2, 2, 2]
clap_note_offset = 1

hat_closed_note_durations = [0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5]
hat_closed_note_offset = 0

#function that converts note durations to timestamps in 16ths
def durations_to_16ths(noteDurations): # got help from ChatGPT for this
    sixteenths = []
    current_timestamp = 0
    for duration in noteDurations:
            sixteenths.append(current_timestamp)
            current_timestamp += duration * 4
    return sixteenths

# function that turns the offset note duration into 16ths
def offset_to_16ths(offset):
    return offset * 4

kick_notes_16th = durations_to_16ths(kick_note_durations)
kick_notes_offset_16th = offset_to_16ths(kick_note_offset)

clap_notes_16th = durations_to_16ths(clap_note_durations)
clap_notes_offset_16th = offset_to_16ths(clap_note_offset)

hat_closed_notes_16th = durations_to_16ths(hat_closed_note_durations)
hat_closed_notes_offset_16th = offset_to_16ths(hat_closed_note_offset)

#function that converts timestamps to time
def sixteenths_to_timestamps(timestamps, BPM, offset):
    quarternote_duration = 60 / BPM
    sixteenthnote_duration = quarternote_duration / 4.0
    stamps = []
    for  timestamp in timestamps:
        time_value = (timestamp + offset) * sixteenthnote_duration
        stamps.append(time_value)
    return stamps

kick_timestamps = sixteenths_to_timestamps(kick_notes_16th, bpm, kick_notes_offset_16th)
clap_timestamps = sixteenths_to_timestamps(clap_notes_16th, bpm, clap_notes_offset_16th)
hat_closed_timestamps = sixteenths_to_timestamps(hat_closed_notes_16th, bpm, hat_closed_notes_offset_16th)

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
    timestamps.clear() # clear list but not sure if that's necessary?
    return events

def get_timestamp(event):
    return event['timestamp']

kick_events = generate_events(kick_timestamps, 'kick_event', kick)
clap_events = generate_events(clap_timestamps, 'clap_event', clap)
hat_closed_events = generate_events(hat_closed_timestamps, 'hat_closed_event', hat_closed)

events = kick_events+clap_events+hat_closed_events
events.sort(key=get_timestamp) # sort the events by timestamps

# function that handles events
def handle_event(event):
    print(event['timestamp'])
    print(current_time-start_time)
    event['instrument'].play()
    print(event['name'])

start_time = time.time()

# loop that checks the timestamps of the events and calls the handle_event function
# ChatGPT helped me come up with this
while events:
    current_time = time.time()
    current_timestamp = events[0]['timestamp'] # store the timestamp of the event at index 0 here
    if current_time - start_time >= current_timestamp:
        simultaneous_events = []
        # compare the timestamp of the element at index 0 to the current timestamp
        # collect events that share the same timestamp in a list
        while events and events[0]['timestamp'] == current_timestamp:
            simultaneous_events.append(events.pop(0))
        # play the simultaneous events with a loop that iterates through the list
        for event in simultaneous_events:
            handle_event(event)
    else:
        # short sleep to keep my computer from turning into a jet engine
        time.sleep(0.001)
  
time.sleep(1) # let the last 'note' ring out


