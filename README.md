# Fun Columns SDL

## Description:
The aim of this project is to implement the original Free Tools Association (FTA) version of their Fun Columns game in SDL.

For those who may not have heard of the Free Tools Association (FTA) and their influence within the Apple IIGS community many
decades ago, a [website](http://www.freetoolsassociation.com/) is still maintained by Olivier Goguel (one of the original members of the group).

<b>Please Note:</b> This source code is very much in a state of flux and is currently a bit of a mess.
I will provide updates as best as I can :smile:

## Change-log:

* 04/05/2024 - Foundation code
* 20/07/2024 - Making progress, albeit slowly when I can find time between work and personal life

## Compilation
* Make sure to install the followwing development libraries
  1. SDL2
  2. SDL_image 2.0
  3. libsodium
 
* Type the following commands:

`cd src`<br>
`make`

## Screenshot
![Fun Columns](https://raw.githubusercontent.com/bou-samra/Fun-Columns-SDL/main/img/fun-columns.png)

## Misc.
* Run from command line or GUI
* To move game window using GNOME (Press Super [win] key) and right click/hold mouse) anywhere in game window.

## Todo
* Cluster (removal / realignment)
* Hi scores routine
* Points allocation routine
* Brick (tile cycling / XY movement / drop)
* Next piece preview (in progress)
* Game (loop / timing)
* Intro (page / music)
* Game play (music / Sound FX)

## Done
* Cluster detection research
* Display updated board
* No more moves / Game over
* Random brick selection
* Random column selection
* Backdrop colour selection
* About screen
* Menu screen
* Info screen

## Author(s)
* IIGS Version: FTA (1990/91)
* SDL Version: Jason Bou-Samra (2024)
