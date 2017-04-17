#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    /// Resets the application.
    void resetApp();

    /// Shows information about the author.
    void showAuthorInfo();

    /// Shows information about the application.
    void showAppInfo();

    ~MainWindow();

private slots:
    /// Sets the path to progrma executable.
    void on_btSetExecutable_clicked();

    /// Sets the path to program test examples directory.
    void on_btSetInputExamples_clicked();

    /// Starts the testing of the program.
    void on_btTest_clicked();

private:
    Ui::MainWindow *ui;

    bool allReady() const;
};

#endif // MAINWINDOW_HPP
