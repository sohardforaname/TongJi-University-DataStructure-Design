#define _CRT_SECURE_NO_WARNINGS

#include "HashTable.hpp"
#include "Trie.hpp"
#include "String.h"
#include "Heap.hpp"
#include <cstdio>

struct Edge
{
	size_t w, to;
	Edge() {}
	Edge(const size_t& _w, const size_t& _to) :
		w(_w), to(_to) {}
	bool operator<(const Edge& e) const
	{
		return w > e.w;
	}
};
Vector<Vector<Edge>>G;
size_t edgeCount;
size_t nodeCount;

Vector<size_t> dis, pre;
Vector<bool> vis, exist;

Heap<Edge>q;

size_t dijkstra(const size_t& s, const size_t& t, Vector<int>& path)
{
	dis.Resize(G.GetSize());
	pre.Resize(G.GetSize());
	vis.Resize(G.GetSize());
	for (size_t i = 0; i < dis.GetSize(); ++i)
		dis[i] = INT_MAX;
	for (size_t i = 0; i < vis.GetSize(); ++i)
		vis[i] = 0;

	dis[s] = 0;
	q.Push(Edge(0, s));
	while (q.GetSize())
	{
		Edge e = q.GetTop();
		q.Pop();
		if (vis[e.to])
			continue;
		int u = e.to;
		vis[u] = 1;
		for (size_t i = 0; i < G[u].GetSize(); ++i)
		{
			int v = G[e.to][i].to, w = G[e.to][i].w;
			if (dis[v] > dis[u] + w)
			{
				dis[v] = dis[u] + w;
				pre[v] = u;
				q.Push(Edge(dis[v], v));
			}
		}
	}
	path.Resize(0);
	size_t cur = t;
	while (cur != s)
	{
		path.PushBack(cur);
		cur = pre[cur];
	}
	path.PushBack(cur);
	return dis[t];
}

Trie<char, String, int>mpStrToInt;
Vector<String> mpIntToStr;

void PrintPath(const Vector<int>& path)
{
	printf("path: \n");
	for (size_t i = path.GetSize() - 1; int(i) >= 0; --i)
		printf("%s%s", mpIntToStr[path[i]].GetCstr(), i ? " -> " : "\n");
}

bool LoadGraph(const char* filePath)
{
	char* buffer = new char[1 << 10];
	FILE* fp = fopen(filePath, "r");
	if (!fp)
		return printf("Can't load graph from: %s\n", filePath), false;
	fscanf(fp, "%u", &nodeCount);
	for (size_t i = 0; i < nodeCount; ++i)
	{
		fscanf(fp, "%s", buffer);
		mpStrToInt.Insert(String(buffer), i);
		mpIntToStr.PushBack(String(buffer));
	}
	exist.Resize(nodeCount);
	for (size_t i = 0; i < exist.GetSize(); ++i)
		exist[i] = true;;
	G.Resize(nodeCount);
	fscanf(fp, "%u", &edgeCount);
	for (size_t i = 0; i < edgeCount; ++i)
	{
		fscanf(fp, "%s", buffer);
		int u = *mpStrToInt.Find(String(buffer));
		fscanf(fp, "%s", buffer);
		int v = *mpStrToInt.Find(String(buffer));
		size_t w;
		fscanf(fp, "%u", &w);
		G[u].PushBack(Edge(w, v));
		//G[v].PushBack(Edge(w, u));
	}
	fclose(fp);
	delete[]buffer;
	return true;
}

void StoreGraph(const char* filePath)
{
	FILE* fp = fopen(filePath, "w");
	fprintf(fp, "%u\n", mpStrToInt.GetSize());
	for (size_t i = 0; i < mpIntToStr.GetSize(); ++i)
		if (exist[i])
			fprintf(fp, "%s\n", mpIntToStr[i].GetCstr());
	fprintf(fp, "%u\n", edgeCount);
	for (size_t i = 0; i < G.GetSize(); ++i)
		for (size_t j = 0; exist[i] && j < G[i].GetSize(); ++j)
			fprintf(fp, "%s %s %u\n", mpIntToStr[i].GetCstr(),
				mpIntToStr[G[i][j].to].GetCstr(), G[i][j].w);
	fclose(fp);
}

