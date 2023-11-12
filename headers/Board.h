#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

#define vec vector
typedef pair<bool, int> pbi;
#define mp make_pair

class Board {
    private:
        Vector2u size;
        int nmines;
        vector<Vector2u> minepos;

        random_device dev;
        mt19937 rng;
        uniform_int_distribution<mt19937::result_type> randomMinex, randomMiney;

        int checkMinesAround(Vector2u pos);
    public:
        Board(Vector2u s, int mines);
        int updateAt(Vector2i pos);
        void regenerate_map(Vector2u s, int mines, Vector2i clickPos);
        void regenerate_visible();
        vector<vector<pair<bool, int>>> generatedmap;
        Vector2i getSize();
};

#endif