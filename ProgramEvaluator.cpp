#include "ProgramEvaluator.hpp"

#include <iostream>
#include <QString>

ProgramEvaluator::ProgramEvaluator()
    : m_successNum(0)
{}

void ProgramEvaluator::registerSuccess(unsigned i)
{
    m_status[i] = true;
    ++m_successNum;
}

void ProgramEvaluator::registerFailure(unsigned i)
{
    m_status[i] = false;
}

void ProgramEvaluator::clearStatus()
{
    m_status.clear();
    m_successNum = 0;
}

void ProgramEvaluator::showStatus() const
{
    for (const auto & pair : m_status) {
        std::cout << "Test " << pair.first+1 << ": ";
        if (pair.second) std::cout << "success!" << std::endl;
        else std::cout << "fail!" << std::endl;
    }
}

bool ProgramEvaluator::getItem(unsigned i) const
{
    if (m_status.count(i))
        return m_status.at(i);
    else {
        qDebug() << "Wrong indexing, no text example numbered " << i;
        return false;
    }
}

double ProgramEvaluator::getPercentage() const
{
    return m_successNum * 1.0 / m_status.size() * 100.0;
}

QString ProgramEvaluator::getItemStr(unsigned i) const
{
    if (! m_status.count(i))  {
        qDebug() << "Wrong indexing, no text example numbered " << i;
        return "null";
    }

    if (m_status.at(i))
        return "Test " + QString::number(i) + " success!";
    else
        return "Test " + QString::number(i) + " fail!";
}

unsigned ProgramEvaluator::getTestSize() const
{
    return m_status.size();
}

unsigned ProgramEvaluator::getSuccessfulTestNum() const
{
    return m_successNum;
}

unsigned ProgramEvaluator::getFailedTestNum() const
{
    return m_status.size() - m_successNum;
}

QString ProgramEvaluator::getScoreList() const
{
    QString tmp = "";

    for (unsigned i = 0; i < m_status.size(); i++)
        tmp += getItemStr(i) + "\n";

    return tmp;
}

QString ProgramEvaluator::getScoreFraction() const
{
    return "Overall: " + QString::number(m_successNum) + "/" + QString::number(m_status.size());
}

QString ProgramEvaluator::getScorePercent() const
{
    return "Overall: " + QString::number(getPercentage()) + "%";
}

QStringList ProgramEvaluator::getScoreQStringList() const
{
    QStringList l;

    for (unsigned i = 0; i < m_status.size(); i++)
        l << getItemStr(i) + "\n";

    return l;
}
