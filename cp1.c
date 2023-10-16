#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define V 5

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}
void printSolution(int dist[], int parent[], int dest, char* locations[]) {
    printf("Location\tDistance from Your City\n");
    for (int i = 0; i < V; i++) {
        printf("%s\t\t%d\n", locations[i], dist[i]);
    }
    
    printf("\nShortest Path from Your City to %s: ", locations[dest]);
    int current = dest;
    while (current != -1) {
        printf("%s", locations[current]);
        if (parent[current] != -1) {
            printf(" <- ");
        }
        current = parent[current];
    }
    printf("\n");
}
void dijkstra(int graph[V][V], int src, int dest, char* locations[]) {
    int dist[V]; // The output array to store the shortest distance from the source
    bool sptSet[V]; // sptSet[i] will be true if the vertex i is included in the shortest path tree
    int parent[V]; // Parent array to store the shortest path tree

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printSolution(dist, parent, dest, locations);
}

int main() {
    char* locations[V] = {
        "Location A",
        "Location B",
        "Location C",
        "Location D",
        "Location E"
    };

    int graph[V][V] = {
        {0, 1000, 0, 300, 100},
        {150, 0, 500, 400, 0},
        {0, 550, 600, 200, 110},
        {350, 0, 260, 0, 460},
        {1000, 0, 180, 160, 0}
    };

    int source, destination;

    printf("Enter Your City (0 to 4): ");
    scanf("%d", &source);
    printf("Enter the destination location (0 to 4): ");
    scanf("%d", &destination);

    if (source < 0 || source >= V || destination < 0 || destination >= V) {
        printf("Invalid source or destination location.\n");
        return 1;
    }

    dijkstra(graph, source, destination, locations);

    return 0;
}
