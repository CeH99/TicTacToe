#ifndef MODEL_H
#define MODEL_H

#define ROW 3
#define COL 3

#include <QObject>

class Model : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant board READ board NOTIFY boardChanged)

public:
    explicit Model(QObject* parent = nullptr);
    ~Model();

    void setCell(int row, int col, int value);
    int getCell(int row, int col) const;

    int check_Win();

    QVariant board() const;

signals:
    void boardChanged();

private:
    int arr[ROW][COL];
};

#endif // MODEL_H
