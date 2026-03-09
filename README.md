Programming assignment 1, a simplified version of monopoly using linked lists

As a side note, HHCDevelopment is another GitHub I have, but it is not linked to Clion or this GitHub in any way. I am unsure why it says that account is the one committing.

To build and run, simply copy main.cpp into a c++ interpreter of your choice and run. This project is built around a singly linked, circular linked list containing a maximum of 40 entries. 

### Core A: Add a Space with Capacity Enforcement (10 points)
**Function:** `addSpace(...)`
**Description:** Adds a new node to the tail, maintains circular structure,
enforces max size 40, returns success/failure beyond capacity.
### Core B: Add Multiple Spaces at Once (10 points)
**Function:** `addMany(...)`
**Description:** Adds spaces sequentially, stops exactly at capacity, returns how
many were added, and does not corrupt pointers.
### Core C: Traversal-Based Player Movement (10 points)
**Function:** `movePlayer(int n)`
**Description:** Moves a player cursor forward by `n` steps node-by-node, wraps
around, and tracks how many times the player passes GO.
### Core D: Controlled Board Display (10 points)
**Function:** `printFromPlayer(int count)`
**Description:** Prints a fixed number of spaces starting from the player (or a
starting point if you design it that way) with a safe stop condition (no infinite
loops).
**Function:** `mirrorBoard()`
**Description:** Reverses the `next` links of all nodes while preserving circular structure
