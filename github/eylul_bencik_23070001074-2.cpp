#include <raylib.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>

using namespace std;

const int COLS  = 100;
const int ROWS  = 100;
const int CELL  = 20;
const int BAR_H = 140; // for 5 rows

struct Node {
    int x, y;
    int dist;
    Node* parent;
    bool isWall;
    bool isMud;
    bool visited;
};

Node grid[COLS][ROWS];

bool currentPath[COLS][ROWS];
bool previousPath[COLS][ROWS];

// Metrics AND State Management
int    visitedCount    = 0;
double elapsedTime     = 0.0;
bool   pathFound       = false;
bool   algorithmRan    = false;
bool   lastWasDijkstra = true;

bool   dijkstraRan     = false;
int    dijkstraVisited = 0;
double dijkstraTime    = 0.0;
bool   dijkstraFound   = false;
int    dijkstraCost    = 0;

bool   bfsRan          = false;
int    bfsVisited      = 0;
double bfsTime         = 0.0;
bool   bfsFound        = false;
int    bfsHops         = 0;
int    bfsRealCost     = 0; // true weighted cost of BFS path, for display

void ClearPathArray(bool arr[COLS][ROWS]) {
    for (int i = 0; i < COLS; i++)
        for (int j = 0; j < ROWS; j++)
            arr[i][j] = false;
}

void SnapshotPath(Node* endNode, Node* startNode, bool arr[COLS][ROWS]) {
    ClearPathArray(arr);
    Node* temp = endNode->parent;
    while (temp != nullptr && temp != startNode) {
        arr[temp->x][temp->y] = true;
        temp = temp->parent;
    }
}

// Walk path via parent pointers and sum real weights (mud=5, normal=1).
int CalcRealCost(Node* endNode, Node* startNode) {
    int total = 0;
    Node* temp = endNode;
    while (temp != nullptr && temp != startNode) {
        total += temp->isMud ? 5 : 1;
        temp = temp->parent;
    }
    return total;
}

void DrawTextBold(const char* text, int x, int y, int size, Color color) {
    DrawText(text, x + 1, y, size, color);
    DrawText(text, x,     y, size, color);
}

void FullReset() {
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            grid[i][j].x       = i;
            grid[i][j].y       = j;
            grid[i][j].dist    = 1000000;
            grid[i][j].parent  = nullptr;
            grid[i][j].isWall  = false;
            grid[i][j].isMud   = false;
            grid[i][j].visited = false;
        }
    }
    ClearPathArray(currentPath);
    ClearPathArray(previousPath);
    visitedCount = 0;
    elapsedTime  = 0.0;
    pathFound    = false;
    algorithmRan = false;
    dijkstraRan  = false;
    bfsRan       = false;
    dijkstraCost = 0;
    bfsHops      = 0;
    bfsRealCost  = 0;
}

// Keeps walls/mud AND both paths
void PartialReset() {
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            grid[i][j].dist    = 1000000;
            grid[i][j].parent  = nullptr;
            grid[i][j].visited = false;
        }
    }
    visitedCount = 0;
    elapsedTime  = 0.0;
    pathFound    = false;
    algorithmRan = false;
    // currentPath / previousPath intentionally NOT cleared here
}

// DIJKSTRA — cheapest weighted path (mud = 5)
void RunDijkstra(Node* startNode, Node* endNode) {
    priority_queue<pair<int,Node*>, vector<pair<int,Node*>>, greater<pair<int,Node*>>> pq;
    startNode->dist = 0;
    pq.push({0, startNode});

    int dx[] = {1,-1, 0, 0};
    int dy[] = {0, 0, 1,-1};
    double startTime = GetTime();

    while (!pq.empty()) {
        Node* curr = pq.top().second; pq.pop();
        if (curr == endNode) { pathFound = true; break; }
        if (curr->visited) continue;
        curr->visited = true;
        visitedCount++;

        for (int i = 0; i < 4; i++) {
            int nx = curr->x + dx[i], ny = curr->y + dy[i];
            if (nx < 0 || nx >= COLS || ny < 0 || ny >= ROWS) continue;
            if (grid[nx][ny].isWall) continue;
            int cost = grid[nx][ny].isMud ? 5 : 1;
            if (grid[nx][ny].dist > curr->dist + cost) {
                grid[nx][ny].dist   = curr->dist + cost;
                grid[nx][ny].parent = curr;
                pq.push({grid[nx][ny].dist, &grid[nx][ny]});
            }
        }
    }

    elapsedTime     = GetTime() - startTime;
    lastWasDijkstra = true;
    algorithmRan    = true;

    for (int i = 0; i < COLS; i++)
        for (int j = 0; j < ROWS; j++)
            previousPath[i][j] = currentPath[i][j];

    if (pathFound) SnapshotPath(endNode, startNode, currentPath);
    else           ClearPathArray(currentPath);

    dijkstraRan     = true;
    dijkstraVisited = visitedCount;
    dijkstraTime    = elapsedTime;
    dijkstraFound   = pathFound;
    dijkstraCost    = pathFound ? endNode->dist : 0;
}

