Project 3: Threads and Synchronization
Panos Argyrakis and Amanda Chan

Problem 1: Pirates and Ninjas 
Description: 
Pirates and ninjas cannot be seen together. The only time that they will see each other is if they are in the costuming department, which they share, at the same time. If any pirate is in the costuming department, it will be forced to fight any ninja that enters, and vice versa. Therefore, pirates and ninjas cannot use the same costuming department at the same time. However two pirates may use the costuming department at the same time, as may two ninjas. Neither side may deprive the other of the costuming department by always occupying the department, so we must preserve fairness. We have decided to use a semaphore to solve this synchronization problem.

How to Test:
1. make
2. ./part_1 [numCTeams] [numPirates] [numNinjas] [avgCTimeP] [avgCTimeN] [avgATimeP] [avgATimeN]


*****

Problem 2: Taming Massachusetts Drivers
Description:
