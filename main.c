#include <stdio.h>     // Standard input-output library for printf, scanf, etc.
#include <stdlib.h>    // Standard library for dynamic memory allocation (malloc, free)
#include <string.h>    // String handling library for functions like strcpy, strcmp
#define MAX_PEOPLE 100 // Defining the maximum number of people in the network
#define INF 99999      // Defining INF as a large number to represent infinite distance for unconnected nodes

// Define a structure for a node in the adjacency list
typedef struct Node
{
    int personID;      // ID of the person this node represents
    struct Node *next; // Pointer to the next node in the adjacency list
} Node;

// Define a structure for the graph
typedef struct Graph
{
    int numPeople;               // Total number of people (or nodes) in the graph
    char people[MAX_PEOPLE][50]; // Array of names (or labels) for each person, up to 50 characters each
    Node *adjList[MAX_PEOPLE];   // Array of pointers representing the adjacency list for each person
} Graph;

// Function to create and initialize a new graph
Graph *createGraph()
{
    // Allocate memory for the graph structure
    Graph *graph = (Graph *)malloc(sizeof(Graph));

    // Initialize the number of people (nodes) in the graph to zero
    graph->numPeople = 0;

    // Initialize each adjacency list pointer to NULL, indicating no connections initially
    for (int i = 0; i < MAX_PEOPLE; i++)
    {
        graph->adjList[i] = NULL;
    }

    // Return the pointer to the newly created and initialized graph
    return graph;
}

// Function to find the index of a person in the graph by name
int findPerson(Graph *graph, char *name)
{
    // Loop through the list of people in the graph
    for (int i = 0; i < graph->numPeople; i++)
    {
        // Compare each name with the given name
        if (strcmp(graph->people[i], name) == 0)
            return i; // Return the index if a match is found
    }

    // Return -1 if the person is not found in the graph
    return -1;
}

// Function to add a new person to the graph
void addPerson(Graph *graph, char *name)
{
    // Check if the person already exists in the graph
    if (findPerson(graph, name) != -1)
    {
        // If found, print a message and return without adding
        printf("'%s' already exists in the network.\n", name);
        return;
    }

    // Copy the name into the people array at the current index
    strcpy(graph->people[graph->numPeople], name);

    // Increment the count of people in the graph
    graph->numPeople++;

    // Print a confirmation message
    printf("Person '%s' added to the network.\n", name);
}

// Function to delete a person from the graph
void deletePerson(Graph *graph, char *name)
{
    // Find the ID of the person to delete
    int personID = findPerson(graph, name);
    if (personID == -1)
    {
        // Print a message if the person is not found
        printf("'%s' is not in the network.\n", name);
        return;
    }

    // Remove all connections to this person from other people's adjacency lists
    for (int i = 0; i < graph->numPeople; i++)
    {
        if (i != personID)
        {
            // Call deleteConnection to remove connections for each person in the network
            deleteConnection(graph, graph->people[i], name);
        }
    }

    // Shift all people and their connections after personID to fill the gap left by deletion
    for (int i = personID; i < graph->numPeople - 1; i++)
    {
        // Copy the next person's name and adjacency list to the current position
        strcpy(graph->people[i], graph->people[i + 1]);
        graph->adjList[i] = graph->adjList[i + 1];
    }

    // Set the last adjacency list pointer to NULL and decrement the number of people
    graph->adjList[graph->numPeople - 1] = NULL;
    graph->numPeople--;

    // Print a confirmation message
    printf("Person '%s' deleted from the network.\n", name);
}

// Function to add a connection (edge) between two people in the graph
void addConnection(Graph *graph, char *person1, char *person2)
{
    // Find the IDs of the two people to connect
    int p1 = findPerson(graph, person1);
    int p2 = findPerson(graph, person2);

    // Check if both people exist in the network
    if (p1 == -1 || p2 == -1)
    {
        // Print a message if either person is not found
        printf("Both people need to be in the network to add a connection.\n");
        return;
    }

    // Create a new node for the adjacency list of person1 pointing to person2
    Node *newNode1 = (Node *)malloc(sizeof(Node));
    newNode1->personID = p2;
    newNode1->next = graph->adjList[p1];
    graph->adjList[p1] = newNode1;

    // Create a new node for the adjacency list of person2 pointing to person1 (for an undirected graph)
    Node *newNode2 = (Node *)malloc(sizeof(Node));
    newNode2->personID = p1;
    newNode2->next = graph->adjList[p2];
    graph->adjList[p2] = newNode2;

    // Print a confirmation message
    printf("Connection added between '%s' and '%s'.\n", person1, person2);
}

