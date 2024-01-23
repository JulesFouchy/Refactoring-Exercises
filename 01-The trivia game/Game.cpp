#include "Game.hpp"
#include <fmt/format.h>

using namespace std;

static constexpr int QUESTIONS_COUNT{50};

Game::Game()
    : places{}, purses{}, currentPlayer(0)
{
    for (int i = QUESTIONS_COUNT - 1; i >= 0; i--)
    {
        const std::string str0 = fmt::format("Pop Question {}", i);
        popQuestions.push_back(str0);

        const std::string str = fmt::format("Science Question {}", i);
        scienceQuestions.push_back(str);

        const std::string str1 = fmt::format("Sports Question {}", i);
        sportsQuestions.push_back(str1);

        rockQuestions.push_back(createRockQuestion(i));
    }
}

string Game::createRockQuestion(int index)
{
    const std::string indexStr = fmt::format("Rock Question {}", index);
    return indexStr;
}

bool Game::isPlayable()
{
    return (howManyPlayers() >= 2);
}

void print_all_player_names(const vector<string>& players)
{
    for (const std::string& player_name : players)
    {
        fmt::print("They join {}.\n", player_name);
    }
}

bool Game::add(const string& playerName)
{
    fmt::print("{} was added\n", playerName);
    fmt::print("They are player number {}\n", players.size() + 1);
    print_all_player_names(players);

    players.push_back(playerName);
    places.push_back(0);
    purses.push_back(0);
    inPenaltyBox.push_back(false);
    return true;
}

int Game::howManyPlayers()
{
    return players.size();
}

void Game::roll(int roll)
{
    fmt::print("{} is the current player\n", players[currentPlayer]);
    fmt::print("They have rolled a {}\n", roll);

    if (inPenaltyBox[currentPlayer])
    {
        if (roll % 2 != 0)
        {
            isGettingOutOfPenaltyBox = true;

            fmt::print("{} is getting out of the penalty box\n", players[currentPlayer]);
            places[currentPlayer] = places[currentPlayer] + roll;
            if (places[currentPlayer] > 11)
                places[currentPlayer] = places[currentPlayer] - 12;

            fmt::print("{}'s new location is {}\n", players[currentPlayer], places[currentPlayer]);
            fmt::print("The category is {}\n", currentCategory());
            askQuestion();
        }
        else
        {
            fmt::print("{} is not getting out of the penalty box\n", players[currentPlayer]);
            isGettingOutOfPenaltyBox = false;
        }
    }
    else
    {
        places[currentPlayer] = places[currentPlayer] + roll;
        if (places[currentPlayer] > 11)
            places[currentPlayer] = places[currentPlayer] - 12;

        fmt::print("{}'s new location is {}\n", players[currentPlayer], places[currentPlayer]);
        fmt::print("The category is {}\n", currentCategory());
        askQuestion();
    }
}

void Game::askQuestion()
{
    if (currentCategory() == "Pop")
    {
        fmt::print("{}\n", popQuestions.back());
        popQuestions.pop_back();
    }
    if (currentCategory() == "Science")
    {
        fmt::print("{}\n", scienceQuestions.back());
        scienceQuestions.pop_back();
    }
    if (currentCategory() == "Sports")
    {
        fmt::print("{}\n", sportsQuestions.back());
        sportsQuestions.pop_back();
    }
    if (currentCategory() == "Rock")
    {
        fmt::print("{}\n", rockQuestions.back());
        rockQuestions.pop_back();
    }
}

string Game::currentCategory()
{
    if (places[currentPlayer] == 0)
        return "Pop";
    if (places[currentPlayer] == 4)
        return "Pop";
    if (places[currentPlayer] == 8)
        return "Pop";
    if (places[currentPlayer] == 1)
        return "Science";
    if (places[currentPlayer] == 5)
        return "Science";
    if (places[currentPlayer] == 9)
        return "Science";
    if (places[currentPlayer] == 2)
        return "Sports";
    if (places[currentPlayer] == 6)
        return "Sports";
    if (places[currentPlayer] == 10)
        return "Sports";
    return "Rock";
}

bool Game::wasCorrectlyAnswered()
{
    if (inPenaltyBox[currentPlayer])
    {
        if (isGettingOutOfPenaltyBox)
        {
            fmt::print("Answer was correct!!!!\n");
            purses[currentPlayer]++;
            fmt::print("{} now has {} Gold Coins.\n", players[currentPlayer], purses[currentPlayer]);

            bool winner = didPlayerWin();
            currentPlayer++;
            if (currentPlayer == players.size())
                currentPlayer = 0;

            return winner;
        }
        else
        {
            currentPlayer++;
            if (currentPlayer == players.size())
                currentPlayer = 0;
            return true;
        }
    }
    else
    {
        fmt::print("Answer was corrent!!!!\n");
        purses[currentPlayer]++;
        fmt::print("{} now has {} Gold Coins.\n", players[currentPlayer], purses[currentPlayer]);

        bool winner = didPlayerWin();
        currentPlayer++;
        if (currentPlayer == players.size())
            currentPlayer = 0;

        return winner;
    }
}

bool Game::wrongAnswer()
{
    fmt::print("Question was incorrectly answered\n");
    fmt::print("{} was sent to the penalty box\n", players[currentPlayer]);
    inPenaltyBox[currentPlayer] = true;

    currentPlayer++;
    if (currentPlayer == players.size())
        currentPlayer = 0;
    return true;
}

bool Game::didPlayerWin()
{
    return !(purses[currentPlayer] == 6);
}