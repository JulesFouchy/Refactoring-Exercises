#include <string>
#include <vector>

#ifndef GAME_H_
#define GAME_H_

class Game {
private:
    std::vector<std::string> players;

    std::vector<int> places;
    std::vector<int> purses;

    std::vector<bool> inPenaltyBox;

    std::vector<std::string> popQuestions;
    std::vector<std::string> scienceQuestions;
    std::vector<std::string> sportsQuestions;
    std::vector<std::string> rockQuestions;

    unsigned int currentPlayer;
    bool         isGettingOutOfPenaltyBox;

public:
    Game();
    std::string createRockQuestion(int index);
    bool        isPlayable();
    bool        add(const std::string& playerName);

    int  howManyPlayers();
    void roll(int roll);

private:
    void        askQuestion();
    std::string currentCategory();

public:
    bool wasCorrectlyAnswered();
    bool wrongAnswer();

private:
    bool didPlayerWin();
};

#endif /* GAME_H_ */