#ifndef MYAES_H
#define MYAES_H
#include <QTemporaryFile>
void EncryptFile();
void DectyptFile();
class tempfile{
public:
    static QTemporaryFile tp1;
};

#endif // MYAES_H

