#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>

static const int MAX_ROWS   = 1000;
static const int MAX_COLS   = 1000;
static const int MAX_PATH   = 100000;

struct Point {
    int r, c;
};

char   grid[MAX_ROWS][MAX_COLS];
bool   seen[MAX_ROWS][MAX_COLS];
char   logSteps[MAX_PATH][60];
int    logSize = 0;
Point  startPt, exitPt;

bool dfsSearch(int r, int c, int pr, int pc, int totalR, int totalC);
void processAll(std::ifstream &inF, std::ofstream &outF);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_entrada> <arquivo_saida>\n";
        return EXIT_FAILURE;
    }
    std::ifstream inF(argv[1]);
    if (!inF) {
        std::cerr << "Erro: nao foi possivel abrir '" << argv[1] << "'\n";
        return EXIT_FAILURE;
    }
    std::ofstream outF(argv[2]);
    if (!outF) {
        std::cerr << "Erro: nao foi possivel criar '" << argv[2] << "'\n";
        return EXIT_FAILURE;
    }
    processAll(inF, outF);
    return EXIT_SUCCESS;
}

bool dfsSearch(int r, int c, int pr, int pc, int totalR, int totalC) {
    // verifica limites e obstáculos
    if (r < 0 || r >= totalR || c < 0 || c >= totalC) return false;
    if (grid[r][c] != '0' || seen[r][c])           return false;

    seen[r][c] = true;

    // registra passo
    if (pr < 0 && pc < 0) {
        std::snprintf(logSteps[logSize++], 60, "INI@%d,%d", r, c);
    } else if (r == pr && c == pc + 1) {
        std::snprintf(logSteps[logSize++], 60, "D->%d,%d", r, c);
    } else if (r == pr - 1 && c == pc) {
        std::snprintf(logSteps[logSize++], 60, "F->%d,%d", r, c);
    } else if (r == pr && c == pc - 1) {
        std::snprintf(logSteps[logSize++], 60, "E->%d,%d", r, c);
    } else if (r == pr + 1 && c == pc) {
        std::snprintf(logSteps[logSize++], 60, "T->%d,%d", r, c);
    }

    // se estiver na borda (e não for o início), achou saída
    if ((r == 0 || r == totalR - 1 || c == 0 || c == totalC - 1)
        && !(r == startPt.r && c == startPt.c)) {
        exitPt = {r, c};
        std::snprintf(logSteps[logSize++], 60, "FIM@%d,%d", r, c);
        return true;
    }

    // nova ordem de exploração: esquerda, baixo, direita, cima
    if (dfsSearch(r,     c - 1, r, c, totalR, totalC)) return true;
    if (dfsSearch(r + 1, c,     r, c, totalR, totalC)) return true;
    if (dfsSearch(r,     c + 1, r, c, totalR, totalC)) return true;
    if (dfsSearch(r - 1, c,     r, c, totalR, totalC)) return true;

    // marca retrocesso (se ainda não achou saída e não é o início)
    if (!(r == startPt.r && c == startPt.c) && exitPt.r < 0) {
        std::snprintf(logSteps[logSize++], 60,
                      "BT@%d,%d->%d,%d", r, c, pr, pc);
    }
    return false;
}

void processAll(std::ifstream &inF, std::ofstream &outF) {
    std::string line;
    if (!std::getline(inF, line)) {
        std::cerr << "Erro: formato invalido ou arquivo vazio.\n";
        std::exit(EXIT_FAILURE);
    }
    int mazeCount = std::atoi(line.c_str());

    for (int idx = 0; idx < mazeCount; ++idx) {
        if (!std::getline(inF, line)) {
            std::cerr << "Erro: dimensoes faltando no labirinto " << idx << "\n";
            std::exit(EXIT_FAILURE);
        }
        std::istringstream hdr(line);
        int cols, rows;
        hdr >> cols >> rows;

        // reset
        startPt = {-1, -1};
        exitPt  = {-1, -1};
        logSize = 0;
        std::memset(seen, 0, sizeof(seen));

        // lê o labirinto
        for (int rr = 0; rr < rows; ++rr) {
            std::getline(inF, line);
            std::istringstream rowStream(line);
            std::string cell;
            for (int cc = 0; cc < cols; ++cc) {
                rowStream >> cell;
                grid[rr][cc] = cell[0];
                if (cell[0] == 'X') {
                    startPt = {rr, cc};
                    grid[rr][cc] = '0';
                }
            }
        }

        if (startPt.r < 0) {
            std::cerr << "Erro: ponto inicial 'X' nao encontrado no labirinto " << idx << "\n";
            std::exit(EXIT_FAILURE);
        }

        // busca
        dfsSearch(startPt.r, startPt.c, -1, -1, rows, cols);

        // se não achou saída
        if (exitPt.r < 0) {
            std::strcpy(logSteps[logSize++], "FIM@-,-");
        }

        // saída no formato original
        outF << "L" << idx << ":";
        for (int k = 0; k < logSize; ++k) {
            outF << (k ? "|" : "") << logSteps[k];
        }
        outF << "\n";
    }
    std::cout << "fim\n";
}
