#ifndef PARACHUTEMODEL_H
#define PARACHUTEMODEL_H

#include <QString>
#include <vector>
#include <QObject>

class ParachuteModel : public QObject {
    Q_OBJECT

public:
    ParachuteModel(int sectors, int tracks);
    void setMessage(const QString& message);
    QString getBinaryMessage() const;
    int getSectors() const;
    int getTracks() const;
    void setSectors(int sectors);
    void setTracks(int tracks);
    std::vector<int> getBinaryMap() const;
    void setReferenceChar(QChar ref);
    QChar getReferenceChar() const;

signals:
    void binaryMapChanged();

private:
    int S, T;
    QString binaryMessage;
    QChar referenceChar = '@';
    std::vector<int> binaryMap;
    void encodeMessage(const QString& message);
};

#endif // PARACHUTEMODEL_H