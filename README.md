# Plague simulation

## General info

This project is trying to simulate the development of plague in the city. It is a console application, with simple ASCII graphic and it contains about 650 lines of code. In the simulation, there is a lot of parameters to freely manipulate. For example you can choose city size, chances to get ill from people or from the contaminated well, time to hatch the disease, chances to establish quarantine, chances to get cured and many more.

The simulation is contained in the loop and it iterates through each cell. Software was built with polymorphism, that is why loop interation is regardless of whether it is a house or a well. The population of the city is exposed to sick individuals and contaminated wells. Then people can get sick and afterwards they can die or they have a chance to get cured. To make the simulation more realistic, houses with sick people can be closed in quarantine mode. Logs of the simulation can be written in the file.

![alt text](https://raw.githubusercontent.com/Haroth/Plague-simulation/blob/master/Screen/Plague.png)

## Technologies

Project is created with:
* C++ version: 14


## Setup
To run the simulation, compile three cpp files, and two headers. All files are in the main folder.


