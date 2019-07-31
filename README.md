# Mock Steam Client
A CLI application that mimics the functionality of Valve's Steam client by keeping track of video game players, the
games they play, their progress within the games they play, the friends they have. The application also has 
functionality to compile some of this data and output reports about them.

The application takes input via stdin and writes output to stdout.

Interface:

AddPlayer <Player ID> <Player Name>
Add player to the data structures. <Player ID> is a positive integer identifier for the player. <Player Name> is a string enclosed by double quotes ("Benjamin Lane"). <Player Name> may contain special characters (excluding double quote).

AddGame <Game ID> <Game Name>
Add game to the data structures. <Game ID> is a positive integer identifier for the game. <Game Name> is a string enclosed by double quotes (i.e. "Mirror's Edge"). <Game Name> may contain special characters (excluding double quote).

AddVictory <Game ID> <Victory ID> <Victory Name> <Victory Points>
Add Victory to the game denoted by <Game ID>. <Victory ID> is an integer identifier for the Victory. <Victory Name> is a string enclosed by double quotes (i.e. "Head over heels"). <Victory Name> may contain special characters (excluding double quote). <Victory Points> is an integer indicating how many gamer points the Victory is worth.

Plays <Player ID> <Game ID> <Player IGN>
Add entry for player playing a specific game. <Player IGN> is a string identifier for that player's particular in game name for the specified game, enclosed by double quotes. <Player IGN> may contain special characters (excluding double quote).

AddFriends <Player ID1> <Player ID2>
Makes players 1 & 2 friends. Friends are mutual.

WinVictory <Player ID> <Game ID> <Victory ID>
Adds Victory indicated to <Player ID>'s record. Each Victory can only be achieved by a given player for once.

FriendsWhoPlay <Player ID> <Game ID>
Report which of player's friends play the specified game.

ComparePlayers <Player ID1> <Player ID2> <Game ID>
Print report comparing player 1 and player 2's Victory records and total Victory scores for the given game. The given game is guaranteed to have been played by both players.

SummarizePlayer <Player ID>
Print record of all of player's friends, games the player plays, and gamer point totals.

SummarizeGame <Game ID>
Print a record of all players who play the specified game and the number of times each of its victories have been accomplished.

SummarizeVictory <Game ID> <Victory ID>
Print a list of all players who have achieved a Victory, and the percentage of players who play that game who have the Victory.

VictoryRanking
Print a summary ranking all players by their total number of gamer points.

Instructions to run:

You can use the makefile to compile and run the code on the compute.cse.tamu.edu server.
In oder to compile using the makefile you can enter the command "make all" (no quotes).
Then type "./main" (no quotes) to run the program after it has finished compiling.

Players, Games, Victories and data relationships must exist before being operated on. IDs must be unique within their scope (i.e. a game's Victories will all have mutually exclusive IDs, but different games may have Victories with the same ID).


WARNING

The program has a tendency to exhibit unusual and improper behavior when inputting commands from a file via redirection.
It is recommended that if you are trying to feed the program a list of commands to copy and paste the list directly into the terminal after starting the program.
It is much more likely that there will not be any unusual behavior by executing the program in this manner.


Instructions to stop execution:

When you are ready to terminate the program, you can enter an 'x' or and 'X' into the terminal or enter CTRL+C to break the process.
The program is designed to run infinitely so you can enter any commands as the desire arises without having to mess with files.
This means that manual termination of the program is required.
