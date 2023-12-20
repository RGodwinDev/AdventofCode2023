#pragma once
class D17Vertex
{
private:

	//the calculated distance from the start_vertex
	int distance;
	//A reference to the vertex that occurs immediately before the vertex, on a path from some start_vertex to the vertex
	D17Vertex* predVertex;
public:
	D17Vertex(char label);

	void setPred(D17Vertex pred);
	void setDist(int x);

};

