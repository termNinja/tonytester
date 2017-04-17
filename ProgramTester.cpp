#include "ProgramTester.hpp"

#include <QFileInfo>
#include <QDebug>
#include <QDirIterator>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

#include <vector>
#include <algorithm>
#include <iostream>

#include "TestExample.hpp"
#include "ProgramEvaluator.hpp"

#define SEPARATOR "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="

ProgramTester::ProgramTester(QString programExecutablePath, QString testExamples)
    : m_programExecutable(programExecutablePath), m_testExamples(testExamples)
{
}

QString ProgramTester::testExamples() const
{
    return m_testExamples;
}

QString ProgramTester::exec(std::string cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
            result += buffer.data();
    }
    return QString::fromStdString(result);
}

ProgramEvaluator ProgramTester::performTest()
{
    // Read all input examples and dump them into vector
    std::vector<QString> files;
    QDirIterator itInput(m_testExamples);
    while (itInput.hasNext()) {
        QString tmp = itInput.next();
        if (itInput.fileName() != "" && itInput.fileName() != "." && itInput.fileName() != "..")
            files.push_back(tmp);
    }

    // Make sure we have enough pairs for test examples
    if (files.size() % 2 != 0) {
        throw "Input and output test examples files not matched...";
    }

    // Sort the damn thing
    std::sort(std::begin(files), std::end(files));
    qDebug() << SEPARATOR; qDebug() << "input files:"; qDebug() << SEPARATOR;
    for (const auto & e: files) qDebug() << e;
    qDebug() << SEPARATOR << "\n";


    // Run tests
    std::vector<TestExample> testExamples;
    for (auto it = files.begin(); it != files.end(); it++) {
        // QString inputExample = readData(*it);
        it++;
        QString outputExample = readData(*it);
        testExamples.push_back(TestExample(*(it-1), outputExample));
    }

    // Run example by example
    ProgramEvaluator eval;
    unsigned i = 0;
    for (TestExample & te: testExamples) {
        std::string cmd = m_programExecutable.toStdString() + " < \"" + te.inputPath().toStdString() + "\"";
        std::cout << "exec: " << cmd << std::endl;
        QString output = exec(cmd);

        qDebug() << "Comparing " << output << " with " << te.outputContent();
        if (output.trimmed() == te.outputContent().trimmed())
            eval.registerSuccess(i);
        else
            eval.registerFailure(i);
        i++;
    }
    eval.showStatus();

    return eval;
}

QString ProgramTester::readData(QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
        return "";
    }
    QTextStream in(&file);
    QString tmp = in.readAll();
    file.close();
    return tmp;
}
