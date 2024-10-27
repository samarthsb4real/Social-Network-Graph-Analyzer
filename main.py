import networkx as nx
import matplotlib.pyplot as plt

class SocialNetworkGraphAnalyzer:
    def __init__(self):
        self.graph = nx.Graph()
    
    def add_person(self, name):
        if name in self.graph:
            print(f"'{name}' already exists in the network.")
        else:
            self.graph.add_node(name)
            print(f"Person '{name}' added to the network.")
    
    def remove_person(self, name):
        if name in self.graph:
            self.graph.remove_node(name)
            print(f"Person '{name}' removed from the network.")
        else:
            print(f"Person '{name}' not found in the network.")
    
    def add_connection(self, person1, person2):
        if person1 not in self.graph or person2 not in self.graph:
            print("Both people need to be in the network to add a connection.")
        else:
            self.graph.add_edge(person1, person2)
            print(f"Connection added between '{person1}' and '{person2}'.")
    
    def remove_connection(self, person1, person2):
        if self.graph.has_edge(person1, person2):
            self.graph.remove_edge(person1, person2)
            print(f"Connection removed between '{person1}' and '{person2}'.")
        else:
            print(f"No connection found between '{person1}' and '{person2}'.")
    
    def find_shortest_path(self, person1, person2):
        try:
            path = nx.shortest_path(self.graph, source=person1, target=person2)
            print(f"Shortest path between '{person1}' and '{person2}': {path}")
        except nx.NetworkXNoPath:
            print(f"No path found between '{person1}' and '{person2}'.")
        except nx.NodeNotFound as e:
            print(e)
    
    def most_influential_person(self):
        if len(self.graph) == 0:
            print("The network is empty.")
            return None
        degree_dict = dict(self.graph.degree())
        most_influential = max(degree_dict, key=degree_dict.get)
        print(f"The most influential person is '{most_influential}' with {degree_dict[most_influential]} connections.")
    
    def find_clusters(self):
        clusters = list(nx.connected_components(self.graph))
        print("Clusters of connected people:")
        for i, cluster in enumerate(clusters, 1):
            print(f"Cluster {i}: {cluster}")
    
    def visualize_network(self):
        plt.figure(figsize=(10, 7))
        nx.draw(self.graph, with_labels=True, node_color='skyblue', node_size=2000, edge_color='gray', font_size=10, font_weight='bold')
        plt.title("Social Network Graph")
        plt.show()

    def display_menu(self):
        print("\n--- Social Network Graph Analyzer ---")
        print("1. Add a person")
        print("2. Remove a person")
        print("3. Add a connection")
        print("4. Remove a connection")
        print("5. Find shortest path between two people")
        print("6. Find the most influential person")
        print("7. Find clusters of connected people")
        print("8. Visualize network")
        print("9. Exit")

    def run(self):
        while True:
            self.display_menu()
            choice = input("Choose an option: ")

            if choice == '1':
                name = input("Enter the person's name: ")
                self.add_person(name)
            elif choice == '2':
                name = input("Enter the person's name to remove: ")
                self.remove_person(name)
            elif choice == '3':
                person1 = input("Enter the first person: ")
                person2 = input("Enter the second person: ")
                self.add_connection(person1, person2)
            elif choice == '4':
                person1 = input("Enter the first person: ")
                person2 = input("Enter the second person: ")
                self.remove_connection(person1, person2)
            elif choice == '5':
                person1 = input("Enter the start person: ")
                person2 = input("Enter the end person: ")
                self.find_shortest_path(person1, person2)
            elif choice == '6':
                self.most_influential_person()
            elif choice == '7':
                self.find_clusters()
            elif choice == '8':
                self.visualize_network()
            elif choice == '9':
                print("Exiting the Social Network Graph Analyzer.")
                break
            else:
                print("Invalid choice, please try again.")

# Run the interactive program
if __name__ == "__main__":
    analyzer = SocialNetworkGraphAnalyzer()
    analyzer.run()
