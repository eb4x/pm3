# pm3
Premier Manager 3 savegame tool

# Build
mkdir build
cd build
cmake ..
make

# Run
```
Usage: pm3 -[abc] -g 1-8 [-f] [-t 0-113] [-l] [-s] [-h] /path/to/pm3/

  -[abc]
    Dump game[abc]

  -g 1-8, --game=1-8
    Which savegame to work on

  -f
    Print out free players

  -t 0-113
    Change starting team to team ID

  -l
    Level aggression to 5 for all players in all teams

  -s
    Maximize all values for team

  -h
    Displays this help message

  /path/to/pm3/
    Path to PM3
```
