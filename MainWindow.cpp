#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include <QListWidget>
#include <QProgressBar>
#include <cmath>

#include "ProgramTester.hpp"
#include "ProgramEvaluator.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Menu bar actions.
    connect(ui->actionNew_test, &QAction::triggered, this, &MainWindow::resetApp);
    connect(ui->actionAuthor, &QAction::triggered, this, &MainWindow::showAuthorInfo);
    connect(ui->actionApplication, &QAction::triggered, this, &MainWindow::showAppInfo);
}

void MainWindow::resetApp()
{
    ui->leExecutablePath->clear();
    ui->leTestExamples->clear();
    ui->listWidgetLog->clear();
    ui->progressBarTest->setValue(0);
}

void MainWindow::showAuthorInfo()
{
    QMessageBox::information(this, "About author", "Created by Nemanja Micovic.\nContact at: nmicovic@outlook.com");
}

void MainWindow::showAppInfo()
{
    QMessageBox::information(this, "About application", "Simple program tester for dms.rs programming problems.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btSetExecutable_clicked()
{
    // QString base = "/home/termninja/Projects/ProgramTester/tests";
    QString base = QDir::currentPath();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Find executable"), base, tr("Executable files (*.exe *.out *)"));

    fileName = QDir::toNativeSeparators(fileName);

    ui->leExecutablePath->setText(fileName);
    qDebug() << "Input executable: " << fileName;
}

void MainWindow::on_btTest_clicked()
{
    if (! allReady()) return;
    ui->listWidgetLog->clear();

    ProgramTester tester(ui->leExecutablePath->text(), ui->leTestExamples->text());
    ProgramEvaluator eval = tester.performTest();

    unsigned testSize = eval.getTestSize();
    for (unsigned i = 0; i < testSize; i++) {
        QListWidgetItem* it = new QListWidgetItem(eval.getItemStr(i));
        if (eval.getItem(i))
            it->setForeground(Qt::green);
        else
            it->setForeground(Qt::red);
        ui->listWidgetLog->addItem(it);
    }

    ui->progressBarTest->setValue(std::round(eval.getPercentage()));
    ui->listWidgetLog->addItem(eval.getScoreFraction());
}

bool MainWindow::allReady() const
{
    if (ui->leExecutablePath->text().isEmpty()) return false;
    if (ui->leTestExamples->text().isEmpty()) return false;
    return true;
}

void MainWindow::on_btSetInputExamples_clicked()
{
    // QString base = "/home/termninja/Projects/ProgramTester/tests";
    QString base = QDir::currentPath();

    QString dir = QFileDialog::getExistingDirectory(
        this,
        tr("Open Directory with input test examples"),
        base,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    dir = QDir::toNativeSeparators(dir);

    ui->leTestExamples->setText(dir);
    qDebug() << "Input test samples: " << dir;
}
