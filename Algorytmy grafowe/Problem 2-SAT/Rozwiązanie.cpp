#include<cstdio>
#include<vector>

using namespace std;


void input(int vertices, int connections, int offset, vector<vector<int> > &Graph, vector<vector<int> > &InvertedGraph)
{
	Graph.resize(vertices);
	InvertedGraph.resize(vertices);
	for (int i = 0; i < connections; i++)
	{
		char sign_1, sign_2;
		int temp_1, temp_2;
		scanf(" %c%d %c%d", &sign_1, &temp_1, &sign_2, &temp_2);
		temp_1--; temp_2--;
		if (sign_1=='-'&& sign_2=='-')
		{
			Graph[temp_1+offset].push_back(temp_2);
			Graph[temp_2 + offset].push_back(temp_1);
			InvertedGraph[temp_2].push_back(temp_1 + offset);
			InvertedGraph[temp_1].push_back(temp_2 + offset);
			

		}
		else if(sign_1=='-'&&sign_2=='+')
		{
			Graph[temp_1 + offset].push_back(temp_2+offset);
			Graph[temp_2].push_back(temp_1);
			InvertedGraph[temp_2+offset].push_back(temp_1 + offset);
			InvertedGraph[temp_1].push_back(temp_2);
		}
		else if(sign_1=='+'&&sign_2=='-')
		{
			Graph[temp_1].push_back(temp_2);
			Graph[temp_2 + offset].push_back(temp_1+offset);
			InvertedGraph[temp_2].push_back(temp_1);
			InvertedGraph[temp_1+offset].push_back(temp_2 + offset);
		}
		else
		{
			Graph[temp_1].push_back(temp_2+offset);
			Graph[temp_2].push_back(temp_1+offset);
			InvertedGraph[temp_2+offset].push_back(temp_1);
			InvertedGraph[temp_1+offset].push_back(temp_2);
		}
	}
}

void DfsOrdering(int x,vector<vector<int> > &Connections, vector<bool> &Checked, vector<int> &Order)
{
	Checked[x] = true;
	for (int i = 0; i<Connections[x].size(); i++)
	{
		if (Checked[Connections[x][i]] == false)
			DfsOrdering(Connections[x][i], Connections, Checked, Order);
	}
	Order.push_back(x);
}

void TopologicalOrder(int amount, vector<vector<int> > &Connections, vector<bool> &Checked, vector<int> &Order)
{
	for (int i = 0; i < amount; i++)
	{
		if (Checked[i] == false)
			DfsOrdering(i, Connections, Checked, Order);
	}
}

void DfsScc(int x, int scccounter,  vector<vector<int> > &Connections, vector<bool> &Checked, vector<int> &SCC)
{
	Checked[x] = false;
	SCC[x]=scccounter;
	for (int i = 0; i<Connections[x].size(); i++)
	{
		if (Checked[Connections[x][i]] == true)
			DfsScc(Connections[x][i], scccounter, Connections, Checked, SCC);
	}
}

void SccCalculation(int amount, vector<vector<int> > &Connections, vector<bool> &Checked, vector<int> &Order,vector<int> &SCC,vector<int> &SCCcounter)
{
	int scccounter = 0;
	for (int i = amount-1; i >= 0; i--)
	{
		
		if (Checked[Order[i]] == true)
		{
			DfsScc(Order[i], scccounter, Connections, Checked, SCC);
			SCCcounter.push_back(Order[i]);
			scccounter++;
			//printf("X");
		}
	}
}

bool SccCheck(int amount, vector<int> &SCC)
{
	for (int i = 0; i < amount; i++)
	{
		//printf("%d %d\n", SCC[i], SCC[i + amount]);
		if (SCC[i] == SCC[i + amount])
		{
			return true;
		}
			
	}
	return false;
}

void SatSolving(int amount, vector<int> &SCC, vector<int> &Value, vector<int> &SCCcounter)
{
	if (SccCheck(amount,SCC))
	{
		printf("NIE\n");
		return;
	}
	for (int i = Value.size()-1;i>=0; i--)
	{
		if (Value[i] == -1)
		{
			Value[i] = 1;
			if (SCCcounter[i] < amount)
			{
				if(Value[SCC[SCCcounter[i]+amount]]==-1)
					Value[SCC[SCCcounter[i]]] = 0;
			}
			else
			{
				if (Value[SCC[SCCcounter[i] - amount]] == -1)
					Value[SCC[SCCcounter[i]]] = 0;
			}
			
		}
	}
	printf("TAK\n");

	for (int i = 0; i < amount; i++)
	{
		printf("%d ", Value[SCC[i]]);
	}
	printf("\n");
}

int main()
{
	int AGH; scanf("%d", &AGH);
	while (AGH--)
	{
		int vertices=0, connections=0,offset=0;
		scanf("%d %d", &offset, &connections);
		vertices = 2 * offset;
		vector<vector<int> > Graph;
		vector<vector<int> > InvertedGraph;
		input(vertices,connections,offset,Graph,InvertedGraph);
		vector<bool> Check(vertices, false);
		vector<int> Order;
		TopologicalOrder(vertices, Graph, Check, Order); 
		//for (int i = 0; i < Order.size(); i++)
			//printf("%d ", Order[i]);
		vector<int> SCC(vertices, 0);
		vector<int> SCCcounter;
		SccCalculation(vertices, InvertedGraph, Check, Order, SCC,SCCcounter);
		vector<int> Value(SCCcounter.size(), -1);
		SatSolving(offset, SCC, Value, SCCcounter);
	}
	
}
