#ifndef TESTEXAMPLE_HPP
#define TESTEXAMPLE_HPP

#include <QDebug>
#include <vector>

class TestExample {
public:
    /// Constructs a test example where:
    /// 'inputPath' is a path to input for the program;
    /// 'outputContent' is the correct output of the program.
    TestExample(QString inputPath, QString outputContent);

    /// Returns the path to the input test example.
    QString inputPath() const;

    /// Returns the content of the output test example.
    QString outputContent() const;

    /// Returns a string representation of the test example.
    QString str() const;

private:
    /// Input path to the input test example.
    /// Input path is used instead of contents of the file,
    /// because program tester redirects program input to this path.
    QString m_inputPath;

    /// Content of the output test example.
    /// Content is compared to the content written to standard output
    /// by the program that should be tested.
    QString m_outputContent;
};

#endif // TESTEXAMPLE_HPP
