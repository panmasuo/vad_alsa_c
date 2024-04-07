# VAD algorithm implemented using ALSA library in C programming language

Voice Activity Detection (VAD) algorithm made based on Moattar and Homayounpour's publication [A simple but efficient real-time voice activity detection algorithm](https://www.researchgate.net/publication/255667085_A_simple_but_efficient_real-time_voice_activity_detection_algorithm)

All of the code is written in C language. Using:
1. ALSA (for sound proccesing)
2. Pthreads (for multithreading)

## Building
sudo apt-get install ninja-build
Built and tested with `gcc-13` using `c23` standard.

Make sure to install all needed dependencies:
```
sudo apt-get install libasound2-dev 
```
```
sudo apt-get install wiringpi
```
