# Fun Columns SDL

## Description:
The aim of this project is to implement the original Free Tools Association (FTA) version of their Fun Columns game in SDL, which I really enjoyed playing back in the day.

For those who may not have heard of the Free Tools Association (FTA) and their influence within the Apple IIGS community many
decades ago, a [website](http://www.freetoolsassociation.com/) is still maintained by Olivier Goguel (one of the original members of the group).

~~<b>Please Note:</b> This source code is very much in a state of flux and is currently a bit of a mess.
I will provide updates as best as I can :smile:~~

<b>UPDATE:</b><br>
Game in playable state now, feature complete. still needs a bit of a polish.<br>
I really enjoyed programming this game. I hope you find it enjoyable to play.<br>
Much thanks to Olivier Goguel for inspiration and moral support. :smile:

## Change-log:

* 04/05/2024 - Foundation code.
* 20/07/2024 - Making progress, albeit slowly when I can find time between work and personal life.
* 12/08/2024 - Code refactoring and tidyup.
* 18/08/2024 - Code starting to come together and take shape. Overall structure begining to settle. Squashing bugs.
* 30/08/2024 - It's been four months already. More incremental progress.
* 16/10/2024 - All features nearly complete, bugs need to be squashed. Code still a bit rough around the edges.
* 28/10/2024 - Feature complete

## Compilation
* Make sure to install the following development libraries
  * SDL2
  * SDL_image 2.0
  * libsodium
 
* Type the following commands:

`cd src`<br>
`make`

## Screenshot
![Fun Columns](https://raw.githubusercontent.com/bou-samra/Fun-Columns-SDL/main/img/fun-columns.png)

## Misc.
* Run from command line or GUI
* To move game window using GNOME (Press Super [win] key) and right click/hold mouse) anywhere in game window.

## Todo
* 

## In Progress
* High score dotfile (in user home dir)

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
* High scores (entry & panel)
* Status (panel) - needs improvment
* Score (points allocation) - needs improvment

## Bugs
* Visual artifacts
* Intermittent tile elimination issues

## Author(s)
* Apple IIGS Version: FTA (1990/91)
* SDL Version: Jason Bou-Samra (2024)
