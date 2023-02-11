# Sleeping Barber Problem in Process Synchronization

*Assignment-2 for the course EC60012*

## Problem Statement

Imagine a hypothetical barbershop with one barber, one barber chair, and a 
waiting room with n chairs (n may be 0) for waiting customers. The following 
rules apply:

- If there are no customers, the barber falls asleep in the chair
- A customer must wake the barber if he is asleep
- If a customer arrives while the barber is working, the customer leaves if all chairs are occupied and sits in an empty chair if it's available
- When the barber finishes a haircut, he inspects the waiting room to see if there are any waiting customers and falls asleep if there are none

## How to run

To compile and run the source code, make sure you are using a *NIX system.

- Compiling
    ```shell
    $ make
    ```

- Executing
    ```shell
    $ ./barber_shop
    ```

- Cleaning
    ```shell
    $ make clean
    ```