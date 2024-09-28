# Fun Columns SDL

## Description:
The aim of this project is to implement the original Free Tools Association (FTA) version of their Fun Columns game in SDL.

For those who may not have heard of the Free Tools Association (FTA) and their influence within the Apple IIGS community many
decades ago, a [website](http://www.freetoolsassociation.com/) is still maintained by Olivier Goguel (one of the original members of the group).

<b>Please Note:</b> This source code is very much in a state of flux and is currently a bit of a mess.
I will provide updates as best as I can :smile:

## Change-log:

* 04/05/2024 - Foundation code.
* 20/07/2024 - Making progress, albeit slowly when I can find time between work and personal life.
* 12/08/2024 - Code refactoring and tidyup.
* 18/08/2024 - Code starting to come together and take shape. Overall structure begining to settle. Ironing out bugs.
* 30/08/2024 - It's been four months already. More incremental progress. Hopefully not much longer now. 

## Compilation
* Make sure to install the following development libraries
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
* Score (points allocation)

## In Progress
* High scores (entry & panel)
* Status (panel)

## Nice to have
* Intro (page / music)
* Game play (music / Sound FX)

## Done
* Cluster detection
* Display updated board (render/update)
* No more moves / Game over
* Random brick selection
* Brick: Rotation [**R**], Left [**←**], Right [**→**]
* Random column selection
* Display in play brick (falling brick)
* Backdrop Colour selection [**^C**]
* About screen [**A**]
* Menu screen
* Info screen [**I**]
* Pause [**P**]
* Quit [**Q**]
* Restart [**^R**]
* Keyboard input (Event Handling)
* Invert backdrop gradient [**ctrl + X**]
* Next piece preview [**N**]
* Tile Shape [**^S**]
* Brick (drop) [**SPC**] - improvment needed
* Game (loop / timing / logic) - still some issues need to be ironed out - improvment needed
* Brick (cluster elimination & explosion)
* Levels [**1 - 6**]

## Bugs
* Visual artifacts

## Author(s)
* Apple IIGS Version: FTA (1990/91)
* SDL Version: Jason Bou-Samra (2024)
