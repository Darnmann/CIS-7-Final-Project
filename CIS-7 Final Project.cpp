#include <iostream>
#include <algorithm>	//std::next_permutation
#include <vector>		//std::vector

void displayMenu();
void addEdge(int a, int b, int w);
void displayGraph();
void displayAdjacencyList();
void displayPossibleRoutes();
std::vector<int> createTripVector(int startingCity);
void displayShortestRoute();
int calculateTripLength(int arr[4]);

int graph[4][4];	//2D array to act as adjacency matrix

int main()
{
	addEdge(0, 1, 24);
	addEdge(0, 2, 16);
	addEdge(0, 3, 33);
	addEdge(1, 0, 24);
	addEdge(1, 2, 18);
	addEdge(1, 3, 30);		//Adding the weighted edges to the adjacency matrix
	addEdge(2, 0, 16);
	addEdge(2, 1, 18);
	addEdge(2, 3, 26);
	addEdge(3, 0, 33);
	addEdge(3, 1, 30);
	addEdge(3, 2, 26);	

	int choice;
	do		//do-while loop that displays the menu of choices again after every selection
	{
		displayMenu();
		std::cin >> choice;
		switch (choice)		//Switch statement that determines which function is called based on which option the user chose
		{
		case 1:	//Case 1 displays possible routes starting from each city
			displayPossibleRoutes();
			break;
		case 2:
			displayShortestRoute();
			break;
		case 3: //Case 3 displays an adjacency list of the cities and roads
			displayAdjacencyList();
			break;
		case 4:	//Case 4 displays the adjacency matrix
			displayGraph();
			break;
		case 5:	//Case 5 quits the program
			std::cout << "\n\nThanks for trying out the program!\n\n";
			return 0;
		}
	} while (true);
}

void displayMenu()
{
	std::cout << "Choose from one of the options below\n1) Show possible routes\n2) Show shortest round trips\n3) Show the roads of each city\n4) Show map\n5) Exit\n";
}

void addEdge(int a, int b, int w)
{
	graph[a][b] = w;	//a is the first vertex, b is the second vertex, and w is the weight of the road/edge between them
}

void displayPossibleRoutes()
{	
	std::vector<int> vec;	//Vector to take the value of the vector from the createTripVector function
	int trip[4];	//Array that will copy the values of the above vector in order to make use of the std::next_permutation function
	std::cout << "\n0 = Riverside, 1 = Perris, 2 = Moreno Valley, 3 = Hemet\n";
	for (int i = 0; i < 4; i++)	//Outer for-loop
	{
		vec = createTripVector(i);	//Assign newly created vector to vec
		for (int i = 0; i < 4; i++)	//Copy values from vec to the trip array
			trip[i] = vec[i];
		std::cout << "Possible routes from "<<i<<": \n";	//Inner for-loop
		for (int i = 0; i < 5; i++)
		{
			std::next_permutation(trip, trip + 4);	//Permute the trip array and display every new permutation that includes the current starting city as its first element
			std::cout << trip[0] << " -> " << trip[1] << " -> " << trip[2] << " -> " << trip[3] << '\n';
		}
		vec.clear();
	}
	std::cout << std::endl;
}

void displayShortestRoute()	//Function to calculate and display the shortest trip through all the other cities from each starting city. Works just like the above function but has a different output
{
	std::vector<int> vec;	//Vector to take the value of the vector from the createTripVector function
	int trip[4];	//Array that will copy the values of the above vector in order to make use of the std::next_permutation function
	std::cout << "\n0 = Riverside, 1 = Perris, 2 = Moreno Valley, 3 = Hemet\n";
	std::cout << "Shortest routes through the cities starting from each one: \n";

	int shortestTripLength;
	int shortestTrip[4];

	for (int i = 0; i < 4; i++)
	{
		vec = createTripVector(i);	//Assign newly created vector to vec
		for (int i = 0; i < 4; i++)	//Copy values from vec to the trip array
			trip[i] = vec[i];

		shortestTripLength = calculateTripLength(trip);
		for (int i = 0; i < 4; i++)		//Assigning the vertices from the current shortest trip to an array to be displayed after all permutations are checked
			shortestTrip[i] = trip[i];

		for (int i = 0; i < 5; i++)
		{
			std::next_permutation(trip, trip + 4);	//Permute the trip array to get new trip combinations
			int temp = calculateTripLength(trip);
			if (temp < shortestTripLength)	//If this route from the current starting city beats the previous route, than update the shortest variables with the new current best
			{
				shortestTripLength = temp;
				for (int i = 0; i < 4; i++)	
					shortestTrip[i] = trip[i];
			}
		}
		vec.clear();
		std::cout << i << " = " << shortestTrip[0] << " -> " << shortestTrip[1] << " -> " << shortestTrip[2] << " -> " << shortestTrip[3] << " ... ";
		std::cout << "Total miles: " << shortestTripLength << '\n';
	}

	std::cout << std::endl;
}

int calculateTripLength(int arr[4])	//Function to calculate the total weight of a trip through the 4 cities
{
	int tripLength = 0;
	tripLength += graph[arr[0]][arr[1]];
	tripLength += graph[arr[1]][arr[2]];
	tripLength += graph[arr[2]][arr[3]];
	return tripLength;
}

std::vector<int> createTripVector(int startingCity)	//Function to return a vector of a city and all the cities it is connected to by road
{
	std::vector<int> trip = { startingCity };

	int count = 1;
	for (int i = 0; i < 4; i++)
	{
		if (graph[startingCity][i] != 0)
		{
			trip.push_back(i);
			count++;
		}
	}

	return trip;
}

void displayAdjacencyList()	//This function works like the below function but with a slightly modified output to the console
{
	std::cout << "\n0 = Riverside, 1 = Perris, 2 = Moreno Valley, 3 = Hemet\n";
	std::cout << "Below shows which other cities each city is connected to by a road\n";
	for (int i = 0; i < 4; i++)
	{			
		std::cout << i;
		for (int j = 0; j < 4; j++)
		{
			if (graph[i][j] != 0)
			{
				std::cout << " -> " << j;
			}
		}
		std::cout << '/'<<std::endl;
	}
	std::cout << '\n';
}

void displayGraph()
{
	std::cout << "\n0 = Riverside, 1 = Perris, 2 = Moreno Valley, 3 = Hemet\n";
	for (int i = 0; i < 4; i++)	//for-loop that goes through each vertex and displays its connections and the miles in between them
	{
		for (int j = 0; j < 4; j++)
		{
			if (graph[i][j] != 0)
			{
				std::cout << '|'<<i << " -> " << j << " is " << graph[i][j] << " miles";
			}

		}			
		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;
}