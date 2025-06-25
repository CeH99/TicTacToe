#include "model.h"
#include <QVariantList>

Model::Model(QObject* parent) : QObject(parent) {
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            arr[i][j] = 0;
}

Model::~Model() {}

void Model::setCell(int row, int col, int value) {
    if (row >= 0 && row < ROW && col >= 0 && col < COL) {
        arr[row][col] = value;
        emit boardChanged();
    }
}

int Model::getCell(int row, int col) const {
    if (row >= 0 && row < ROW && col >= 0 && col < COL) {
        return arr[row][col];
    }
    return -1;
}

QVariant Model::board() const {
    QVariantList outer;
    for (int i = 0; i < ROW; ++i) {
        QVariantList inner;
        for (int j = 0; j < COL; ++j) {
            inner.append(arr[i][j]);
        }
        outer.append(inner);
    }
    return outer;
}


int Model::check_Win()
{
    for (int i = 0; i < 3; i++) {
        // ROWS
        if (arr[i][0] != 0 && arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2]) {
            return arr[i][0]; // 1 / 2
        }
        // COLS
        if (arr[0][i] != 0 && arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i]) {
            return arr[0][i]; // 1 / 2
        }
    }

    // diagonals
    if (arr[0][0] != 0 && arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2]) {
        return arr[0][0]; // 1 / 2
    }

    if (arr[0][2] != 0 && arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0]) {
        return arr[0][2]; // 1 / 2
    }

    // check if there any empty cell
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (arr[i][j] == 0)
                return 0; // continue

    // draw
    return 3;
}

