
## The Smoker's Lung
#### Created by Semuel Leijten for CSD2C (2025)

   Program that does processing on an audio signal with various effects some of which
   are controlled with OSC data from a respiration belt.

_mono in --> stereo out_

   **To use:**
   1.  Turn on Vernier Go Direct Respiration Belt
   2.  Run the program Vernier-GoDirect-RespirationBelt_bluetooth.py
   3
3.  a. Enter the device number in the terminal

    b. If the program says "open device 0 = False"
       - Terminate program
       - Shortly press on/off button on respiration belt to reconnect bluetooth
       - Run program again
   4.  Run this program

**NOTE:** The optimal values for the fields m_oscLowerLimit and m_oscUpperLimit inside callback may vary per person.
