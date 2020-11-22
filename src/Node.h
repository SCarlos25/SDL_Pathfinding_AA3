#pragma once


struct Node {
private:
	Vector2D pos;
	int type;	//Tipo de casilla
	float weight;	//Para la heuristica
	float cost;	//Para la distance

public:
	Node(){}
	Node(const Node &n) : pos(n.pos), type(n.type), weight(n.weight), cost(n.cost) {}
	Node(int _type, Vector2D _pos) {
		type = _type;
		pos = _pos;
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
			cost = 0.5f;
			break;

		case 3:
			weight = 3;
			cost = 3;
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

	bool friend operator==(Node n1, Node n2) {

		return n1.GetPos() == n2.GetPos() && n1.GetType() == n2.GetType();
	}
	bool friend operator!=(Node n1, Node n2) {

		return !(n1.GetPos() == n2.GetPos() && n1.GetType() == n2.GetType());
	}

};