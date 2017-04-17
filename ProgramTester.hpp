#ifndef PROGRAMTESTER_HPP
#define PROGRAMTESTER_HPP

#include <QString>
#include <memory>
#include <array>

#include "TestExample.hpp"
#include "ProgramEvaluator.hpp"

class ProgramTester {
public:
    /// Constructs a program tester object.
    /// 'programExecutablePath' is a path to the program executable.
    /// 'testExamples' is a path do directory that contains test examples.
    ProgramTester(QString programExecutablePath, QString testExamples);

    /// Returns the executable path.
    QString programExecutablePath() const;

    /// Returns the path to directory containing test examples.
    QString testExamples() const;

    /// Runs the given command 'cmd' and returns its output as QString.
    QString exec(std::string cmd);

    /// Performs testing of program executable with test examples.
    /// Returns an evaluator object that has all information relevant for testing.
    ProgramEvaluator performTest();

    /// Reads content from file on path 'path' and returns content.
    QString readData(QString path);

private:
    /// Path to program executable.
    QString m_programExecutable;

    /// Path to directory containing test examples.
    QString m_testExamples;
};

#endif // PROGRAMTESTER_HPP
