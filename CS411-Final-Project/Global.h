#pragma once
#include <unordered_set>
#include <unordered_map>
using namespace std;

/* ======================================================================
 * Global game paramenters
 * =================================================================== */

static const int WIDTH_WINDOW_SCREEN = 640;
static const int HEIGHT_WINDOW_SCREEN = 480;
static const int WIDTH_SCORE_NUM = 28;
static const int HEIGHT_SCORE_NUM = 36;

extern int Score;
extern unordered_set<int> UnlockedLevels;
extern unordered_map<int, int> BestScores;

static const int N_LEVELS = 2;