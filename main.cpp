#include <QCoreApplication>

/**
 * @brief Assignment 10 for Qt5 Design Patterns Tutorial on Udemy.
 * @details Use the QIODevice to store an object.
 * @author edgecrusher8074
 */

#include <dataobject.h>
#include <QTemporaryFile>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto write = [](QFile& file)
    {
      DataObject dO;
      dO.simulateData();

      for(const auto& d : dO.data())
          qInfo() << "to:" <<  d;

      dO.toIODevice(&file);
    };

    auto read = [](QFile& file)
    {
      DataObject dO;
      file.seek(0);
      dO.fromIODevice(&file);
      for(const auto& d : dO.data())
          qInfo() << "from:" <<  d;

    };

    QTemporaryFile testData("testData.txt");
    testData.open();
    write(testData);
    read(testData);
    testData.close();

    return a.exec();
}
