# No-Te-Enojes
TL;DR: Program to simulate different player strategies in the board game No Te Enojes.

This program is an integral part of a research project that explores the mathematical properties of both Chutes and Ladders and No Te Enojes. This code specifically runs a 
simulation of No Te Enojes to find empircal gameplay data. 

No Te Enojes is very similar to Parcheesi, and just like Parcheesi, the player must make choices at each turn as to which pawn to move. Implemented in the code are three 
strategies: random, aggressive, and defensive. A random strategy will choose a random, valid pawn to move. An aggressive strategy will choose a pawn if the selected pawn
will take an opponent's pawn, and will default to random choice if such a move isn't possible. A defensive strategy will choose a pawn if it is within a die-roll's reach of
an opponent's pawn AND if the roll is enough to escape this reach. Again, a defensive strategy defaults to random choice if such a move isn't possible. All strategies will 
opt to move a new pawn out of the starting lane if possible, and to move a pawn out of the shortcut space if possible. 

For implementation and computation sake, only two players are implemented. Gameplay data and "optimal" strategies might very well shift when considering the usual 4 or 6
player game. 
