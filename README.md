# Social Network Graph Analyzer

This **Social Network Graph Analyzer** project is a Python-based program designed to create, analyze, and visualize social networks. It uses **NetworkX** for graph operations and **Matplotlib** for network visualization, offering a variety of features for managing and exploring social network data.

## Features

1. **Add/Remove People**: Add individuals (nodes) to the network and remove them when needed.
2. **Add/Remove Connections**: Create or delete connections (edges) between individuals to represent relationships.
3. **Find Shortest Path**: Calculate the shortest path between two people in the network.
4. **Most Influential Person**: Identify the person with the most connections, making them the most influential.
5. **Cluster Analysis**: Detect clusters of connected people within the network.
6. **Network Visualization**: Generate a visual graph to better understand the social network structure.
7. **Interactive Menu**: A user-friendly, interactive menu to guide the user through different options.

## Technology Stack

- **Python**: Programming language used for implementing the graph analyzer.
- **NetworkX**: Library for the creation, manipulation, and study of complex networks.
- **Matplotlib**: Library for data visualization, specifically used for rendering the social network graph.

## Prerequisites

Before running the **Social Network Graph Analyzer**, make sure to have the following prerequisites in place:

1. **Python 3.7+**:  
   Ensure Python is installed on your system. You can download it from [python.org](https://www.python.org/downloads/).
   - To check if Python is installed and to verify the version, use:
     ```bash
     python --version
     ```

2. **Package Dependencies**:  
   The project uses two main libraries, **NetworkX** and **Matplotlib**:
   
   - **NetworkX**: Used for graph creation, manipulation, and analysis.
   - **Matplotlib**: Used for visualizing the social network as a graph.

   Install these dependencies with the following command:
   ```bash
   pip install networkx matplotlib
