#include <stdio.h>
#include <iostream> 
using namespace std;

// a node of a doubly linked list.
class Node
{
public:
	int val; // Value of the node
	Node* next; // Pointer to the next node
	Node* prev; // Pointer to the previous node
};

/* A helper function to swap elements. */
void swapNodes(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

// A helper function to find the last node of the linked list.
Node* getLastNode(Node* head) {
	// If the list is empty, return NULL
	if (head == NULL) {
		return NULL;
	}

	// Start from the head
	Node* current = head;

	// Traverse the list until the last node is reached
	while (current->next != NULL) {
		current = current->next;
	}

	return current;
}

// Consider the last element as pivot.
Node* partition(Node* start, Node* end) // Function to partition a linked list around a pivot element
{
	// set pivot as end element.
	int pivot = end->val;


	Node* i = start->prev; // Initialize a pointer i to the previous of the start node, similar to array of i = start -1

	for (Node* temp = start; temp != end; temp = temp->next)
	{
		if (temp->val <= pivot)
		{
			if (i == NULL)
				i = start;
			else
				i = i->next;

			swapNodes(&(i->val), &(temp->val));
		}
	}

	if (i == NULL)
		i = start;
	else
		i = i->next;

	swapNodes(&(i->val), &(end->val));

	return i; // Return the new position of the pivot
}

// Implementation of quicksort.
void quickSort(Node* start, Node* end)
{
	// Base case: Check if end is not NULL and start and end are different nodes.
	// This ensures that the partition has more than one element.
	if (end != NULL && start != end && start != end->next)
	{
		// Partition the current segment and get the pivot element.
		Node* pivot = partition(start, end);

		// Recursively sort the left partition (elements less than the pivot).
		quickSort(start, pivot->prev);

		// Recursively sort the right partition (elements greater than the pivot).
		quickSort(pivot->next, end);
	}
	// If any of the base case conditions is not met, the segment is already sorted or cannot be partitioned further.
	// No further sorting is required for this segment.
}

void sortLinkedList(Node* root) // Function to sort a linked list
{
	Node* end = getLastNode(root); // Get the last node of the list
	Node* head = root; // Set the head of the list

	quickSort(head, end); // Sort the linked list using quicksort
}

// A helper function to print contents of linked list.
void printLinkedList(Node* root) // Function to print the elements of a linked list
{
	while (root) // Traverse the list
	{
		cout << root->val << " "; // Print the value of the current node
		root = root->next; // Move to the next node
	}
	cout << endl; // Print a newline character
}

// Helper function to insert a node in the beginning. 
void insertAtBeginning(Node** head, int value)
// Node ** because it is pointer to a pointer
{
	Node* node = new Node; // Create a new node
	node->val = value; // Set the value of the new node to the given value

	node->prev = NULL; // Set the previous pointer of the new node to NULL
	node->next = (*head); // Set the next pointer of the new node to the current head of the list

	if ((*head) != NULL) // If the list is not empty
		(*head)->prev = node; // Set the previous pointer of the current head to the new node

	(*head) = node; // Set the head of the list to the new node
}

int main()
{
	Node* root = NULL; // Initialize the root of the linked list to NULL
	insertAtBeginning(&root, 10); // Insert nodes at the beginning of the list
	insertAtBeginning(&root, 17);
	insertAtBeginning(&root, 16);
	insertAtBeginning(&root, 15);
	insertAtBeginning(&root, 1100);
	insertAtBeginning(&root, 127);
	insertAtBeginning(&root, 1);
	insertAtBeginning(&root, 15);
	insertAtBeginning(&root, 18);

	cout << "Linked List before sorting \n";
	printLinkedList(root); // Print the elements of the linked list

	sortLinkedList(root); // Sort the linked list

	cout << "Linked List after sorting \n";
	printLinkedList(root); // Print the elements of the linked list
	return 0;
}
