import simpleaudio as sa

wave_obj = sa.WaveObject.from_wave_file("python_basics/MP_140_F#_SynthLp1.wav")
play_obj = wave_obj.play()
play_obj.wait_done()

# import simpleaudio.functionchecks as fc

# fc.LeftRightCheck.run()