// Function to delete a connection (edge) between two people in the graph
void deleteConnection(Graph *graph, char *person1, char *person2)
{
    // Find the IDs of the two people
    int p1 = findPerson(graph, person1);
    int p2 = findPerson(graph, person2);

    // Check if both people exist in the network
    if (p1 == -1 || p2 == -1)
    {
        // Print a message if either person is not found
        printf("Both people need to be in the network to delete a connection.\n");
        return;
    }

    // Helper function to remove a connection from one person's adjacency list
    void removeConnection(int from, int to)
    {
        Node *current = graph->adjList[from];
        Node *prev = NULL;

        // Traverse the adjacency list to find the node representing the connection
        while (current)
        {
            if (current->personID == to)
            {
                // If found, remove the node by adjusting the pointers
                if (prev)
                {
                    prev->next = current->next;
                }
                else
                {
                    graph->adjList[from] = current->next;
                }
                free(current); // Free the removed node's memory
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    // Remove the connections in both directions for an undirected graph
    removeConnection(p1, p2);
    removeConnection(p2, p1);

    // Print a confirmation message
    printf("Connection deleted between '%s' and '%s'.\n", person1, person2);
}

// Function to find the shortest path between two people in the graph
void findShortestPath(Graph *graph, int start, int end)
{
    int visited[MAX_PEOPLE] = {0}; // Array to track visited nodes
    int distance[MAX_PEOPLE];      // Array to store distances from the start node
    int queue[MAX_PEOPLE];         // Queue for BFS traversal
    int front = 0, rear = 0;       // Queue front and rear pointers
    int prev[MAX_PEOPLE];          // Array to store the previous node in the shortest path

    // Initialize distances to infinity and previous nodes to -1
    for (int i = 0; i < MAX_PEOPLE; i++)
    {
        distance[i] = INF;
        prev[i] = -1;
    }

    // Start BFS from the starting node
    queue[rear++] = start;
    distance[start] = 0;
    visited[start] = 1;

    // Perform BFS to explore the shortest path
    while (front < rear)
    {
        int curr = queue[front++];
        Node *temp = graph->adjList[curr];

        // Explore neighbors of the current node
        while (temp)
        {
            int neighbor = temp->personID;
            if (!visited[neighbor])
            {
                // If not visited, add to queue and update distance and previous node
                queue[rear++] = neighbor;
                visited[neighbor] = 1;
                distance[neighbor] = distance[curr] + 1;
                prev[neighbor] = curr;
            }
            temp = temp->next;
        }
    }

    // If the end node is unreachable, print a message
    if (distance[end] == INF)
    {
        printf("No path found between %s and %s.\n", graph->people[start], graph->people[end]);
    }
    else
    {
        // Print the shortest path by backtracking through 'prev' array
        printf("Shortest path between %s and %s: ", graph->people[start], graph->people[end]);
        int path[MAX_PEOPLE], path_length = 0;

        // Build the path from end to start by following 'prev' pointers
        for (int at = end; at != -1; at = prev[at])
        {
            path[path_length++] = at;
        }

        // Print the path in the correct order
        for (int i = path_length - 1; i >= 0; i--)
        {
            printf("%s", graph->people[path[i]]);
            if (i > 0)
                printf(" -> ");
        }
        printf("\n");
    }
}
// Function to find the most influential person in the graph
void findMostInfluentialPerson(Graph *graph)
{
    int maxConnections = 0;         // Variable to store the highest number of connections found
    char *influentialPerson = NULL; // Pointer to store the name of the most influential person

    // Loop through each person in the graph
    for (int i = 0; i < graph->numPeople; i++)
    {
        int connections = 0;            // Counter to track the number of connections for the current person
        Node *temp = graph->adjList[i]; // Pointer to traverse the adjacency list of the current person

        // Traverse the adjacency list and count the connections
        while (temp)
        {
            connections++;
            temp = temp->next;
        }

        // Update the most influential person if the current person has more connections
        if (connections > maxConnections)
        {
            maxConnections = connections;
            influentialPerson = graph->people[i];
        }
    }

    // Print the most influential person or an appropriate message if the network is empty
    if (influentialPerson != NULL)
    {
        printf("The most influential person is '%s' with %d connections.\n", influentialPerson, maxConnections);
    }
    else
    {
        printf("The network is empty.\n");
    }
}

// Helper function for Depth-First Search (DFS) to find clusters in the graph
void DFS(Graph *graph, int personID, int visited[], int cluster[], int *clusterSize)
{
    // Mark the current person as visited
    visited[personID] = 1;

    // Add the current person to the current cluster and increment the cluster size
    cluster[(*clusterSize)++] = personID;

    // Traverse the adjacency list of the current person
    Node *temp = graph->adjList[personID];
    while (temp)
    {
        // If the adjacent person has not been visited, perform DFS on them
        if (!visited[temp->personID])
        {
            DFS(graph, temp->personID, visited, cluster, clusterSize);
        }
        temp = temp->next;
    }
}

// Function to find and print clusters of connected people in the graph
void findClusters(Graph *graph)
{
    int visited[MAX_PEOPLE] = {0}; // Array to track visited people; initialized to 0 (unvisited)
    int clusterCount = 0;          // Counter to keep track of the number of clusters

    printf("Clusters of connected people:\n");

    // Loop through each person in the graph to start DFS if they haven't been visited
    for (int i = 0; i < graph->numPeople; i++)
    {
        // If the person hasn't been visited, they are part of a new cluster
        if (!visited[i])
        {
            int cluster[MAX_PEOPLE]; // Array to store IDs of members in the current cluster
            int clusterSize = 0;     // Variable to track the size of the current cluster

            // Perform DFS starting from the current person to find all connected members
            DFS(graph, i, visited, cluster, &clusterSize);

            // Print the current cluster's members
            printf("Cluster %d: ", ++clusterCount);
            for (int j = 0; j < clusterSize; j++)
            {
                printf("%s ", graph->people[cluster[j]]);
            }
            printf("\n");
        }
    }

    // If no clusters are found, print a message indicating an empty network
    if (clusterCount == 0)
    {
        printf("No clusters found. The network may be empty.\n");
    }
}

void displayMenu()
{
    printf("\n--- Social Network Graph Analyzer ---\n");
    printf("1. Add a person\n");
    printf("2. Add a connection\n");
    printf("3. Find shortest path\n");
    printf("4. Find most influential person\n");
    printf("5. Find clusters\n");
    printf("6. Delete Person\n");
    printf("7. Delete Connection\n");
    printf("8. Exit\n");
}

int main()
{
    Graph *graph = createGraph();  // Create a new graph structure for the social network
    int choice;                    // Variable to store user’s menu choice
    char person1[50], person2[50]; // Variables to store names of people for input

    while (1) // Infinite loop to keep the menu running until the user chooses to exit
    {
        displayMenu(); // Display the menu options to the user
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // Add a person to the network
            printf("Enter the person's name: ");
            scanf("%s", person1);
            addPerson(graph, person1);
            break;

        case 2: // Add a connection between two people in the network
            printf("Enter the first person: ");
            scanf("%s", person1);
            printf("Enter the second person: ");
            scanf("%s", person2);
            addConnection(graph, person1, person2);
            break;

        case 3: // Find the shortest path between two people
            printf("Enter the start person: ");
            scanf("%s", person1);
            printf("Enter the end person: ");
            scanf("%s", person2);
            int start = findPerson(graph, person1); // Find ID of the start person
            int end = findPerson(graph, person2);   // Find ID of the end person
            if (start != -1 && end != -1)           // Check if both people exist in the network
            {
                findShortestPath(graph, start, end);
            }
            else
            {
                printf("One or both people are not in the network.\n");
            }
            break;

        case 4: // Find the most influential person (based on the number of connections)
            findMostInfluentialPerson(graph);
            break;

        case 5: // Find clusters of connected people in the network
            findClusters(graph);
            break;

        case 6: // Delete a person from the network
            printf("Enter the person's name to delete: ");
            scanf("%s", person1);
            deletePerson(graph, person1);
            break;

        case 7: // Delete a connection between two people in the network
            printf("Enter the first person: ");
            scanf("%s", person1);
            printf("Enter the second person: ");
            scanf("%s", person2);
            deleteConnection(graph, person1, person2);
            break;

        case 8: // Exit the program
            printf("Exiting the Social Network Graph Analyzer.\n");
            free(graph); // Free allocated memory for the graph
            return 0;

        default: // Handle invalid choices
            printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}