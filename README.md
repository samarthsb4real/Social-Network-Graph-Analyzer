# Social Network Graph Analyzer

Welcome to the **Social Network Graph Analyzer**! This project allows you to analyze and interact with a social network represented as a graph. You can add people, create connections, find clusters, and analyze relationships within this network.

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Requirements](#requirements)
- [Setup](#setup)
- [How to Use](#how-to-use)

---

## Project Overview
The Social Network Graph Analyzer simulates a social network where individuals (nodes) and their connections (edges) form a graph. This project helps identify influential people, clusters, and connections in the network, and is designed for beginners to understand basic concepts of graph theory and algorithms like **Depth-First Search (DFS)** and **Breadth-First Search (BFS)**.

## Features
- **Add People**: Add individuals to the network.
- **Create Connections**: Connect people within the network.
- **Find Shortest Path**: Discover the shortest path between two individuals using BFS.
- **Identify Influential Person**: Identify the person with the most connections.
- **Cluster Detection**: Find clusters of connected individuals using DFS.
- **Delete People and Connections**: Manage the network by removing people or their connections.

## Requirements
- **C Compiler**: A C compiler such as `gcc` is required to compile and run the code.
- **Terminal**: Access to a terminal or command prompt to execute the program.
- **Python**: Programming language used for implementing the graph analyzer.
- **NetworkX**: Library for the creation, manipulation, and study of complex networks.
- **matplotlib**: Library for data visualization, specifically used for rendering the social network graph.

## Setup
1. **Clone the Repository**:
    ```bash
    git clone https://github.com/samarthsb4real/social-network-graph-analyser.git
    ```
2. **Navigate to Project Directory**:
    ```bash
    cd SocialNetworkGraphAnalyzer
    ```
3. **Compile the Program**:
    ```bash
    gcc social_network_graph_analyzer.c -o social_network_graph_analyzer
    ```
4. **Run the Program**:
    ```bash
    ./social_network_graph_analyzer
    ```
### For Python
1. **Package Dependencies**:  

   The project uses two main libraries, **NetworkX** and **Matplotlib**:
   - **NetworkX**: Used for graph creation, manipulation, and analysis.
   - **Matplotlib**: Used for visualizing the social network as a graph.

   Install these dependencies with the following command:
   ```bash
   pip install networkx matplotlib
   
2. **Run the script**:

   Use the following command to run the script:
   ```bash
   python main.py
   ```

## How to Use
Once the program starts, you'll see a menu with several options. Here's a quick guide to each option:

1. **Add a person**: Type the name of the person you'd like to add to the network.
2. **Add a connection**: Connect two existing people in the network by entering their names.
3. **Find shortest path**: Specify two people to find the shortest path between them.
4. **Find the most influential person**: Discover who has the most connections.
5. **Find clusters**: Identify clusters (groups of connected individuals) in the network.
6. **Delete a person**: Remove a person and their connections from the network.
7. **Delete a connection**: Remove a connection between two people.
8. **Exit**: Quit the program.

**Example Usage**:
```plaintext

--- Social Network Graph Analyzer ---
1. Add a person
2. Add a connection
3. Find shortest path
4. Find the most influential person
5. Find clusters
6. Delete Person
7. Delete Connection
8. Exit
Choose an option: 
