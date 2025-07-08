#ifndef IFILESERVICE_H
#define IFILESERVICE_H

#include <QString>
#include <QObject>

class IFileService : public QObject
{
    Q_OBJECT

public:
    explicit IFileService(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IFileService() = default;
    
    // File operations
    virtual QString openFile(const QString &fileName) = 0;
    virtual bool saveFile(const QString &fileName, const QString &content) = 0;
    
    // Error handling
    virtual QString getLastError() const = 0;
    virtual void clearError() = 0;
};

#endif // IFILESERVICE_H 