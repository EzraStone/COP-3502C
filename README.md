# COP 3502C - Computer Science 1

In this comprehensive course on fundamental computer science concepts, I delved deeply into the world of data structures and algorithms, specifically within the context of the C programming language.

## Topics Covered

* Recursion
* Abstract data types
* Arrays
* Linked lists
* Stacks
* Queues
* Big O
* Binary trees
* Binary heaps
* Hash tables
* Sorting algorithms
* Search algorithms

## Projects

### Assigned Seating

- For this first assignment, I was asked to implement a program in C that efficiently manages seat reservations in a theater. The assignment requires dynamic memory allocation and manipulation of structs to handle various actions, including purchasing seats and looking up seat ownership. I was tasked with writing various different functions, including but not limited to creating, adding, and looking up orders. A large emphasis is placed on memory management, function implementation, and adherence to runtime requirements.

### Movie Ticketing Queue

- This programming assignment required me to simulate a movie ticketing system using queues implemented via linked lists. The system assigns customers to one of 12 queues based on their name and then distributes these queues among a given number of booths. Customers arrive with their name, number of tickets, and arrival time. Each booth processes customers in a first-come-first-serve manner, with processing time determined by the number of tickets purchased. I was tasked with designing a program that efficiently processes these customers, assigning them to booths, and outputing the checkout times for each customer at each booth. In the implementation I had to adhere to specific rules, including dynamic memory allocation, queue operations, and efficient processing.

### Where to Sit

- This programming assignment focuses on recursion and required me to write two related programs to determine seating arrangements for a group of people attending a movie. The first program calculates the total number of valid orderings of attendees that satisfy certain constraints, such as not sitting next to specific individuals. The second program finds the lexicographically first valid ordering of attendees based on alphabetical order. Input includes the number of attendees, who has popcorn, and pairs of people who can't sit next to each other. Both programs must use a permutation algorithm, memory allocation was not required, and the runtime should be O(n x n!), where n is the number of attendees.

### Projector

- This assignment tasked me with implementing a program that utilizes merge sort to solve a problem involving projection angles in a circular room. The story sets the stage in a movie theater where a projector is projecting a movie onto a circular wall. Groups of people standing in the room must be avoided by the projector's light to prevent harm. The program must determine the largest possible angle for projection without harming anyone and find all the pairs of groups closest to the edge of the projection for that angle. Key implementation requirements include dynamic memory allocation, sorting groups based on angles using merge sort, and proper comparison functions for sorting.

### Theater Loyalty Program

- In this assignment i was asked to implement a program that manages a theater's loyalty program using a binary search tree. The program handled various commands such as adding and subtracting loyalty points, deleting customers, searching for customers, and counting customers with names alphabetically before a given name. The final output includes sorting the customers by loyalty points and printing their names and points. Key implementation requirements include using a binary search tree, maintaining runtime efficiency, implementing comparison functions, and sorting the customer data using Quick Sort.

### Theater Inventory

- This assignment tasked me with implementing a program to manage a theater's inventory using separate chaining hashing. The program handled various commands including buying supplies from suppliers, selling items to customers, and updating the sale price of items. Input commands specify these actions, and the program must output corresponding messages for buy and sell commands, as well as calculate the total cash on hand and the total complexity of all operations. The implementation utilized a hash table with separate chaining hashing, ensuring O(1) time complexity for processing each command. 
