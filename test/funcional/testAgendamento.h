#ifndef TESTAGENDAMENTO_H
#define TESTAGENDAMENTO_H

#include <QtTest>
#include <QCoreApplication>
#include <QPushButton>
#include <QCalendarWidget>
#include <QMessageBox>
#include <QTimer>

class TestAgendamento : public QObject {
    Q_OBJECT

private slots:
    void testFluxoAgendamentoCompleto();
};

#endif