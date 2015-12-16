# ICubeX-mapper-juce

A JUCE-based sensor interfacing framework with libmapper bindings.

It started off as an interface application between I-CubeX (www.icubex.com) Sensors and libmapper, but has since been extended as a general sensor visualization.

Currently it is a sandbox project as part of experimentation with the JUCE framework and to aid in the architectural design of the system. Major refactoring will be expected.

Some Goals:

- interface with other microcontrollers
- apply signal visualization, analysis, and processing components
- use the above components to perform higher level feature extraction
- more usable interface for connecting with mapping tools, and/or built in mapping tools


Dec 2015

---

Current development configuration:

Software:
- Mac OSX
- Juce 4.0.x 

NOTE: this project should be checked out into the same level as JUCE_ROOT/examples folder. This way, the modules do not have to be explicitly checked in.

Hardware:
- I-CubeX USB microDig (or Wi-Microdig)
- Some sensors of your choice

Software:
- libmapper (https://github.com/malloch/libmapper)
- ICubeX Connect (http://infusionsystems.com/connectmac)

Originally developed as part of the requirements of MUMT609, McGill University
Johnty Wang (johntywang@gmail.com)
Input Devices and Music Interactions Lab, McGill University
Apr 2015
