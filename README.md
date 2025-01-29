# NES emulator
An NES emulator coded entirely on C programming language using device drivers developed for the LCOM Curricular Unit.
<br><br>
[![Static Badge](https://img.shields.io/badge/OS-Minix%203-blue)](https://minix3.org/)
<br><br>

## Table of contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [System Requirements](#system-requirements)
4. [Installation](#installation)
5. [Usage](#usage)

## Introduction
This project aims to provide an emulator for the Nintendo Entertainment System (NES) written from the ground up to be portable and easily plugged into any device driver, be it Linux, Windows or even Minix, allowing users to play classic NES games on modern hardware.

## Features
- Accurate emulation of NES CPU, PPU, cartridge loading, mapping and control connection
- Support for the popular NES (.nes) file formats with iNES headers
- Serial connection to the real controller through an ESP8266 being used as a bridge
- Various resolutions and scales
- Very fast loading and unloading of games

## System requirements
This repo only runs on the Minix image developed for the LCOM subject at FEUP.<br>
Download the image [here](https://drive.google.com/file/d/1dM32zTzkTUEqNtTwsO-n__XO6r1Y5I-f/view?usp=sharing).

## Installation
### From releases:
Download the latest version and follow the instructions on the release page.

### From source:
- Move to shared folder with minix
- `git clone git@github.com:itsnova204/LCOM.git`
- Move the roms from `roms/roms.txt` to the `roms/` folder

#### IN MINIX:<br>
```bash
cd labs/src/
make
lcom_run proj
```

## Usage
To run use `lcom_run proj`<br>
The following flags can also be used:
| Syntax | Description |
| --- | ----------- |
| --no-uart | Disables serial connection |
| --player-1-serial | Swaps controller 1 from keyboard to Serial |
| --vmode 0x115 | Enables VBE_MODE_DC_24 video mode while emulator is running |

(Don't forget to wrap the flags in " ")

## Controls
#### IN MENU:<br>
Use the mouse to select the game.<br>
Use Right and Left keyboard arrows to change the game page.

#### IN GAME:<br>
![NES KB CTRL](https://github.com/itsnova204/LCOM/blob/main/doc/image.png?raw=true)
