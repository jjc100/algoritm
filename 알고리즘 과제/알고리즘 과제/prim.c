#include<stdio.h>
#include <stdlib.h>
#include <limits.h>


#define TRUE 1
#define FALSE 0

#define VERTICES 7
#define INF 1000L


#define BIG_INT     8192
#define MAX_SIZE    10
#define FOUND       1
#define NOT_FOUND   -1





int result[VERTICES][VERTICES];

int selected[VERTICES];
int dist[VERTICES];
int get_min_vertex(int n);
//void prim(int s, int n);
void prim(int array[VERTICES][VERTICES]);



void load_graph_from_file(char* filename, int graph[][MAX_SIZE], int* n);
int choose(int* distance, int* found, int n);
void shortest_path(int v, int graph[][MAX_SIZE], int* distance, int* found, int* pre_vertex, int n);
void print_path(int* pre_vertex, int n);




main()
{
	int adj_mat[VERTICES][VERTICES] = {
		{ 0, 29, INF, INF, INF, 10, INF },
		{ 29,  0, 16, INF, INF, INF, 15 },
		{ INF, 16, 0, 12, INF, INF, INF },
		{ INF, INF, 12, 0, 22, INF, 18 },
		{ INF, INF, INF, 22, 0, 27, 25 },
		{ 10, INF, INF, INF, 27, 0, INF },
		{ INF, 15, INF, 18, 25, INF, 0 } };

	//int resultGraph[VERTICES][VERTICES] = { 0, };

	printf("\n                   <prim 알고리즘>                  \n");
	printf("\n 주어진 그래프에서 prim의 최소비용 신장트리를 알려줍니다.");
	printf("\n +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	printf("\n +                                                                 +");
	printf("\n +                         [a]-------29------[b]                   +");
	printf("\n +                         /                 / (                   +");
	printf("\n +                        /                 /   (                  +");
	printf("\n +                      10                15     16                 +");
	printf("\n +                      /                /         (                +");
	printf("\n +                     /                /           (               +");
	printf("\n +                    [f]           [g]            [c]             +");
	printf("\n +                     (           /   (            /               +");
	printf("\n +                      (         /      (         /                +");
	printf("\n +                      27       25       18      12                 +");
	printf("\n +                        (     /           (    /                  +");
	printf("\n +                          (  /             (  /                   +");
	printf("\n +                           [e]------22-------[d]                   +");
	printf("\n +                                                                 +");
	printf("\n +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	////////////////////////////////////////////////////////////////////////////////////
	

	prim(adj_mat[VERTICES][VERTICES]);
	//prim(0, VERTICES);

	print_path(result, VERTICES);

	int graph[MAX_SIZE][MAX_SIZE];
	int distance[MAX_SIZE];
	int found[MAX_SIZE];
	int pre_vertex[MAX_SIZE];
	int v;
	int n;  // num of vertex

	//load_graph_from_file("graph.dat", graph, &n);
	//shortest_path(0, graph, distance, found, pre_vertex, n);
	//print_path(pre_vertex, n);

	return 0;
	
	
}



void prim(int array[][VERTICES])
{
	int s = 0, n;

	int i, j, u, v, min = 0;

	n = VERTICES;

	for (u = 0; u<n; u++)
		dist[u] = INF;								//key값
	dist[s] = 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			result[i][j] = 0;
		}
	}
	for (i = 0; i<n; i++) {
		u = get_min_vertex(n);
		selected[u] = TRUE;
		if (dist[u] == INF)
			return;
		min += dist[u];
		printf("\n\t%d번째  %c방문  거리=%d, 최소 비용=%d \n", i, u + 65, dist[u], min);
		for (v = 0; v<n; v++)
			if (array[u][v] != INF)
				if (!selected[v] && array[u][v] < dist[v]) {
					result[u][v] = array[u][v];
					dist[v] = array[u][v];
				}
	}

	return result;
}


/*
void prim(int s, int n)
{
	int i, u, v, min = 0;

	for (u = 0; u<n; u++)
		dist[u] = INF;
	dist[s] = 0;
	for (i = 0; i<n; i++) {
		u = get_min_vertex(n);
		selected[u] = TRUE;
		if (dist[u] == INF)
			return;
		min += dist[u];
		printf("\n\t%d번째  %c방문  거리=%d, 최소 비용=%d \n", i, u + 65, dist[u], min);
		for (v = 0; v<n; v++)
			if (adj_mat[u][v] != INF)
				if (!selected[v] && adj_mat[u][v]< dist[v])
					dist[v] = adj_mat[u][v];
	}

}

*/

// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i <n; i++)
		if (!selected[i]) {
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && (dist[i] < dist[v])) v = i;
	return (v);
}
//





void load_graph_from_file(char* filename, int graph[][MAX_SIZE], int* n) {
	FILE* fp;
	fopen_s(&fp, filename, "r");

	int v, w;   // start vertex, end vertex
	int weight;
	
	int i, j;
	
	if (fp == NULL) {
	
		printf("file not found exception.");
		exit(1);
		}
	
	fscanf_s(fp, "%d", n);

	if (*n > MAX_SIZE) { printf("too many vertex"); exit(1); }
	
	for (i = 0; i<*n; ++i) {
	
		for (j = 0; j<*n; ++j) {
		
			graph[i][j] = BIG_INT;
			
		}
		}
	
	while (!feof(fp)) {
	
		fscanf_s(fp, "%d %d %d", &v, &w, &weight);
		
		graph[v][w] = weight;
		
	}
	
}


int choose(int* distance, int* found, int n) {

	int i;
	
	int min = INT_MAX;
	int minpos = -1;
	
	for (i = 0; i<n; ++i) {
	
		if (found[i] > NOT_FOUND) continue;
		if (distance[i] >= min) continue;
		
		min = distance[i];
		
		minpos = i;
		
		}
	
		return minpos;
	
}

void shortest_path(int v, int graph[][MAX_SIZE], int* distance, int* found, int* pre_vertex, int n) {

		int i, u, w;

		//int pre_vertex;


		// init

		for (i = 0; i<n; ++i) {

				distance[i] = graph[v][i];

				found[i] = NOT_FOUND;

				if (distance[i] > 0 && distance[i] < BIG_INT) pre_vertex[i] = v;

				else pre_vertex[i] = -1;

		}





		distance[v] = 0;

		found[v] = FOUND;



		for (i = 0; i<n - 1; ++i) {

				u = choose(distance, found, n); //가장 가까운 정점을 찾는다.

				found[u] = FOUND;

				for (w = 0; w<n; ++w) {        // 최단 경로상의 정점들로부터 인접정점들까지의 모든 distance를 계산한다.

						if (found[w] > NOT_FOUND) continue;

						if (distance[u] + graph[u][w] >= distance[w]) continue;

						distance[w] = distance[u] + graph[u][w];

						pre_vertex[w] = u;

				}

		}

}

void print_path(int pre_vertex[][VERTICES], int n) {
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			printf("%d ->", pre_vertex[i][j]);
		printf("\n");
	}
}

/*
void print_path(int* pre_vertex, int n) {

		int i;

		int cv; // current vertex

		for (i = 0; i<n; ++i) {

				cv = i;


				printf("shortest path to %d :[%d]", cv, cv);

				while (pre_vertex[cv] > 0) {
				printf("<-[%d]", pre_vertex[cv]);
				
				cv = pre_vertex[cv];
				
				}
			
				printf("\n");
			
		}
	
}
*/
