#include "controller.h"

#include <QRandomGenerator>
#include <vector>
#include <utility> // для std::pair

Controller::Controller(Model* model, QObject* parent)
    : QObject(parent), model_(model), switch_(false), aiIsX_(false) {}

void Controller::setAiAsX(bool isX) {
    aiIsX_ = isX;
}

void Controller::setIndex(int row, int col, bool player)
{
    if (model_->getCell(row, col) != 0)
        return;

    int currentPlayer;

    if (aiEnabled_) {
        //in mode with ai human moves with the opposite char
        if (aiIsX_) {
            currentPlayer = 2; // human playes O (2), ai playes X (1)
        } else {
            currentPlayer = 1; // human playes X (1), ai playes O (2)
        }
    } else {
        currentPlayer = player ? 2 : 1;  // true=O(2), false=X(1)
    }

    model_->setCell(row, col, currentPlayer);

    int result = model_->check_Win();
    if (result != 0) {
        emit gameOver(result);
        return;
    }

    if (aiEnabled_) {
        // ai moves after human`s move
        makeAiMove();
    } else {
        switch_ = !switch_;
        emit TurnChanged();
    }
}



QString Controller::getIndex(int row, int col)
{

    if(model_->getCell(row, col) == 0)
    {
        return " ";
    }
    else if(model_->getCell(row, col) == 1)
    {
        return "X";
    }
    else
    {
        return "O";
    }
}

bool Controller::getTurn()
{
    return switch_;
}

int Controller::checkWin()
{
    return model_->check_Win();
}

bool Controller::isAiEnabled() const {
    return aiEnabled_;
}

void Controller::setAiEnabled(bool enabled) {
    if (aiEnabled_ != enabled) {
        aiEnabled_ = enabled;
        if (enabled) {
            // ai - zeros
            aiIsX_ = false;
        }
        resetBoard(); // restart
        emit aiModeChanged();
    }
}

void Controller::makeAiMove()
{
    std::vector<std::pair<int, int>> freeCells;

    // 1. collecting empty cells
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (model_->getCell(i, j) == 0)
                freeCells.emplace_back(i, j);
        }
    }

    if (freeCells.empty()) return;

    int aiValue = aiIsX_ ? 1 : 2;
    int opponentValue = aiIsX_ ? 2 : 1;

    // help func for checking possibility of win
    auto tryWinOrBlock = [&](int testValue) -> std::pair<int, int> {
        for (const auto& [r, c] : freeCells) {
            model_->setCell(r, c, testValue);
            if (model_->check_Win() == testValue) {
                model_->setCell(r, c, 0); // back
                return {r, c};
            }
            model_->setCell(r, c, 0); // back
        }
        return {-1, -1};
    };

    // 2. trying to win
    auto [winR, winC] = tryWinOrBlock(aiValue);
    if (winR != -1) {
        model_->setCell(winR, winC, aiValue);
        // checking win
        int result = model_->check_Win();
        if (result != 0) {
            emit gameOver(result);
        }
        return;
    }

    // 3. blocking enemy
    auto [blockR, blockC] = tryWinOrBlock(opponentValue);
    if (blockR != -1) {
        model_->setCell(blockR, blockC, aiValue);
        // checking win
        int result = model_->check_Win();
        if (result != 0) {
            emit gameOver(result);
        }
        return;
    }

    // 4. random move
    int idx = QRandomGenerator::global()->generate() % static_cast<int>(freeCells.size());
    auto [r, c] = freeCells[idx];
    model_->setCell(r, c, aiValue);

    // checking win again)
    int result = model_->check_Win();
    if (result != 0) {
        emit gameOver(result);
    }
}

void Controller::resetBoard() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            model_->setCell(i, j, 0);

    switch_ = false; // crosses re always first

    if (aiEnabled_ && aiIsX_) {
        makeAiMove();
    }

    emit TurnChanged();
}

void Controller::setFirstPlayer(bool isX) {
    if (aiEnabled_) {
        aiIsX_ = isX;  // setting ai play
    }
    //assert(aiIsX_ == isX && switch_ != isX);
    resetBoard();
}

bool Controller::getFirstPlayer() const { return switch_; }







