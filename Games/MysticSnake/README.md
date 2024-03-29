# MysticSnake : game or framework
So I started writing this as a game for my son (and my own amusement) and thinking that "I'll sort out problems as I come by them" ... oh boy was I wrong.
I designed only 3 maps but have a basic map generator.

In the end, 2 years after starting (2022 now) and looong breaks AFK, I'm thinking that this should be kept as a framework that I would reuse for making a game. Keeping the technical part away from the game specifics.
This will be just a demo of the different capabilities of the framework, without any gameplay ambition. Until I change my mind again.

## What does it do now
- top view Zelda style maps up to 32x32 tiles with background scrolling
- player move, 4 directions sprites, alternating L/R steps
- collision detection with respect of pseudo top view
- transition detection (collision with tiles that trigger the transition to next map)
- monster ("AI") support with the most basic version of player chasing
- HUD displaying life etc

## What it will do (one day)
- Inventory menu
- Items, chests, pick it, use it
- Combat 
- Weapons (contact/distant)
- Magic!
- Some format for describing maps interations (ie: yaml file describing transitions between maps, where to start the hero, enemies, etc. and a small parser to convert to a C file?)
- NPC with dialog
- Quests
- Gold, purchase and sell etc
- Sound FX
- Music (don't count on that one)
- GB Color support
- Multi-bank support (now mono bank = 32kb max)

## Map ideas
- a cave, full of crystals
- a labyrinth
- sea/seaside
- a tavern
