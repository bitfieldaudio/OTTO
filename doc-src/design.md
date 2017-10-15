# OTTO General Design Ruleset 

(version 0.1, 12-09-2017)

Hi! 
D-I-S-K-U-S here.

Let me explain you how I design all the screens for OTTO, and what I’ve set as rules for this project. 
If you feel like changing things up, that’s fine. This is an open source project after all.

Right, here we go.

## Quirck.

If you are familiar with the OP-1, you will probably know that one of the charms the device has, is its quircky visuals and animations. Giving a beat more punch, by displaying a boxer with a glove, who is ready to give a punch. What’s not to like?

Now, there are no rules to the amount of quirck in the OTTO, really. However, in my (D-I-S-K-U-S) opinion it’s good to keep the quirck down to a minimum where it’s at a level where it’s clear to understand what you’re trying to say with given metaphor, while still giving enough information and reference to visually understand what’s going on. I also think it’s important to realise that that’s the main goal for the graphics: to understand what you are changing, by simply looking at the visual.

## Font

We have created a special font for the OTTO, conveniently called ‘OTTO’. There’s 4 versions:
* Light
* Regular
* Bold
* Monospace

Now, obviously the different weights have different uses. 
Light is used when letters are displayed at a large size, for instance on the metronome screen, or the mixer screen.
Regular is used anywhere it fits, really. Most of the text looks great in this weight. Personally, I find that if the letters have to be displayed at a really small size, Bold works best. It seems to give the best thickness and level of detail to the letters to make them readable no matter how small you make it.

Now, last but not least, Monospace. 
Monospace is used for everything that contains just the numbers. This is to ensure the letters always stay in place. For instance, the timer on the tapedeck is a monospace. To explain it in a quick sense: a number is placed in a sort of rectangle when creating the font. In the monospace, each rectangle has the same dimensions (whereas in a normal font, the 1 would be more narrow than for instance the 4). This way you can keep the numbers tidy, even when they jump from a narrow 11, to a more wide 22, to a higher (and wider) number such as 154.

## Shapes

Shapes! There’s loads of them in the OTTO. What is generally done with the shapes is that when they intersect with another one, you try to give them some space. It’s a bit like giving the other intersecting shape another black outline, so that the other line has a bit more air to breathe.

Shapes are rarely ever just filled with a colour. When they are, they are exceptions. Shapes that have to have a fill as a colour, as ought to be filled with lines instead. See the Lines explanation for more details.

### Rounded Corners

Whilst the OP-1 uses hard corners that arent rounded, we do. It makes everything look a bit more smooth. There’s not a specific amount that is used, it depends what looks good on the object you’re making. Just try and make sure that nothing looks too ‘sharp’, but everything stays clean and polished/smooth.

### Depth

You’re probably going to want to make something in a three dimentional way, at some point. Nice going! That’s really good. However, do realise that it is hard to make a 3D drawing on Canvas. 

What I personally do is some trickery. For instance, I want to visualize a bottle: I can’t really go and make a 3D bottle, so instead, pick a colour and use both a light and dark tint out of that chosen colour. Now the goal is to give the illusion of depth by faking light and shadows. 

## Lines

Currently almost every line used in OTTO is a 2.0 thickness line. Why is this? Simple. A 1.0 line was simply too thin, we feared that this would be too ‘fragile’ on any display used for the OTTO in the future. On the other hand, 3.0 lines are quite thick, and tend to make visuals look really cluttered real fast. I must say however, I can see scenario’s where you would want to use thick lines, so 3.0 are not off limit. Just use them wisely, and make sure everything keeps having a clean look, not a cluttered mess.

One other thing worth mentioning is that all lines in OTTO have rounded endcaps. 

Shapes are sometimes filled with lines, opposed to just plain coloured shapes. There are exceptions, like the ‘brew’ parameter in the Heisen-Synth. This gives users a better understanding of what the maximum reachable amount is, as well as the minimum. It gives the users more control, and communicates the values in a better way. Consider using lines insead of full fill, espcially in high constrasting areas. When you do use lines, use vertical or horizontal lines, as they render alot better at low resolutions. If you want to make an exception to this, like I have on the ‘brew’ parameter in the Heisen-Synth, then at least give a proper alternative. For instance, on my brown ‘brew’ shape is the textual parameter in numbers, so that you can see what you are changing. It is not unusual for a user to expect the highest amount for a parameter to be 100, unless told/instructed otherwise.

### Dotted Lines / Grids

According to Topisani, dotted lines are hard to code. So, unless you’re some kind of code wizard, try to avoid these or try to flatten them so that they’re individual objects. 
I, D-I-S-K-U-S, use them to make certain visuals a bit more clear. When you look at the Mustard Squeeze Compressor, the mustard spaying out of the bottle is placed on a grid/array of dotted lines (which i will from now on just call ‘grid’). In this way you can show the user where this line is going to go, and what it might do to the audio. It gives the line a minimum and a maximum value. When using a visual that is not quite clear enough, this is a nice way to give it more information, while keeping it playful.

## Use of Colour

With OTTO we’re trying to use a default set of colours, to give the style a really continuous feel. Currently these colours are:

**Main colours**
* Blue
* Green
* White
* Red

**Current experimental extra additions** (on behalf of D-I-S-K-U-S)
* Slightly Dark Orange
* Blueish Gray
* Dark Gray

For the main colours, it’s usual to use both the light and dark version of given colour. Look further down in this document to find the HEX codes for these colours.

If you want to use other colours than the ones used in OTTO, that’s fine. Do however make sure the colours fit together, as we really value this at OTTO.

### Background

I wasn’t sure if I had to really list this, but still, here we go: The background is always black. No exceptions.
