# TOP-1: **T**otally **O**riginal **P**roject-**1**

Ah, who doesnt love the [op-1](http://teenage.engineering/products/op-1)? Its a magical beast of modern technology! Everything you need to play around with electronic music, in one self-contained device. Its pretty close to perfect, but not quite - its simplicity is its power, but it's also the source of its shortcomings. And then of course, it's not open source.

Come chat with me at my [discord server](https://discord.gg/4cV9Ucz) if you're interested in the project.

### Introducing the TOP-1!  
To be fair, the TOP-1 is an op-1 clone. But i like to think it's a bit more than that. Some differences will be subtle, and some differences will be big. Especially the non-core modules will differ greatly, as most of them are designed fully independently. The UI too varies, from the tapedeck, which is practically the same, to the metronome, which is very different (see both below).

# Screenshots:  
<img src="doc/images/tapedeck.png" width="45%" alt="Tapedeck"> <img src="doc/images/mixer.png" width="45%" alt="Mixer">
<img src="doc/images/metronome.gif" width="45%" alt="Metronome"> <img src="doc/images/simple-drums.png" width="45%" alt="Drum Synth">

# Current Progress  
The tapedeck is completed, with a few bugs left to iron out, and with the addition of the metronome, mixer, and input selector, the software is just about ready to be used for recording with external synthesizers. It runs in an OpenGLFW window, and the buttons and rotaries are emulated with keyboard shortcuts.

# Keybindings

| Key                 | Action              |
|-------------------------------------------|
| Ctrl                | (mod) Encoder Click |
| Q                   | +Red Encoder        |
| A                   | -Red Encoder        |
| W                   | +Blue Encoder       |
| S                   | -Blue Encoder       |
| E                   | +White Encoder      |
| D                   | -White Encoder      |
| R                   | +Green Encoder      |
| F                   | -Green Encoder      |
| Left Arrow          | Rewind              |
| Shift + Left Arrow  | Skip Rewind         |
| Right Arrow         | Forward             |
| Shift + Right Arrow | Skip Forward        |
| Space               | Play                |
| F1                  | Track 1             |
| F2                  | Track 2             |
| F3                  | Track 3             |
| F4                  | Track 4             |
| Ctrl + T            | Tape                |
| Ctrl + Y            | Mixer               |
| Ctrl + U            | Synth               |
| Ctrl + G            | Metronome           |
| L                   | Enable Loop         |
| I                   | Set Loop In         |
| O                   | Set Loop Out        |
| X                   | Cut Tape Selection  |
| C                   | Lift Tape Selection |
| V                   | Drop Tape Selection |

# Future Plans
 - [ ] Input selection screen - select external audio, internal audio, or the mixer output
 - [ ] Sequencers - A few basic ones are planned
 - [ ] Synthesizers - One or two simple synths
 - [ ] Effects - Filter, EQ, Delay, Bit crushing etc
 - [ ] Sampler - This is the big one!
 - [ ] Modulation - LFO mainly
And from there its just modules, modules, modules

# Installation  
Install the dependencies. For Debian 9+/Ubuntu 16.10+, this should do the trick
```bash
apt install jackd\
    cmake\
    gcc\
    g++\
    pkg-config\
    libglfw3-dev\
    libedit-dev\
    libjack-jackd2-dev\
    libgles2-mesa-dev -y
```
I recommend also installing `patchage` and `jack-keyboard`, but they are in no way required.

With this set up, you can build & run the TOP-1 with
```
cmake .
make -j4
bin/tapedeck
```
or with the provided `install.sh` script.

It should be possible to get the TOP-1 running on Windows/Mac too, but for now you are on your own with that. If you do succeed in doing it, we'd apreciate a guide added to this README

## Faust
Most of the DSP is done using [faust](http://faust.grame.fr), which you will need if you want to change the `.dsp` files.  
It is important to note that `faust2` is required. There are a few ways to install it, so check [this](https://github.com/grame-cncm/faust/tree/faust2) out
Once you have faust installed, verify that the `faust` command uses the correct version. You should see something like this:
```bash
$ faust --version
FAUST : DSP to C, C++, JAVA, JavaScript, ASM JavaScript, WebAssembly (wast/wasm), LLVM IR, Interpreter, Version 2.0.a73
Copyright (C) 2002-2017, GRAME - Centre National de Creation Musicale. All rights reserved. 
```
Any version `2.x.x` should work.

Then, make the apropriate changes in the `.dsp` files, and compile them by running
```
sh compile-faust.sh
```

# Docker
Another way to run the TOP-1 is using the docker image. It should be noted that the docker image will only work on linux.
```bash
cd TOP-1
docker build . -t top-1/topisani
```
Then you will be able to run it using
```bash
sh dockerrun.sh
```
This will build the source, and run TOP-1, patchage and jack-keyboard.
The source will be mounted into docker from the current directory, so the image will not need to be rebuilt when the source is updated.

## Pulseaudio
If you are using pulseaudio, you may have to pause it while running the docker container. This means you won't hear any sound from other applications.
To automatically suspend pulseaudio and restart it when TOP-1 closes, run the container like this:
```bash
pasuspender -- sh dockerrun.sh
```

# Getting Involved
If you're up for it, I'd love some help, for a lot of different things, like
 - Software testing
 - Writing documentation
 - Hardware design / testing
 - UI design
 - Creating default samples & settings
and of course, the coding itself, with areas like
 - Synth/Effect design (I know very little about dsp)
 - General backend design
 - Hardware bridging
 - Distro setup - a custom distro for the Pi might be necessary

If you are interested, come chat with me at my [discord server](https://discord.gg/4cV9Ucz).

# Credits
 - Audio Framework: [jack](http://jackaudio.org/)
 - DSP Framework: [faust](http://faust.grame.fr/)
 - Vector Graphics: [NanoVG](https://github.com/memononen/nanovg) with [NanoCanvas](https://github.com/Geequlim/NanoCanvas)
 - [plog](https://github.com/SergiusTheBest/plog), a great little logging lib
 - [fmtlib](http://fmtlib.net), string formatting in C++
 - [json](https://github.com/nlohmann/json/), json for modern C++
 - [mapbox/variant](https://github.com/mapbox/variant), one of the best variant implementations out there

And of course, none of this would be posible without [spacemacs](http://spacemacs.org/), because i would've given up programming long ago

