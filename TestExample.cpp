#include "TestExample.hpp"

TestExample::TestExample(QString input, QString outputContent)
    : m_inputPath(input), m_outputContent(outputContent)
{
}

QString TestExample::outputContent() const
{
    return m_outputContent;
}

QString TestExample::inputPath() const
{
    return m_inputPath;
}

QString TestExample::str() const
{
    return "in\n" + m_inputPath + "\n\noutput:\n" + m_outputContent;
}
