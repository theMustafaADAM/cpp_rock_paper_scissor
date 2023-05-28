#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

string myTAB(short NmbrOfTab)
{
    string t = "";
    for (int i = 0; i < NmbrOfTab; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}

enum enTheWinner { UserPlay = 1, Computer = 2, PlayDraw = 3 };

enum enTheChoice { Stone = 1, Paper = 2, Scissor = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    string WinnerName = "";
    enTheChoice UserPlayChoice; enTheChoice ComputerChoice;
    enTheWinner Players_Winner;
};

struct stGameResults
{
    short  Game__Rounds = 0; short  UserPlayWins = 0;
    short  ComputerWins = 0; short  PlayersDraws = 0;
    string Winners_Name = "";
    enTheWinner  GameWinner;
};

short ReadHowManyRounds()
{
    short TheGameRounds = 1;
    do
    {
        cout << "\nEnter how many rounds you want to play: (From 1 To 10 Rounds) \n" << endl;
        cin >> TheGameRounds;
    } while (TheGameRounds < 1 || TheGameRounds > 10);

    return TheGameRounds;
}

short RandomNumbers(short From, short To)
{
    short RNmber = 0;
    RNmber = rand() % (To - From + 1) + From;
    return RNmber;
}

enTheChoice ReadUserChoice()
{
    short UserChoice = 1;
    do
    {
        cout << "\nWhat is Your Choice? [1] Stone, [2] Paper, [3] Scissor "; cin >> UserChoice;
    } while (UserChoice < 1 || UserChoice > 3);
    return (enTheChoice)UserChoice;
}

enTheChoice GetCmputrChoice()
{
    return (enTheChoice)RandomNumbers(1, 3);
}

enTheWinner TheRoundWinners(stRoundInfo RoundInfo)
{
    if (RoundInfo.UserPlayChoice == RoundInfo.ComputerChoice)
        return enTheWinner::PlayDraw;

    switch (RoundInfo.UserPlayChoice) {

    case enTheChoice::Stone:
        if (RoundInfo.ComputerChoice == enTheChoice::Paper)
            return enTheWinner::Computer; break;

    case enTheChoice::Paper:
        if (RoundInfo.ComputerChoice == enTheChoice::Scissor)
            return enTheWinner::Computer; break;

    case enTheChoice::Scissor:
        if (RoundInfo.ComputerChoice == enTheChoice::Stone)
            return enTheWinner::Computer; break;
    }

    return enTheWinner::UserPlay;
}

string TheWinners_Name(enTheWinner TheWinner)
{
    string ArrWinnerName[3] = { "User Play", "Computer", "No Winner, Draw" };
    return ArrWinnerName[TheWinner - 1];
}

string TheChoiceName(enTheChoice TheChoice)
{
    string ArrChoiceName[3] = { "Stone", "Paper", "Scissor" };
    return ArrChoiceName[TheChoice - 1];
}

void SetWinnerScreenColor(enTheWinner TheWinner)
{
    switch (TheWinner) {
    case enTheWinner::UserPlay: system("color 2F"); break;
    case enTheWinner::Computer: system("color 4F"); cout << "\a"; break;
    case enTheWinner::PlayDraw: system("color 6F"); break;
    }
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
    cout << endl;
    cout << "__________Round [ " << RoundInfo.RoundNumber << " ]__________\n\n";
    cout << "User Play Choice: " << TheChoiceName(RoundInfo.UserPlayChoice) << endl;
    cout << "Computer  Choice: " << TheChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Winner Round is:[ " << TheWinners_Name(RoundInfo.Players_Winner) << " ]" << endl;
    cout << "____________________________________________________________\n\n";

    SetWinnerScreenColor(RoundInfo.Players_Winner);
}

enTheWinner TheGameWinner(short UserPlayWins, short ComputerWins)
{
    if (UserPlayWins > ComputerWins)
        return enTheWinner::UserPlay;

    else if (ComputerWins > UserPlayWins)
        return enTheWinner::Computer;

    else
        return enTheWinner::PlayDraw;
}

stGameResults FillGameResult
(short GameRounds, short UserPlayWins, short ComputerWins, short PlayersDraws)
{
    stGameResults GameResults;
    GameResults.Game__Rounds = GameRounds;
    GameResults.UserPlayWins = UserPlayWins;
    GameResults.ComputerWins = ComputerWins;
    GameResults.PlayersDraws = PlayersDraws;
    GameResults.GameWinner = TheGameWinner(UserPlayWins, ComputerWins);
    GameResults.Winners_Name = TheWinners_Name(GameResults.GameWinner);

    return GameResults;
}

stGameResults PlayTheGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;

    short UserPlayWins = 0, ComputerWins = 0, PlayersDraws = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << myTAB(1) << "Round [ " << GameRound << " ] Begains: " << endl;
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.UserPlayChoice = ReadUserChoice();
        RoundInfo.ComputerChoice = GetCmputrChoice();
        RoundInfo.Players_Winner = TheRoundWinners(RoundInfo);
        RoundInfo.WinnerName = TheWinners_Name(RoundInfo.Players_Winner);

        // Incrase Win & Draws Counters
        if (RoundInfo.Players_Winner == enTheWinner::UserPlay)
            UserPlayWins++;
        else if (RoundInfo.Players_Winner == enTheWinner::Computer)
            ComputerWins++;
        else
            PlayersDraws++;

        PrintRoundResult(RoundInfo);
    }
    return FillGameResult(HowManyRounds, UserPlayWins, ComputerWins, PlayersDraws);
}

void ShowGameOverScreen()
{
    cout << myTAB(1) << "_________________________________________________________\n\n";
    cout << myTAB(1) << "              * * * G A M E  O V E R * * * \n";
    cout << myTAB(1) << "_________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << myTAB(1) << "          __________[ The Game Results ]__________\n\n";
    cout << myTAB(1) << "              The Game Rounds  > " << GameResults.Game__Rounds << " ." << endl;
    cout << myTAB(1) << "              User Play  Wons  > " << GameResults.UserPlayWins << " ." << endl;
    cout << myTAB(1) << "              Computer   Wons  > " << GameResults.ComputerWins << " ." << endl;
    cout << myTAB(1) << "              Players   Draws  > " << GameResults.PlayersDraws << " ." << endl;
    cout << myTAB(1) << "              Final Winner is  > " << GameResults.Winners_Name << " ." << endl;
    cout << endl << endl;
    cout << myTAB(1) << "          _______[ STONE PAPER SCISSOR 2022 ]_______\n\n";
}

void ResetMyScreen()
{
    system("cls"); system("color 70");
}

void StartStonePaperScissor()
{
    char playAgain = 'Y';
    do
    {
        ResetMyScreen();

        stGameResults GameResults = PlayTheGame(ReadHowManyRounds());        
                
        ShowGameOverScreen(); ShowFinalGameResults(GameResults);

        cout << endl << myTAB(1) << "Would you like to play one more time? \n\tThe Options [y/Y] Yes [any key] No ";
        cout << endl << myTAB(1); cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartStonePaperScissor();

    return 0;
}
