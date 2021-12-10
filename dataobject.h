#pragma once

#include <QObject>

class QIODevice;

class DataObject : public QObject
{
    Q_OBJECT
public:
    explicit DataObject(QObject *parent = nullptr);

    void simulateData();
    void toIODevice(QIODevice* ioDevice);
    void fromIODevice(QIODevice* ioDevice);
    const QStringList &data() const;

protected:
    void clearData();

private:
    QStringList m_data;

};

