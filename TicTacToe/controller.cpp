#include "controller.h"

#include <QRandomGenerator>
#include <vector>
#include <utility> // для std::pair

Controller::Controller(Model* model, QObject* parent)
    : QObject(parent), model_(model), switch_(false), aiIsX_(false) {} // Установите true по умолчанию

void Controller::setAiAsX(bool isX) {
    aiIsX_ = isX;
}

void Controller::setIndex(int row, int col, bool player)
{
    if (model_->getCell(row, col) != 0)
        return;

    int currentPlayer = player ? 2 : 1;  // true=O(2), false=X(1)
    model_->setCell(row, col, currentPlayer);

    int result = model_->check_Win();
    if (result != 0) {
        emit gameOver(result);
        return;
    }

    if (aiEnabled_) {
        // Проверяем, нужно ли ИИ делать ход
        bool shouldAiMove = false;

        if (aiIsX_ && currentPlayer == 2) {  // ИИ-крестик, человек походил ноликом
            shouldAiMove = true;
        } else if (!aiIsX_ && currentPlayer == 1) {  // ИИ-нолик, человек походил крестиком
            shouldAiMove = true;
        }

        if (shouldAiMove) {
            makeAiMove();
        }
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
            // При включении ИИ, по умолчанию ИИ играет ноликами
            aiIsX_ = false;
        }
        resetBoard(); // Перезапускаем игру
        emit aiModeChanged();
    }
}

void Controller::makeAiMove()
{
    std::vector<std::pair<int, int>> freeCells;

    // 1. Сбор свободных клеток
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (model_->getCell(i, j) == 0)
                freeCells.emplace_back(i, j);
        }
    }

    if (freeCells.empty()) return;

    // Определяем значения для ИИ и противника
    int aiValue = aiIsX_ ? 1 : 2;        // 1=X, 2=O
    int opponentValue = aiIsX_ ? 2 : 1;   // противоположное значение

    // Вспомогательная лямбда для симуляции хода
    auto tryWinOrBlock = [&](int testValue) -> std::pair<int, int> {
        for (const auto& [r, c] : freeCells) {
            model_->setCell(r, c, testValue);
            if (model_->check_Win() == testValue) {
                model_->setCell(r, c, 0); // откат
                return {r, c};
            }
            model_->setCell(r, c, 0); // откат
        }
        return {-1, -1};
    };

    // 2. Попытка выиграть
    auto [winR, winC] = tryWinOrBlock(aiValue);
    if (winR != -1) {
        setIndex(winR, winC, aiIsX_ ? false : true); // false=X, true=O
        return;
    }

    // 3. Попытка заблокировать противника
    auto [blockR, blockC] = tryWinOrBlock(opponentValue);
    if (blockR != -1) {
        setIndex(blockR, blockC, aiIsX_ ? false : true);
        return;
    }

    // 4. Ходим случайно
    int idx = QRandomGenerator::global()->generate() % static_cast<int>(freeCells.size());
    auto [r, c] = freeCells[idx];
    setIndex(r, c, aiIsX_ ? false : true);
}

void Controller::resetBoard() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            model_->setCell(i, j, 0);

    switch_ = false; // Всегда начинают крестики

    // Если ИИ играет крестиками и включен, делаем первый ход
    if (aiEnabled_ && aiIsX_) {
        makeAiMove();
    }

    emit TurnChanged();
}

void Controller::setFirstPlayer(bool isX) {
    if (aiEnabled_) {
        aiIsX_ = isX;  // Устанавливаем кто из игроков ИИ
    }
    resetBoard();
}

bool Controller::getFirstPlayer() const { return switch_; }








