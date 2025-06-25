#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QWidget>

#include "model.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool turn READ getTurn NOTIFY TurnChanged)
    Q_PROPERTY(bool aiEnabled READ isAiEnabled WRITE setAiEnabled NOTIFY aiModeChanged)

private:
    Model* model_;
    bool switch_;
    bool aiEnabled_;
    bool aiIsX_;

public:
    void setAiAsX(bool isX);
    bool isAiAsX() const { return aiIsX_; }
    bool getFirstPlayer() const;
    explicit Controller(Model* model, QObject* parent = nullptr);
    Q_INVOKABLE void setIndex(int row, int col, bool player);
    Q_INVOKABLE QString getIndex(int row, int col);
    Q_INVOKABLE bool getTurn();
    Q_INVOKABLE int checkWin();
    Q_INVOKABLE void resetBoard();
    bool isAiEnabled() const;
    Q_INVOKABLE void setAiEnabled(bool enabled);
    void makeAiMove();
    Q_INVOKABLE void setFirstPlayer(bool isX);

signals:
    void aiModeChanged();
    void TurnChanged();
    void gameOver(int result);  // 1 - Player 1 wins, 2 - Player 2 wins, 3 - draw
    void firstPlayerChanged();

};

#endif // CONTROLLER_H
