# 🍝 Philosophers

## Problem Description

The dining philosophers problem is a classic synchronization problem in which multiple philosophers sit around a table with a bowl of spaghetti. Between each pair of philosophers, there is a fork. Philosophers can eat, sleep or think. To eat, a philosopher must acquire two forks, one from each side. After eating, forks are put back on the table for other philosophers to use.

## Project Objectives

The objective of the Philosophers project is to simulate this problem using the following technologies:

- Threads to represent each philosopher
- Mutexes for synchronizing access to resources (forks)

## 🛠️ Installation Instructions

1. Clone the repository using the command:

        git clone https://github.com/redarling/Philosophers-42.git

2. Navigate to the project directory:

        cd Philosophers-42/philo

3. To build the project, execute the following command:

        make

After successful compilation, you can run the simulation by providing the necessary command-line parameters

## Example command:

    ./philo 5 800 200 200

## Where:

    5 — number of philosophers
    800 — time to die in milliseconds
    200 — time to eat in milliseconds
    200 — time to sleep in milliseconds

## 📝 Author
- [asyvash](https://github.com/redarling)