// BFS — fewest hops (mud weight ignored by algorithm)
void RunBFS(Node* startNode, Node* endNode) {
    queue<Node*> q;
    startNode->dist    = 0;
    startNode->visited = true;
    q.push(startNode);

    int dx[] = {1,-1, 0, 0};
    int dy[] = {0, 0, 1,-1};
    double startTime = GetTime();

    while (!q.empty()) {
        Node* curr = q.front(); q.pop();
        visitedCount++;
        if (curr == endNode) { pathFound = true; break; }

        for (int i = 0; i < 4; i++) {
            int nx = curr->x + dx[i], ny = curr->y + dy[i];
            if (nx < 0 || nx >= COLS || ny < 0 || ny >= ROWS) continue;
            if (grid[nx][ny].isWall || grid[nx][ny].visited) continue;
            grid[nx][ny].dist    = curr->dist + 1; // just hop count
            grid[nx][ny].parent  = curr;
            grid[nx][ny].visited = true;
            q.push(&grid[nx][ny]);
        }
    }

    elapsedTime     = GetTime() - startTime;
    lastWasDijkstra = false;
    algorithmRan    = true;

    for (int i = 0; i < COLS; i++)
        for (int j = 0; j < ROWS; j++)
            previousPath[i][j] = currentPath[i][j];

    if (pathFound) {
        bfsRealCost = CalcRealCost(endNode, startNode); // before parent pointers are lost
        SnapshotPath(endNode, startNode, currentPath);
    } else {
        bfsRealCost = 0;
        ClearPathArray(currentPath);
    }

    bfsRan     = true;
    bfsVisited = visitedCount;
    bfsTime    = elapsedTime;
    bfsFound   = pathFound;
    bfsHops    = pathFound ? endNode->dist : 0;
}

