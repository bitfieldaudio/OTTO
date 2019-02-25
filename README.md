# OTTO

[![Build Status](https://travis-ci.org/topisani/OTTO.svg?branch=master)](https://travis-ci.org/topisani/OTTO)

Making electronic music is awesome! But for most of us, it requires a lot of setup, a lot of moving a mouse around on a laptop that's probably not quite equipped to handle realtime audio processing. Don't you wish you had one single device, which was built to do it all for you, easily and on the fly?

### Introducing the OTTO!

The OTTO is a complete hardware and software solution, with synths, samplers, effects and a sequencer with an audio looper. The interface is modular, easy to use, simple, but most of all, it encourages experimentation. The graphics are quirky, and the workflow is minimal.

Now that proper introductions are made, we would like to invite you to our [discord server](https://discord.gg/4cV9Ucz) where we hang out and discuss all things OTTO.

# The hardware

The OTTO is basically going to be a Rpi3+, a screen, a DAC, 4 encoders and some 30+ buttons/keys. Some of us are currently building the next version of prototypes. We can (so far) show you some nice renders:


<a href="https://ibb.co/mBXmNnH"><img src="https://i.ibb.co/6Z12XK4/render1.png" alt="render1" width="100%" /></a>
<a href="https://ibb.co/17QcPHK"><img src="https://i.ibb.co/HB4ZbmY/render2.png" alt="render2" width="100%" /></a>

# Planned Features for v1.0

* A synth for live performance with midi effects (arpeggiator, etc.)
* 2 FX slots. Synths and drums send to them as a FX bus.
*  Synths and effects are swappable "engines".
*  For drums, a sampler will run in parallel to the sequencer-synth chain. 
*  The drum sampler has 10 channels. These have a simple 1-bar, 16 step volca-style drum-sequencer, with each step corresponding to a white key on the musical keyboard on the prototype currently being built.
*  An audio line input which has FX send and level
*  A simple loop-station-style audio looper that can get audio from line in or synth. It has overdub and one level of Undo.
* 8 save slots which save the state of the entire system. A save button lets you choose the slot to save in. Saves are only performed when you take the action.

# Screenshots:

The UI tries to walk the line between clear, concise and playful:

<img src="https://i.ibb.co/WvKQrc3/image.png" alt="OTTO Screenshots" border="0" width="100%"/>
<i>From top left to bottom right: FM Synth, ADSR Envelope, Reverb effect, Euclidian Sequencer</i>

# The software

The main software is written in modern C++, and the goal is to be as modular and flexible as possible.
For build instructions, check out [the wiki](https://github.com/topisani/OTTO/wiki/Compiling-and-Running).

# Getting Involved

We are a small, but steadily growing, group of people working in all sorts of areas, and we are always looking for contributors in whatever form, or just people who are interested in general. A good place to read more is on the [wiki](https://github.com/topisani/OTTO/wiki) If you are not a developer, we could still really use some help with testing, documenting, hardware, samples and presets for engines, and more. And if I didn't mention it yet, the best place for you to get involved is our [discord server](https://discord.gg/4cV9Ucz). Seriously, it's where all the magic happens!

If you're up for it, we'd love some help, for a lot of different things, like:
 - Software testing
 - Writing documentation
 - Hardware design / testing
 - UI design
 - Creating default samples & settings
and of course, the coding itself, with areas like
 - Synth/Effect design
 - General backend design
 - Hardware bridging
 - Distro setup (a custom linux distro for the Pi would be optimal)

If you feel like joining the adventure, please check out the [guidelines](https://github.com/topisani/OTTO/wiki/Guidelines).

# Credits
 - DSP Framework: [faust](http://faust.grame.fr/) and [Gamma](http://w2.mat.ucsb.edu/gamma/)
 - Vector Graphics: [NanoVG](https://github.com/memononen/nanovg) with [NanoCanvas](https://github.com/Geequlim/NanoCanvas)
 - [fmtlib](http://fmtlib.net), string formatting in C++
 - [json](https://github.com/nlohmann/json/), json for modern C++
