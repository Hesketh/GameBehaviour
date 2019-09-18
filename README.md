# Game Behaviour
The module at University focused on the development of a custom 2D Pathfinding algorithm and Physics system in a platformer, including collision detection and resolution.

![Screenshot](https://raw.githubusercontent.com/Hesketh/GameBehaviour/master/Screenshot.png)

The objective of the game, as the blue player, was to collect all of the yellow coin objects within the level before the red character would pathfind towards you.

# Pathfinding
Instead of traditional methods of performing scene discretisation, I opted to perform a rather unorthodox 'raycast' to detect which pathfinding nodes had become obstructed due to changes in obstacles. If I ever wish to re-implement this in a future project, it is something I would almost certainly change.

# Collision Detection
As a part of my collision detection both a broad phase sweep and prune is undertaken before a narrow phase comparison between potentially colliding objects. As a part of this process the minimum seperation between colliding objects is calculated so that they may be moved out of each other and prevent overlap.

# Pnysics
The physics within this project allow for arbitry forces to apply to different rigid bodies within the scene. As a part of collision detection the forces on each object are resolved to provide a realistic response such as by maintaining some velocity of a much faster moving object after the collision and applying it too both objects within the collision.
