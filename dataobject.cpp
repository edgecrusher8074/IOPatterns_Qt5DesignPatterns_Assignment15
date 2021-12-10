#include "dataobject.h"

#include <QDataStream>
#include <QIODevice>
#include <QRandomGenerator>

#include <QDebug>

DataObject::DataObject(QObject *parent) : QObject(parent)
{    
}

void DataObject::simulateData()
{
    int dataCount = QRandomGenerator::global()->bounded(3,13);
    qDebug() << "Creating" << dataCount << "data entries...";

    while(m_data.size() < dataCount)
    {
        m_data << QString("Data: %1").arg(QString::number(m_data.size() + 1));
    }
}

void DataObject::toIODevice(QIODevice *ioDevice)
{
    if(ioDevice == nullptr)
    {
        qCritical() << "toIODevice: ioDevice is nullptr";
        return;
    }

    if(!ioDevice->isWritable())
    {
        qCritical() << "toIODevice: ioDevice is not writeable";
        return;
    }

    QDataStream oStream(ioDevice);
    oStream.setVersion(QDataStream::Qt_5_15);
    for(const auto& d : m_data)
    {
        oStream << d;
    }
}

void DataObject::fromIODevice(QIODevice *ioDevice)
{
    if(ioDevice == nullptr)
    {
        qCritical() << "toIODevice: ioDevice is nullptr";
        return;
    }

    if(!ioDevice->isReadable())
    {
        qCritical() << "toIODevice: ioDevice is not readable";
        return;
    }

    clearData();

    QDataStream iStream(ioDevice);
    iStream.setVersion(QDataStream::Qt_5_15);
    while(!iStream.atEnd())
    {
        QString in;
        iStream >> in;
        m_data << in;
    }
}

const QStringList &DataObject::data() const
{
    return m_data;
}

void DataObject::clearData()
{
    m_data.clear();
}
