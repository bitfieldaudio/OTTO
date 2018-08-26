# OTTO

[![Build Status](https://travis-ci.org/topisani/OTTO.svg?branch=master)](https://travis-ci.org/topisani/OTTO)

Making electronic music is awesome! But for most of us, it requires a lot of setup, a lot of moving a mouse around on a laptop that's probably not quite equipped to handle realtime audio processing. Don't you wish you had one single device, which was built to do it all for you, easily and on the fly?

### Introducing the OTTO!

The OTTO is a complete hardware and software solution, with synths, a sampler, effects, sequencers, and studio modules. The interface is modal, easy to use, simple, but most of all, it encourages experimentation. The graphics are quirky, and the workflow is minimal.

> That sounds cool and all, but haven't I heard about this before? <br>
> — _You_

Yes, the OTTO is heavily inspired by the [OP-1](https://teenage.engineering/products/op-1), but it *is not* an OP-1 clone. If you want an OP-1 you can get it [here](https://teenage.engineering/store).

At this point it might be important to mention that the OTTO is not, and will never be, a commercially aimed product. It is open source by nature, in both hardware and software. If you want an OTTO, you're going to get your hands dirty, if not with the code, at least with the hardware.

Now that proper introductions are made, we would like to invite you to our [discord server](https://discord.gg/4cV9Ucz) where we hang out and discuss all things OTTO.

# Screenshots:

We are currently working on redesigning the UI, but this is some of the ideas we are playing with:

<img src="https://camo.githubusercontent.com/a68ee81ff37e4a8d1415c3c09f74f2ae04631ae2/687474703a2f2f7076742e616c62657274736d2e69742f75692f4f74746f322d31312e706e67" width="640px"> 

<img src="https://image.ibb.co/nGgtbK/shoot.png" width="320px"> <img src="https://image.ibb.co/cpKziz/shoot.png" width="320px">

# The hardware

The OTTO is basically going to be a Rpi3 (or other similar boards, we are looking into that), a screen, a DAC, 4 encoders and some 30+ buttons/keys. Some of us are currently building prototypes, and the formfactors and features vary greatly.
Below this you see two OTTO hardware prototypes. Feature wise they are similar, but [the first one](https://github.com/topisani/OTTO-proto-1) is hand-wired, lasercut, and uses arduino pro micros for handling the keys/encoders. [The second one](https://github.com/cester-ino/OTTO-hardware) is 3D printed, uses a PCB with onboard microcontroler etc.
![](https://github.com/topisani/OTTO-proto-1/raw/master/images/closed.jpeg)
![](https://github.com/cester-ino/OTTO-hardware/blob/cb988b7792a6fb47a434e5be7b6f8e89364f83bb/images/OTTOtac0_1.png)

As you can see, the OTTO can be built very differently depending on your skills, your avaliable resources and tools, and your priorities.
You can also have other features than these two, for example the DSP all supports velocity sensitive keys.

You can find more info about the first prototype design on the "Otto Proto One" on [this dedicated repo](https://github.com/topisani/OTTO-proto-1), and @cester-ino's [over at his repo](https://github.com/cester-ino/OTTO-hardware)

# The software

The software is written in (very) modern C++, and the goal is to be as modular and flexible as possible.

|            | Technology                                                                                                                          |
| :--------- | ----------------------------------------------------------------------------------------------------------------------------------- |
| Core       | C++ 17 (you will need a _very_ new compiler.)                                                                                       |
| Graphics   | C++ wrapper on top of [NanoVG](https://github.com/memononen/nanovg), with swappable backends, currently GLFW and EGL are available. |
| Audio/MIDI | Designed to be swappable, though currently the only one available is [jack](http://jackaudio.org).                                  |
| DSP        | C++ and [Faust](http://faust.grame.fr) (compiled down to C++)                                                                       |

It is possible to run the software on the desktop, with [keybinds](https://github.com/topisani/OTTO/wiki/Keyboard-mapping) emulating the physical buttons and encoders.

For build instructions, check out [the wiki](https://github.com/topisani/OTTO/wiki/Compiling-and-Running).

### Backbone

While OTTOs may differ on a lot, some things are fairly set in stone :

- A Raspberry Pi (or similar) at the core, running a minimal Linux distro.
- A >= 320x240 RGB screen, preferably AMOLED.
- ~30 hardware buttons, so nearly every feature has its own button.
- 4 colour coded rotary encoders (full credits to the OP-1 for that idea), as the main controls. Each screen has a maximum of 4 variables which will be coloured corresponding to their encoder.

# Roadmap

Currently, the OTTO consists mainly of a lot of backend, and some proof-of-concept interfaces. During the following months, we will work on punching out the core structure and interactions, along with adding synths, sequencers and effects.

Other ideas for the future include:
- A mobile app to run the graphics and serve as the screen, since good screens are hard to come by, and you probably already have a great one in your pocket.
- Support for optional hardware, like an FM radio, Bluetooth speakers, a joystick

It should also be noted that the OTTO of course feeds on midi, and you should be able to hook up all sorts of controllers, with sync and control signals for the OTTO variables.

# Getting Involved

We are a small, but steadily growing, group of people working in all sorts of areas, and we are always looking for contributors in whatever form, or just people who are interested in general. If you are not a developer, we could still really use some help with testing, documenting, hardware, samples and presets for engines, and more. And if I didn't mention it yet, the best place for you to get involved is our [discord server](https://discord.gg/4cV9Ucz). Seriously, it's where all the magic happens!

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
 
The DSP can be written seperately in [faust](http://faust.grame.fr), a functional language designed for audio processing that compiles to C++, so if you are up for writing some synths/effects, but not quite ready to take on the beast that is C++ yet, there is still hope.

If you feel like joining the adventure, please check out the [guidelines](https://github.com/topisani/OTTO/wiki/Guidelines).

# Credits
 - Audio Framework: [jack](http://jackaudio.org/)
 - DSP Framework: [faust](http://faust.grame.fr/)
 - Vector Graphics: [NanoVG](https://github.com/memononen/nanovg) with [NanoCanvas](https://github.com/Geequlim/NanoCanvas)
 - [fmtlib](http://fmtlib.net), string formatting in C++
 - [json](https://github.com/nlohmann/json/), json for modern C++
 - [mapbox/variant](https://github.com/mapbox/variant), one of the best variant implementations out there

