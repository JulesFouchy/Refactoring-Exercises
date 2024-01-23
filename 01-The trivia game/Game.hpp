#include <iostream>
#include <vector>
using namespace std;

#ifndef GAME_H_
#define GAME_H_

class Game {
private:
    vector<string> players;

    std::vector<int> places;
    std::vector<int> purses;

    std::vector<bool> inPenaltyBox;

    std::vector<string> popQuestions;
    std::vector<string> scienceQuestions;
    std::vector<string> sportsQuestions;
    std::vector<string> rockQuestions;

    unsigned int currentPlayer;
    bool         isGettingOutOfPenaltyBox;

public:
    Game();
    string createRockQuestion(int index);
    bool   isPlayable();
    bool   add(const string& playerName);

    int  howManyPlayers();
    void roll(int roll);

private:
    void   askQuestion();
    string currentCategory();

public:
    bool wasCorrectlyAnswered();
    bool wrongAnswer();

private:
    bool didPlayerWin();
};

#endif /* GAME_H_ */