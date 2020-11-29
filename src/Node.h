#pragma once


struct Node {
private:
	//ID global del nodo
	static int CNumber;
	int ID;
	float weight;	//Para la heuristica
	float cost;	//Para la distance
	Node *originNode;

public:
	Vector2D pos;
	int type;	//Tipo de casilla
	
	Node(){
		pos = Vector2D(NULL, NULL);
		type = weight = cost = NULL;
	}
	Node(const Node &n) : pos(n.pos), type(n.type), weight(n.weight), cost(n.cost) {
		originNode = new Node();
	}
	Node(int _type, Vector2D _pos) {
		type = _type;
		pos = _pos;
		originNode = new Node();
		switch (type)
		{
		case 0:
			weight = 9001;
			cost = 9001;
			break;

		case 1:
			weight = 1;
			cost = 1;
			break;

		case 2:
			weight = 0.5f;
			cost = 0.1f;
			break;

		case 3:
			weight = 3;
			cost = 10;
			break;

		default:
			break;
		}

	}

	const Vector2D GetPos() {
		return pos;
	}

	const int GetType()
	{
		return type;
	}

	const float GetWeight()
	{
		return weight;
	}

	const float GetCost()
	{
		return cost;
	}

	const Node GetOriginNode() {
		return *originNode;
	}

	void SetOriginNode(Node newNode) {
		*originNode = newNode;
	}

	bool operator==(const Node &other) const
	{
		return (pos.x == other.pos.x && pos.y == other.pos.y
			&& type == other.type);
	}

	/*
	bool friend operator==(Node n1, Node n2) {

		return n1.GetPos() == n2.GetPos() && n1.GetType() == n2.GetType();
	}
	*/
	bool friend operator!=(Node n1, Node n2) {

		return !(n1.GetPos() == n2.GetPos() && n1.GetType() == n2.GetType());
	}

};

namespace std {

	template <>
	struct hash<Node>
	{
		std::size_t operator()(const Node& k) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((hash<int>()(k.pos.x)
				^ (hash<int>()(k.pos.y) << 1)) >> 1)
				^ (hash<int>()(k.type) << 1);
		}
	};

}