#ifndef SCS_H
#define SCS_H

#include <QMainWindow>
#include "input.h"

namespace Ui {
class SCS;
}

class SCS : public QMainWindow
{
    Q_OBJECT

public:
    explicit SCS(QWidget *parent = 0);
    ~SCS();

private slots:
    void on_solve_clicked();

    void on_section_textChanged();

    void on_output_clicked();

    void on_actionNew_triggered();

    void on_actionSave_as_triggered();

    void on_actionSave_triggered();

    void on_actionImport_triggered();

private:
    Ui::SCS *ui;
    QVector<QSharedPointer<fiber> > m_psec;
    QVector<QVector<double> > m_M_phi;
};

#endif // SCS_H