int main() {
    int winW = COLS * CELL;         
    int winH = ROWS * CELL + BAR_H; 
    InitWindow(winW, winH, "Pathfinding Visualizer: Dijkstra vs BFS - Eylul Bencik");
    SetTargetFPS(60);
    FullReset();

    Node* startNode = &grid[5][15];
    Node* endNode   = &grid[35][15];

    int px = 20;           // left column  (Dijkstra side)
    int cx = winW/2 + 20;  // right column (BFS side)

    Color COL_GREEN   = GetColor(0x00E430FF);
    Color COL_YELLOW  = GetColor(0xFDF900FF); // CURRENT  + current path
    Color COL_ORANGE  = GetColor(0xFF8C00FF); // PREVIOUS + previous path
    Color COL_RED     = GetColor(0xFF3333FF); // BFS True Cost when higher than Dijkstra
    Color COL_WHITE   = GetColor(0xFFFFFFFF);
    Color COL_GRAY    = GetColor(0x888888FF);
    Color COL_DIMGRAY = GetColor(0x444444FF);
    Color COL_DIVIDER = GetColor(0x2A2A2AFF);
    Color COL_BAR     = GetColor(0x0A0A0AFF);
    Color COL_AMBER   = GetColor(0xFFCC44FF);

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_R)) FullReset();

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            int mx = GetMouseX() / CELL, my = GetMouseY() / CELL;
            if (mx >= 0 && mx < COLS && my >= 0 && my < ROWS)
                if (&grid[mx][my] != startNode && &grid[mx][my] != endNode) {
                    grid[mx][my].isWall = true; grid[mx][my].isMud = false;
                }
        }

        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            int mx = GetMouseX() / CELL, my = GetMouseY() / CELL;
            if (mx >= 0 && mx < COLS && my >= 0 && my < ROWS)
                if (&grid[mx][my] != startNode && &grid[mx][my] != endNode) {
                    grid[mx][my].isMud = true; grid[mx][my].isWall = false;
                }
        }

        if (IsKeyPressed(KEY_SPACE)) { PartialReset(); RunDijkstra(startNode, endNode); }
        if (IsKeyPressed(KEY_B))     { PartialReset(); RunBFS(startNode, endNode); }

        // Draw grid
        BeginDrawing();
        ClearBackground(GetColor(0x181818FF));

        for (int i = 0; i < COLS; i++) {
            for (int j = 0; j < ROWS; j++) {
                Color c;
                if      (&grid[i][j] == startNode) c = COL_GREEN;
                else if (&grid[i][j] == endNode)   c = GetColor(0xE62937FF);
                else if (grid[i][j].isWall)        c = GetColor(0x222222FF);
                else if (grid[i][j].isMud)         c = GetColor(0x8B5E3CFF);
                else if (grid[i][j].visited)       c = GetColor(0x3A7EBFFF);
                else                               c = GetColor(0xDDDDDDFF);
                DrawRectangle(i * CELL, j * CELL, CELL - 1, CELL - 1, c);
            }
        }

        // Previous path (orange) under current (yellow)
        for (int i = 0; i < COLS; i++)
            for (int j = 0; j < ROWS; j++)
                if (previousPath[i][j])
                    DrawRectangle(i * CELL, j * CELL, CELL - 1, CELL - 1, COL_ORANGE);

        for (int i = 0; i < COLS; i++)
            for (int j = 0; j < ROWS; j++)
                if (currentPath[i][j])
                    DrawRectangle(i * CELL, j * CELL, CELL - 1, CELL - 1, COL_YELLOW);

        // Dashboard UI Setup            
        int barY = ROWS * CELL;
        int r1 = barY +   6;  // headers
        int r2 = barY +  32;  // time + visited 
        int r3 = barY +  54;  // cost + hops
        int r4 = barY +  80;  // full width comparison row
        int r5 = barY + 108;  // legend

        // Bar background + top border
        DrawRectangle(0, barY, winW, BAR_H, COL_BAR);
        DrawLine(0, barY, winW, barY, COL_DIVIDER);

        // Row 5 — Legend (always visible)
        DrawText("Normal=1  Mud=5", px, r5, 13, COL_DIMGRAY);
        DrawText("Dijkstra=cheapest path   BFS=fewest steps, ignores mud", px + 125, r5, 13, COL_DIMGRAY);
        DrawRectangle(winW - 155, r5, 11, 11, COL_YELLOW);
        DrawText("Current",  winW - 141, r5, 13, COL_GRAY);
        DrawRectangle(winW - 75,  r5, 11, 11, COL_ORANGE);
        DrawText("Previous", winW - 61,  r5, 13, COL_GRAY);
        DrawLine(0, r5 - 6, winW, r5 - 6, COL_DIVIDER);

        char buf[300];

        if (!algorithmRan && !dijkstraRan && !bfsRan) {
            DrawText("SPACE = Run Dijkstra (Weighted)     B = Run BFS (Unweighted)", px, r1, 20, COL_GRAY);
            DrawText("Left Click = Wall     Right Click = Mud     R = Full Reset",   px, r2, 16, COL_DIMGRAY);
            DrawText("Run both algorithms to see a live side-by-side comparison.",   px, r3, 14, COL_DIMGRAY);

        } else if (dijkstraRan && bfsRan) {
            // Two column layout
            DrawLine(winW/2, barY + 4, winW/2, r5 - 10, COL_DIVIDER);

            bool dijCurrent = lastWasDijkstra;

            // Row 1 — Headers
            const char* dijHeader = dijCurrent ? ">> CURRENT  (DIJKSTRA)" : "   PREVIOUS (DIJKSTRA)";
            const char* bfsHeader = dijCurrent ? "   PREVIOUS (BFS)"      : ">> CURRENT  (BFS)";
            Color dijHColor       = dijCurrent ? COL_YELLOW : COL_ORANGE;
            Color bfsHColor       = dijCurrent ? COL_ORANGE : COL_YELLOW;

            DrawTextBold(dijHeader, px, r1, 19, dijHColor);
            DrawTextBold(bfsHeader, cx, r1, 19, bfsHColor);

            // Row 2 — Time + Visited (left: Dijkstra, right: BFS)
            DrawText("Time:",    px,       r2, 15, COL_GRAY);
            sprintf(buf, "%.6f s", dijkstraTime);
            DrawText(buf,        px + 48,  r2, 15, COL_WHITE);
            DrawText("Visited:", px + 155, r2, 15, COL_GRAY);
            sprintf(buf, "%d", dijkstraVisited);
            DrawText(buf,        px + 220, r2, 15, COL_WHITE);
            DrawText("Path:",    px + 275, r2, 15, COL_GRAY);
            DrawText(dijkstraFound ? "YES" : "NO", px + 315, r2, 15, dijkstraFound ? COL_GREEN : COL_RED);

            DrawText("Time:",    cx,       r2, 15, COL_GRAY);
            sprintf(buf, "%.6f s", bfsTime);
            DrawText(buf,        cx + 48,  r2, 15, COL_WHITE);
            DrawText("Visited:", cx + 155, r2, 15, COL_GRAY);
            sprintf(buf, "%d", bfsVisited);
            DrawText(buf,        cx + 220, r2, 15, COL_WHITE);
            DrawText("Path:",    cx + 275, r2, 15, COL_GRAY);
            DrawText(bfsFound ? "YES" : "NO", cx + 315, r2, 15, bfsFound ? COL_GREEN : COL_RED);

            // Row 3 — Cost + Hops
            DrawText("Weighted Cost:", px,      r3, 15, COL_GRAY);
            sprintf(buf, "%d", dijkstraCost);
            DrawText(buf,             px + 125, r3, 15, COL_WHITE);

            DrawText("Hops:",      cx,       r3, 15, COL_GRAY);
            sprintf(buf, "%d", bfsHops);
            DrawText(buf,         cx + 48,  r3, 15, COL_WHITE);
            DrawText("True Cost:", cx + 100, r3, 15, COL_GRAY);
            Color trueCostColor = (bfsRealCost > dijkstraCost) ? COL_RED : COL_WHITE;
            sprintf(buf, "%d", bfsRealCost);
            DrawText(buf,         cx + 190, r3, 15, trueCostColor);
            if (bfsRealCost > dijkstraCost)
                DrawText("(!)", cx + 220, r3, 15, COL_RED);

            // Row 4 Comparison sentence
            if (dijkstraFound && bfsFound) {
                int diff = bfsRealCost - dijkstraCost;
                if (diff > 0)
                    sprintf(buf,
                        "Result:  Dijkstra cost %d  vs  BFS true cost %d  — BFS costs %d more because it walked through mud.",
                        dijkstraCost, bfsRealCost, diff);
                else if (diff < 0)
                    sprintf(buf,
                        "Result:  Dijkstra cost %d  vs  BFS true cost %d  — BFS happened to avoid mud this run.",
                        dijkstraCost, bfsRealCost);
                else
                    sprintf(buf,
                        "Result:  Both algorithms cost %d  — No mud difference on these paths.",
                        dijkstraCost);
                DrawText(buf, px, r4, 14, COL_AMBER);
            } else {
                DrawText("Result:  One or both algorithms did not find a path.", px, r4, 14, COL_DIMGRAY);
            }

        } else {
            // Only one has run
            if (lastWasDijkstra) {
                DrawTextBold(">> CURRENT  (DIJKSTRA)", px, r1, 19, COL_YELLOW);

                DrawText("Time:",    px,       r2, 15, COL_GRAY);
                sprintf(buf, "%.6f s", dijkstraTime);
                DrawText(buf,        px + 50,  r2, 15, COL_WHITE);
                DrawText("Visited:", px + 170, r2, 15, COL_GRAY);
                sprintf(buf, "%d", dijkstraVisited);
                DrawText(buf,        px + 240, r2, 15, COL_WHITE);
                DrawText("Path:",    px + 310, r2, 15, COL_GRAY);
                DrawText(dijkstraFound ? "YES" : "NO", px + 355, r2, 15, dijkstraFound ? COL_GREEN : COL_RED);

                DrawText("Weighted Cost:", px,      r3, 15, COL_GRAY);
                sprintf(buf, "%d", dijkstraCost);
                DrawText(buf,             px + 130, r3, 15, COL_WHITE);

                DrawText("Press  B  to run BFS — both paths will appear side by side.", px, r4, 14, COL_DIMGRAY);
            } else {
                DrawTextBold(">> CURRENT  (BFS)", px, r1, 19, COL_YELLOW);

                DrawText("Time:",    px,       r2, 15, COL_GRAY);
                sprintf(buf, "%.6f s", bfsTime);
                DrawText(buf,        px + 50,  r2, 15, COL_WHITE);
                DrawText("Visited:", px + 170, r2, 15, COL_GRAY);
                sprintf(buf, "%d", bfsVisited);
                DrawText(buf,        px + 240, r2, 15, COL_WHITE);
                DrawText("Path:",    px + 310, r2, 15, COL_GRAY);
                DrawText(bfsFound ? "YES" : "NO", px + 355, r2, 15, bfsFound ? COL_GREEN : COL_RED);

                DrawText("Hops:",      px,       r3, 15, COL_GRAY);
                sprintf(buf, "%d", bfsHops);
                DrawText(buf,         px + 50,  r3, 15, COL_WHITE);
                DrawText("True Cost:", px + 110, r3, 15, COL_GRAY);
                sprintf(buf, "%d", bfsRealCost);
                DrawText(buf,         px + 205, r3, 15, COL_WHITE);

                DrawText("Press  SPACE  to run Dijkstra — both paths will appear side by side.", px, r4, 14, COL_DIMGRAY);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
