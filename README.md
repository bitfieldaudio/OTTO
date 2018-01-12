# OTTO

[![Build Status](https://travis-ci.org/topisani/OTTO.svg?branch=master)](https://travis-ci.org/topisani/OTTO)

Making electronic music is awesome! But for most of us, it requires a lot of setup, a lot of moving a mouse around on a laptop that's probably not quite equipped to handle realtime audio processing. Don't you wish you had one single device, which was built to do it all for you, easily and on the fly?

### Introducing the OTTO!  
The OTTO is a complete hardware and software solution, with synths, a sampler, effects, sequencers, and studio modules. The interface is modal, easy to use, simple, but most of all, it encourages experimentation. The graphics are quirky, and the workflow is minimal.

> That sounds cool and all, but haven't I heard about this before? <br>
>   — _You_

Yes, the OTTO is heavily inspired by the [OP-1](https://teenage.engineering/products/op-1) (as you will clearly see from our graphics), in fact it started off as a direct clone, but these days we try to take a different spin on an idea that is fundamentally the same.

At this point it might be important to mention that the OTTO is not, and will never be, a commercially aimed product. It is open source by nature, in both hardware and software. If you want an OTTO, you're going to get your hands dirty, if not with the code, at least with the hardware.

Now that proper introductions are made, we would like to invite you to our [discord server](https://discord.gg/4cV9Ucz) where we hang out and discuss all things OTTO.

# Screenshots:  
@D-I-S-K-U-S has been working hard on graphics, and these are some of the highlights:

<img src="doc-src/images/1.png" width="320px"> <img src="doc-src/images/2.png" width="320px">
<img src="doc-src/images/3.png" width="320px"> <img src="doc-src/images/4.png" width="320px">

# The software
The software is written in (very) modern C++, and the goal is to be as modular and flexible as possible. Graphics are done with a C++ wrapper on top of [NanoVG](https://github.com/memononen/nanovg), with swappable backends, currently GLFW and EGL are avaliable. Audio/midi drivers are also designed to be swappable, though currently the only one available is [jack](http://jackaudio.org).

Currently the software runs on the desktop, with [keybinds](https://github.com/topisani/OTTO/wiki/Keyboard-mapping) emulating the physical buttons. A lot of the backend is in, though even that is still undergoing a lot of continuous changes, and has a lot of missing features. While we are working more on that, DSP and graphics for engines is being developed and added, so slowly we should start seeing some more content in an application that is currently quite bare.

The DSP is written seperately in [faust](http://faust.grame.fr), a functional language designed for audio processing that compiles to C++, so if you are up for writing some synths/effects, but not quite ready to take on the beast that is C++ yet, there is still hope. As with anything, come over to our [discord server](https://discord.gg/VF6DNP7) to hear more!

For build instructions, check out [the wiki](https://github.com/topisani/OTTO/wiki/Compiling-and-Running), I apologise in advance, but I really want to use C++17, so you will need a _very_ new compiler.

# The hardware
We are still working on the first prototypes, so this is still very much in flux. You can follow along on [the wiki](https://github.com/topisani/OTTO/wiki/Hardware) and of course on [discord](https://discord.gg/PxCvXZp), but here are the basic ideas:

 - A Raspberry Pi (or similar) at the core, running a minimal linux distro.
 - A >= 320x240 RGB screen, preferably amoled.
 - ~30 hardware buttons, so nearly every feature has its own button.
 - 4 color coded rotary encoders (full credits to the OP-1 for that idea), as the main controls. Each screen has a maximum of 4 variables which will be colored corresponding to their encoder.

Those are the things that are fairly set in stone - everything else is up to you. We would like to see the OTTO exist in all sizes, shapes and colours. We plan to build guides, shopping lists and software packages for our own setups and encourage you to do the same.

Other than that, these are some of the ideas that are on the board for the future:

 - A mobile app to run the graphics and serve as the screen, since good screens are hard to come by, and you probably already have a great one in your pocket.
 - Support for optional hardware, like an FM radio, bluetooth speakers, a joystick
 - Whatever you can think of basically!
 
It should also be noted that the OTTO of course feeds on midi, and you should be able to hook up all sorts of controllers, with sync and control signals for the OTTO variables.

# Getting involved
We are a small, but steadily growing, group of people working in all sorts of areas, and we are always looking for contributors in whatever form, or just people who are interested in general. If you are not a developer, we could still really use some help with testing, documenting, hardware, samples and presets for engines, and more. And if I didn't mention it yet, the best place for you to get involved is our [discord server](https://discord.gg/4cV9Ucz). Seriously, it's where all the magic happens!
