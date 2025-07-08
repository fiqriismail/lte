#include "fileservice.h"
#include "../shared/types/common.h"
#include <QFile>
#include <QTextStream>

FileService::FileService(QObject *parent)
    : IFileService(parent)
{
}

QString FileService::openFile(const QString &fileName)
{
    clearError();
    
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_lastError = "Could not open file: " + fileName;
        return QString();
    }
    
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    
    return content;
}

bool FileService::saveFile(const QString &fileName, const QString &content)
{
    clearError();
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        m_lastError = "Could not save file: " + fileName;
        return false;
    }
    
    QTextStream out(&file);
    out << content;
    file.close();
    
    return true;
}

QString FileService::getLastError() const
{
    return m_lastError;
}

void FileService::clearError()
{
    m_lastError.clear();
} 