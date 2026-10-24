// read_file.cpp
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QList>
#include <QString>
#include <cstdlib>


#include "file_header.h"

int main(int argc, char *argv[])
{
  QFile file("temp.dat");
  if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: could not open file.";
        return EXIT_FAILURE;
    }
  // Read the file as a data stream
  QDataStream in(&file);
  // Read and check the header
  quint32 magic;
  in >> magic;
  if (magic != MAGIC){
    qDebug() << "Error: unexpected format.";
    return EXIT_FAILURE;
  }

  // Read the version
  qint32 version;
  in >> version;
  if(version != 1){
    qDebug() << "Error: unsupported file version.";
    return EXIT_FAILURE;
  }

  // use the same encoding format
  in.setVersion(QDataStream::Qt_5_0);

  // Read the data
  QList<QString> messages;
  in >> messages;

  if (in.status() != QDataStream::Ok) {
     qDebug() << "Error: could not read data.";
     return EXIT_FAILURE;
  }

  file.close();

  // Print the strings
  qDebug() << "Read data from a file:";

  for (const QString &msg : messages) {
    qDebug() << msg;
  }
  return EXIT_SUCCESS;
}
