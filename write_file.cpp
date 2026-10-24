// write_file.cpp
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
  if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Error: could not open file.";
        return EXIT_FAILURE;
    }

  // treat the file as consuming a data stream
  QDataStream out(&file);

  // Write a header with a magic number and a version
  out << MAGIC;
  out << VERSION;

  // use a specific streaming format
  out.setVersion(QDataStream::Qt_5_0);

  // Create a QList of QStrings
  QList<QString> messages;
  messages.append("Hello World!");
  messages.append("This is Exercise 14.");
  messages.append("Learning QDataStream.");
  messages.append("Writing a QList to a file.");
  
  // Write the list to the file
  out << messages;

  if (out.status() != QDataStream::Ok) {
    qDebug() << "Error: could not write data.";
    return EXIT_FAILURE;
  }

    file.close();
  
  // notify the user that we're finished
  qDebug() << "A data stream has been written to a file.";  
  
  return EXIT_SUCCESS;
}
