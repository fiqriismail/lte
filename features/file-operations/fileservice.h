#ifndef FILESERVICE_H
#define FILESERVICE_H

#include "shared/interfaces/ifileservice.h"

class FileService : public IFileService
{
    Q_OBJECT

public:
    explicit FileService(QObject *parent = nullptr);
    
    // IFileService implementation
    QString openFile(const QString &fileName) override;
    bool saveFile(const QString &fileName, const QString &content) override;
    QString getLastError() const override;
    void clearError() override;

private:
    QString m_lastError;
};

#endif // FILESERVICE_H 