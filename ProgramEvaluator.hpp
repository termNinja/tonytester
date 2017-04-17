#ifndef PROGRAMEVALUATOR_HPP
#define PROGRAMEVALUATOR_HPP

#include <QString>
#include <map>
#include <QStringList>

#include "TestExample.hpp"

class ProgramEvaluator {
public:
    /// Constructs a program evaluator.
    /// Users needs to use functions 'registerSuccess' and
    /// 'registerFailure' to register the results of test examples.
    ProgramEvaluator();

    /// Registers that i-th test example has passed a test.
    void registerSuccess(unsigned i);

    /// Registers that i-th test example has failed a test.
    void registerFailure(unsigned i);

    /// Shows the status of ProgramEvaluator to standard output.
    void showStatus() const;

    /// Clears status of the Program Evaluator.
    /// It enables the use of the same object for different evaluation.
    void clearStatus();

    /// Returns true if i-th test example has passed,
    /// false otherwise.
    bool getItem(unsigned i) const;

    /// Returns the success rate in percent.
    double getPercentage() const;

    /// Returns QString representation of the
    /// i-th test example.
    QString getItemStr(unsigned i) const;

    /// Returns the number of test examples.
    unsigned getTestSize() const;

    /// Returns the number of successful test examples.
    unsigned getSuccessfulTestNum() const;

    /// Returns the number of failed test examples.
    unsigned getFailedTestNum() const;

    /// Returns a formatted QString that represents
    /// a list of all test examples and their status.
    QString getScoreList() const;

    /// Returns overall test results in %.
    QString getScoreFraction() const;

    /// Returns overall test results in fraction shape.
    QString getScorePercent() const;

    /// Returns a QStringList of status for all test examples.
    QStringList getScoreQStringList() const;

private:
    /// Contains status of testing for each test example.
    std::map<unsigned, bool> m_status;

    /// The amount of succesful test examples (used to avoid counting).
    unsigned int m_successNum;
};

#endif // PROGRAMEVALUATOR_HPP
