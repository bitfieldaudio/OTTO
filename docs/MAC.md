# OTTO on macOS

Desktop build of [bitfieldaudio/OTTO](https://github.com/bitfieldaudio/OTTO) with CoreAudio, GLFW emulator UI, and AppKit main-thread graphics.

## Build & run

```bash
export PATH="$PWD/.tools:$PATH"   # python shim for Skia
just setup
just run-mac                    # speakers by default when unconfigured
# or:
just run-mac -c ottoconf.mac.json   # BlackHole duplex
```

Bundle a Finder-launchable app:

```bash
just bundle-mac
open dist/OTTO.app
```

## First sound

FM synth opens by default. Master volume defaults to **75%**. Hold **Option (⌥)** and tap piano keys:

| Keys | Role |
|------|------|
| ⌥ + `Z X C V B N M ,` | Lower / upper piano (seq) |
| ⌥ + `Q W E R T Y U I O P` | Seq pads |
| ⌥ + `3 4 6 7 8 0` / `S D G H J` | Channel / black keys |
| `↑` / `↓` | Octave ± |

## What you can click

The LCD is **not** a touchscreen. Interact like the hardware:

| Target | Action |
|--------|--------|
| Front-panel buttons | Click to navigate (every labeled key opens a screen) |
| Hardware encoders | Click = push; scroll = turn |
| **LCD screen** | Scroll = turn encoder (column → blue/green/yellow/red); click = push that encoder |

### Real engines

`arp` · `synth` · `envelope` · `voices` · `slots` · `master`  
(`shift`+`synth` = FM / analogue selector)

### Placeholders (open, show “coming soon”)

`sequencer` · `sampler` · `looper` · `mixer` · `fx1` · `fx2` · `sends` · `external` · `settings` · `omega` · `twist1/2`

### Transport

- **Play** / **Record** keys toggle LEDs (no sequencer yet)
- **Sigma** opens the transport status screen

## Keyboard (no Option)

| Keys | Action |
|------|--------|
| `Q/A` `W/S` `E/D` `R/F` | Blue / green / yellow / red encoders (±) |
| `Ctrl` or `⌘` + those | Encoder click |
| `1`–`6` | Arp, synth, envelope, voices, fx1, fx2 |
| `7` `8` `P` `M` | Sends, slots, play, master |
| `Z X C V` | Pages A–D (context: synth ops/modes) |
| `Shift` | Shift |
| `⌘Q` / `⌘W` | Quit (clean shutdown) |

## Audio

- Default sample rate: **48000**
- Unconfigured: prefers **Speakers** (output-only); else a duplex device (BlackHole)
- Skips Background Music / Zoom / Teams (they hang CoreAudio)
- Settings persist to `./ottoconf.json` on quit

Example (`ottoconf.mac.json`):

```json
{
  "AudioDriver": {
    "input_device": "Existential Audio Inc.: BlackHole 16ch",
    "output_device": "Existential Audio Inc.: BlackHole 16ch",
    "sample_rate": 48000,
    "buffer_size": 256
  },
  "MidiDriver": {
    "input_port": "none"
  }
}
```

## MIDI

- Always opens virtual port **OTTO in**
- Connects to **one** hardware port (not every device)
- `MidiDriver.input_port`:
  - omit / `""` — first real port (skips Midi Through / OTTO)
  - `"none"` — virtual only
  - exact port name — that device only

## Paths

| Path | Contents |
|------|----------|
| `resources/` | Emulator SVG + fonts |
| `data/` | Presets, samples, wavetables, `state.json` |
| `build/bin/otto` | Binary |
| `dist/OTTO.app` | App bundle (after `just bundle-mac`) |
