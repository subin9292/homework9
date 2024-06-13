#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 10 // 최대 정점 수

// Node 구조체 - 각 정점을 나타내는 노드
typedef struct Node {
    int vertex;          // 정점 번호
    struct Node* next;   // 다음 노드를 가리키는 포인터
} Node;

// Graph 구조체
typedef struct Graph {
    Node* adjLists[MAX_VERTICES];  // 각 정점의 인접 리스트를 가리키는 배열
    bool visited[MAX_VERTICES];    // 각 정점의 방문 여부를 저장하는 배열
} Graph;

// 함수 프로토타입 선언
void initializeGraph(Graph* graph);
void insertVertex(Graph* graph, int vertex);
void insertEdge(Graph* graph, int src, int dest);
void DFS(Graph* graph, int startVertex);
void BFS(Graph* graph, int startVertex);
void printGraph(Graph* graph);
Node* createNode(int v);
void resetVisited(Graph* graph);
bool isValidVertex(int vertex);
bool isGraphInitialized(Graph* graph);

// 메인 함수
int main() {
    Graph* graph = (Graph*)malloc(sizeof(Graph)); // 그래프 생성
    initializeGraph(graph);  // 그래프 첫 초기화
    char choice;             // 사용자 명령어 저장
    int vertex, src, dest;   // 정점 및 엣지의 소스/목적지 정점

   printf("\n[----- [강수빈]  [2023078011] -----]\n");

    while (1) {  // q가 입력될때까지 무한 실행
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                       Graph Searches                            \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Graph         = z                                    \n");
        printf(" Insert Vertex            = v       Insert Edge               = e \n");
        printf(" Depth First Search       = d       Breath First Search      = b \n");
        printf(" Print Graph              = p       Quit                      = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command : ");
        scanf(" %c", &choice);

        switch (choice) {  // 사용자가 입력한 명령어에 따라 기능 실행
            case 'z': // 그래프 초기화
                initializeGraph(graph);
                break;
            case 'v':  // vertex 삽입
                printf("Enter vertex to insert (0-9): ");
                scanf("%d", &vertex);
                if (isValidVertex(vertex)) {
                    insertVertex(graph, vertex);
                } else {
                    printf("Invalid vertex number.\n");
                }
                break;
            case 'e': // edge 삽입
                printf("Enter source vertex (0-9): ");
                scanf("%d", &src);
                printf("Enter destination vertex (0-9): ");
                scanf("%d", &dest);
                if (isValidVertex(src) && isValidVertex(dest)) {
                    insertEdge(graph, src, dest);
                } else {
                    printf("Invalid vertex number.\n");
                }
                break;
            case 'd':  // depth first search
                printf("Enter starting vertex for DFS (0-9): ");
                scanf("%d", &vertex);
                if (isValidVertex(vertex)) {
                    resetVisited(graph);
                    DFS(graph, vertex);
                } else {
                    printf("Invalid vertex number.\n");
                }
                break;
            case 'b':  // breath first search
                printf("Enter starting vertex for BFS (0-9): ");
                scanf("%d", &vertex);
                if (isValidVertex(vertex)) {
                    resetVisited(graph);
                    BFS(graph, vertex);
                } else {
                    printf("Invalid vertex number.\n");
                }
                break;
            case 'p':  // 그래프 출력
                printGraph(graph);
                break;
            case 'q':
                free(graph);  // 메모리 해제
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

// 그래프 초기화 함수
void initializeGraph(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjLists[i] = NULL;  // 인접 리스트 초기화
        graph->visited[i] = false;  // 방문 여부 초기화
    }
    printf("Graph initialized.\n");
}

// vertex 삽입 함수
void insertVertex(Graph* graph, int vertex) {
    if (graph->adjLists[vertex] == NULL) {
        graph->adjLists[vertex] = createNode(vertex);  // 새로운 노드 생성
        printf("Vertex %d inserted.\n", vertex);  // 확인 문구 출력
    } else {
        printf("Vertex %d already exists.\n", vertex); 
    }
}

// 노드 생성 함수
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // 새로운 노드 메모리 할당
    newNode->vertex = v;  // 정점 번호 설정
    newNode->next = NULL; // 다음 노드를 NULL로 초기화
    return newNode;       // 생성된 노드 반환
}

// edge 삽입 함수
void insertEdge(Graph* graph, int src, int dest) {
    // src에서 dest로의 edge 추가
    Node* newNode = createNode(dest); 
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // dest에서 src로의 edge 추가 
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;

    printf("Edge added from %d to %d.\n", src, dest);
}

// 깊이 우선 탐색 함수
void DFS(Graph* graph, int startVertex) {
    Node* adjList = graph->adjLists[startVertex]; // 현재 정점의 인접 리스트 가져오기
    Node* temp = adjList;

    graph->visited[startVertex] = true;  // 현재 정점 방문 표시
    printf("%d ", startVertex);  // 방문한 정점 출력

    while (temp != NULL) {  // 인접한 모든 정점 방문
        int connectedVertex = temp->vertex;

        if (!graph->visited[connectedVertex]) {
            DFS(graph, connectedVertex);  // 재귀 호출을 통해 깊이 우선 탐색
        }
        temp = temp->next;
    }
}

// 너비 우선 탐색 함수
void BFS(Graph* graph, int startVertex) {
    int queue[MAX_VERTICES]; // 큐를 위한 배열
    int front = -1;          // 큐의 앞부분 인덱스
    int rear = -1;           // 큐의 뒷부분 인덱스

    graph->visited[startVertex] = true;  // 시작 정점 방문 표시
    queue[++rear] = startVertex;         // 큐에 시작 정점 추가

    while (front != rear) {  // 큐가 빌 때까지 반복
        int currentVertex = queue[++front];
        printf("%d ", currentVertex);  // 방문한 정점 출력

        Node* temp = graph->adjLists[currentVertex];

        while (temp) {  // 현재 정점에 인접한 모든 정점 방문
            int adjVertex = temp->vertex;

            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = true; // 방문 표시
                queue[++rear] = adjVertex;        // 큐에 인접 정점 추가
            }
            temp = temp->next;
        }
    }
}

// 그래프 출력 함수
void printGraph(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        Node* temp = graph->adjLists[i];
        printf("\n Vertex %d : ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// 방문 배열 초기화 함수
void resetVisited(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->visited[i] = false;  // 모든 정점을 미방문으로 초기화
    }
}

// 정점 번호 유효성 검사 함수
bool isValidVertex(int vertex) {
    return vertex >= 0 && vertex < MAX_VERTICES;
}

// 그래프 초기화 여부 확인 함수
bool isGraphInitialized(Graph* graph) {
    return graph != NULL;
}
