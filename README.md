# akli2-kevinz6-ptelag2
# Final Project

**Authors**: 
Alexander Li - [`akli2@illinois.edu`]\
Praval Telagi - [`ptelag2@illinois.edu`]\
Kevin Zhao - [`kevinz6@illinois.edu`]

# Flight Path Generator

![](https://i.imgur.com/IfaxmK3.png)
## [CS225 Final Project Video](https://www.youtube.com/watch?v=azosblYwf2k)
[![CS225 Final Project Video](https://img.youtube.com/vi/azosblYwf2k/maxresdefault.jpg)](https://www.youtube.com/watch?v=azosblYwf2k)


## Features
* The user will be able to generate a flight path from inputted airports.
* The program will perform **Dijkstra's algorithm** to find the shortest path if there is only 1 destination airport
* The program will perform **Landmark Path** to find the shortest path between multiple destination airports if more than 1 destination airport is inputted.
* The program also uses **BFS Search** to label edges and exports these edges to *BFSTravel.txt*.
* We calculated the number of connected components using **Disjoint Sets**.
* The program will generate a route (if one exists) between each airport
* The total distance (in kilometers) for the generated route will also be displayed

## Dependencies
This program will require Catch2 library in order to run unit tests. These are already included within our files.\
**We recommend the user to run on EWS if any issues running locally occurs.**

* [Catch2](https://github.com/catchorg/Catch2)

### Data Files
Our team is using the Open Flights Data Set. Open flights is an open source data set of flight routes and airports. The data is currently dated from 2014 and has no path for updates but is still interesting for historical study. A link to the data files can be found below.

* [Open Flights](https://openflights.org/data.html)

Our program only uses airports.dat and routes.dat

## Make Commands
There are a few commands necessary for this program.
| Command       | Action                                                      |
|---------- |-------------------------------------------------------------|
| `make airport`  | Generates an executable for the main program 
| `make test`     | Generates an executable for the unit tests
| `./airport`     | Executes the main program 
| `./test`        | Executes unit tests

## Additional Notes

* If the user inputs an invalid airport ID, the program will prompt the user to enter a valid airport ID.
* We have ran our code with Valgrind and ensured that no memory leaks exist.
