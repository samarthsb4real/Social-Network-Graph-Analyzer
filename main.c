#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEOPLE 100
#define INF 99999  // Representing an infinite distance for unconnected nodes

typedef struct Node {
    int personID;
    struct Node* next;
} Node;

typedef struct Graph {
    int numPeople;
    char people[MAX_PEOPLE][50];
    Node* adjList[MAX_PEOPLE];
} Graph;

Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numPeople = 0;
    for (int i = 0; i < MAX_PEOPLE; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

int findPerson(Graph* graph, char* name) {
    for (int i = 0; i < graph->numPeople; i++) {
        if (strcmp(graph->people[i], name) == 0)
            return i;
    }
    return -1;
}

void addPerson(Graph* graph, char* name) {
    if (findPerson(graph, name) != -1) {
        printf("'%s' already exists in the network.\n", name);
        return;
    }
    strcpy(graph->people[graph->numPeople], name);
    graph->numPeople++;
    printf("Person '%s' added to the network.\n", name);
}

void addConnection(Graph* graph, char* person1, char* person2) {
    int p1 = findPerson(graph, person1);
    int p2 = findPerson(graph, person2);
    if (p1 == -1 || p2 == -1) {
        printf("Both people need to be in the network to add a connection.\n");
        return;
    }
    Node* newNode1 = (Node*)malloc(sizeof(Node));
    newNode1->personID = p2;
    newNode1->next = graph->adjList[p1];
    graph->adjList[p1] = newNode1;

    Node* newNode2 = (Node*)malloc(sizeof(Node));
    newNode2->personID = p1;
    newNode2->next = graph->adjList[p2];
    graph->adjList[p2] = newNode2;

    printf("Connection added between '%s' and '%s'.\n", person1, person2);
}

void findShortestPath(Graph* graph, int start, int end) {
    int visited[MAX_PEOPLE] = {0};
    int distance[MAX_PEOPLE];
    int queue[MAX_PEOPLE];
    int front = 0, rear = 0;
    int prev[MAX_PEOPLE];

    for (int i = 0; i < MAX_PEOPLE; i++) {
        distance[i] = INF;
        prev[i] = -1;
    }

    queue[rear++] = start;
    distance[start] = 0;
    visited[start] = 1;

    while (front < rear) {
        int curr = queue[front++];
        Node* temp = graph->adjList[curr];

        while (temp) {
            int neighbor = temp->personID;
            if (!visited[neighbor]) {
                queue[rear++] = neighbor;
                visited[neighbor] = 1;
                distance[neighbor] = distance[curr] + 1;
                prev[neighbor] = curr;
            }
            temp = temp->next;
        }
    }

    if (distance[end] == INF) {
        printf("No path found between %s and %s.\n", graph->people[start], graph->people[end]);
    } else {
        printf("Shortest path between %s and %s: ", graph->people[start], graph->people[end]);
        int path[MAX_PEOPLE], path_length = 0;
        for (int at = end; at != -1; at = prev[at]) {
            path[path_length++] = at;
        }
        for (int i = path_length - 1; i >= 0; i--) {
            printf("%s", graph->people[path[i]]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }
}

void findMostInfluentialPerson(Graph* graph) {
    int maxConnections = 0;
    char* influentialPerson = NULL;

    for (int i = 0; i < graph->numPeople; i++) {
        int connections = 0;
        Node* temp = graph->adjList[i];
        while (temp) {
            connections++;
            temp = temp->next;
        }
        if (connections > maxConnections) {
            maxConnections = connections;
            influentialPerson = graph->people[i];
        }
    }

    if (influentialPerson != NULL) {
        printf("The most influential person is '%s' with %d connections.\n", influentialPerson, maxConnections);
    } else {
        printf("The network is empty.\n");
    }
}

void findClusters(Graph* graph) {
    int visited[MAX_PEOPLE] = {0};
    int clusterCount = 0;

    void DFS(int personID) {
        visited[personID] = 1;
        Node* temp = graph->adjList[personID];
        while (temp) {
            if (!visited[temp->personID]) {
                DFS(temp->personID);
            }
            temp = temp->next;
        }
    }

    printf("Clusters of connected people:\n");
    for (int i = 0; i < graph->numPeople; i++) {
        if (!visited[i]) {
            clusterCount++;
            printf("Cluster %d: ", clusterCount);
            DFS(i);
            for (int j = 0; j < graph->numPeople; j++) {
                if (visited[j]) printf("%s ", graph->people[j]);
            }
            printf("\n");
        }
    }
}

void displayMenu() {
    printf("\n--- Social Network Graph Analyzer ---\n");
    printf("1. Add a person\n");
    printf("2. Add a connection\n");
    printf("3. Find shortest path\n");
    printf("4. Find most influential person\n");
    printf("5. Find clusters\n");
    printf("6. Exit\n");
}

int main() {
    Graph* graph = createGraph();
    int choice;
    char person1[50], person2[50];

    while (1) {
        displayMenu();
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the person's name: ");
                scanf("%s", person1);
                addPerson(graph, person1);
                break;
            case 2:
                printf("Enter the first person: ");
                scanf("%s", person1);
                printf("Enter the second person: ");
                scanf("%s", person2);
                addConnection(graph, person1, person2);
                break;
            case 3:
                printf("Enter the start person: ");
                scanf("%s", person1);
                printf("Enter the end person: ");
                scanf("%s", person2);
                int start = findPerson(graph, person1);
                int end = findPerson(graph, person2);
                if (start != -1 && end != -1) {
                    findShortestPath(graph, start, end);
                } else {
                    printf("One or both people are not in the network.\n");
                }
                break;
            case 4:
                findMostInfluentialPerson(graph);
                break;
            case 5:
                findClusters(graph);
                break;
            case 6:
                printf("Exiting the Social Network Graph Analyzer.\n");
                free(graph);
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}