void AddPoint(const String& point)
{
	auto ptr1 = mpStrToInt.Find(point);
	if (ptr1)
		return;
	nodeCount++;
	mpStrToInt.Insert(point, mpIntToStr.GetSize());
	exist.PushBack(true);
	mpIntToStr.PushBack(point);
	G.PushBack(Vector<Edge>());
}

void DeletePoint(const String& point)
{
	const auto ptr1 = mpStrToInt.Find(point);
	if (!ptr1)
		return;
	for (size_t i = 0; i < G.GetSize(); ++i)
	{
		if (i == *ptr1)
			continue;
		Vector<int>v;
		for (size_t j = 0; j < G[i].GetSize(); ++j)
			if (G[i][j].to == *ptr1)
				v.PushBack(j);
		for (int j = v.GetSize() - 1; j >= 0; --j)
			G[i].Erase(v[j]);
		edgeCount -= v.GetSize();
	}
	edgeCount -= G[*ptr1].GetSize();
	--nodeCount;
	exist[*ptr1] = false;
	mpStrToInt.Erase(point);
}

void AddEdge(const String& from, const String& to, size_t w)
{
	AddPoint(from);
	AddPoint(to);
	G[*mpStrToInt[from]].PushBack(Edge(w, *mpStrToInt[to]));
}

void DeleteEdge(const String& from, const String& to)
{
	auto ptr1 = mpStrToInt.Find(from);
	if (!ptr1)
		return;
	auto ptr2 = mpStrToInt.Find(to);
	if (!ptr2)
		return;
	for (size_t i = 0; i < G[*ptr1].GetSize(); ++i)
		if (G[*ptr1][i].to == *ptr2)
		{
			G[*ptr1].Erase(i);
			break;
		}
	--edgeCount;
}

char op[10], buf1[1 << 4], buf2[1 << 4];
size_t w;

void PrintMenu()
{
	printf("What do you want to do?\n");
	printf("1. Load Graph\n");
	printf("2. Store Graph\n");
	printf("3. Add an edge\n");
	printf("4. Delete an edge\n");
	printf("5. Add a point\n");
	printf("6. Delete a point\n");
	printf("7. Get the shortest path\n");
	printf("press number to choose, 0 to exit\n");
}

Vector<int> p;
int main()
{
	while (1)
	{
		PrintMenu();
		scanf("%s", op);
		printf("\n");

		if (op[0] == '0')
			break;
		switch (op[0] - '0')
		{
		case 1:
			printf("Input the path of the file\n");
			scanf("%s", buf1);
			LoadGraph(buf1);
			break;
			
		case 2:
			printf("Input the path of the file\n");
			scanf("%s", buf1);
			StoreGraph(buf1);
			break;

		case 3:
			printf("Input the point from ans point to and weight\n");
			scanf("%s%s%u", buf1, buf2, &w);
			AddEdge(buf1, buf2, w);
			break;

		case 4:
			printf("Input the point from ans point to\n");
			scanf("%s%s", buf1, buf2);
			DeleteEdge(buf1, buf2);
			break;

		case 5:
			printf("Input the point\n");
			scanf("%s", buf1);
			AddPoint(buf1);
			break;

		case 6:
			printf("Input the point\n");
			scanf("%s", buf1);
			DeletePoint(buf1);
			break;

		case 7:
			printf("Input the point from ans point to\n");
			scanf("%s%s", buf1, buf2);
			{
				auto ptr1 = mpStrToInt[buf1];
				auto ptr2 = mpStrToInt[buf2];
				if (!ptr1 || !ptr2)
				{
					printf("not such point on the graph\n");
					break;
				}
				printf("%u\n", dijkstra(
					*ptr1, *ptr2, p
				));
				PrintPath(p);
				break;
			}

		default:
			printf("Order not found\n");
		}

		system("pause");
		system("cls");
	}
	return 0;
}