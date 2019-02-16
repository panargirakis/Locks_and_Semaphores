Project 3: Threads and Synchronization
Panos Argyrakis and Amanda Chan

Problem 1: Pirates and Ninjas 
Description: 
Pirates and ninjas cannot be seen together. The only time that they will see each other is if they are in the costuming department, which they share, at the same time. If any pirate is in the costuming department, it will be forced to fight any ninja that enters, and vice versa. Therefore, pirates and ninjas cannot use the same costuming department at the same time. However two pirates may use the costuming department at the same time, as may two ninjas. Neither side may deprive the other of the costuming department by always occupying the department, so we must preserve fairness. We have decided to use a semaphore to solve this synchronization problem.

How to Test:
1. make
2. ./part_1 [numCTeams] [numPirates] [numNinjas] [avgCTimeP] [avgCTimeN] [avgATimeP] [avgATimeN]

Note: We have created a special makefile that has test cases we have written for this solution. The first test has all of the correct arguments. The second test should not work because it has incorrect arguments. The third test should work and has different arguments than the first one.


*****

Problem 2: Taming Massachusetts Drivers
Description:
When using the intersection, a driver will use 1-3 quadrants, based on the type of use. For example, if a car approaches from the North, depending on where it is going, it proceeds through the intersection as follows:

Right: NW quadrant only
Straight: NW, then SW quadrant
Left: NW, then SW, then SE quadrants

No two cars be in the same portion of the intersection at the same time. Each direction has a single lane of traffic and vehicles cannot pass each other in the intersection or in the line approaching the intersection. If two cars both approach from the same direction, the first car to reach the intersection should be the first to go. Additionally, the solution should not starve traffic from any other direction. Lastly, if cars from multiple directions may safely use the intersection at the same time, they should do so. We decided to use mutexes/condition variables to solve this synchronization problem.

How to Test:
1. make
2. ./part_2
