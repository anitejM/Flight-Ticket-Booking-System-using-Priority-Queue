#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Structure for a flight
struct Flight {
char source[50];
char destination[50];
char name[50];
int age;
float price;
struct Flight *left, *right;
};
// Function to create a new flight
struct Flight *newFlight(char source[], char destination[], char name[], int age, float price) {
struct Flight *flight = (struct Flight *)malloc(sizeof(struct Flight));
strcpy(flight->source, source);
strcpy(flight->destination, destination);
strcpy(flight->name, name);
flight->age = age;
flight->price = price;
flight->left = flight->right = NULL;
return flight;
}
// Function to insert a flight into the priority queue
struct Flight *insert(struct Flight *root, char source[], char destination[], char name[], int age, float price) {
if (root == NULL) {
return newFlight(source, destination, name, age, price);
}
if (age < root->age) {
root->left = insert(root->left, source, destination, name, age, price);
} else {
root->right = insert(root->right, source, destination, name, age, price);
}
// Ensure the flight with the highest priority (lowest age) is at the root
if (root->left != NULL && root->left->age < root->age) {
struct Flight *temp = root->left;
root->left = temp->right;
temp->right = root;
return temp;
}
return root;
}
// Function to book a flight based on priority
struct Flight *bookFlight(struct Flight *root) {
if (root == NULL) {
printf("No flights available.\n");
return root;
}
printf("Flight booked from %s to %s for %s with age %d. Price:%.2f\n", root->source, root->destination, root->name, root->age, root->price);
// Update the priority queue after booking
return root->right;
}
// Function to display the flights in the priority queue (in-order traversal)
void displayFlights(struct Flight *root) {
if (root != NULL) {
displayFlights(root->left);
printf("From: %s, To: %s, Name: %s, Age: %d, Price: %.2f\n",
root->source, root->destination, root->name, root->age, root->price);
displayFlights(root->right);
}
}
// Main function
int main() {
struct Flight *root = NULL;
int option;
do {
printf("\nOptions:\n");
printf("1. Book a flight\n");
printf("2. Check booking\n");
printf("3. Exit\n");
printf("Enter your option: ");
scanf("%d", &option);
switch (option) {
case 1: {
// Taking input for booking a flight
char source[50], destination[50], name[50];
int age;
float price;
printf("Enter source: ");
scanf("%s", source);
printf("Enter destination: ");
scanf("%s", destination);
printf("Enter your name: ");
scanf("%s", name);
printf("Enter your age: ");
scanf("%d", &age);
printf("Enter the price: ");
scanf("%f", &price);
root = insert(root, source, destination, name, age, price);
break;
}
case 2: {
// Checking booking
printf("Booked Flights:\n");
root = bookFlight(root);
break;
}
case 3:
// Exiting the program
printf("Exiting the program.\n");
break;
default:
printf("Invalid option. Please try again.\n");
}
} while (option != 3);
return 0;
}
