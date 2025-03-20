#ifndef PARACHUTEMODEL_H
#define PARACHUTEMODEL_H

#include <QString>
#include <vector>
#include <QObject>  // ✅ Needed for signals

class ParachuteModel : public QObject {
    Q_OBJECT  // ✅ Make it a Qt Object to use signals

public:
    ParachuteModel(int sectors, int tracks);

    void setMessage(const QString& message);
    QString getBinaryMessage() const;

    int getSectors() const;
    int getTracks() const;
    void setSectors(int sectors);
    void setTracks(int tracks);

    std::vector<int> getBinaryMap() const;

signals:
    void binaryMapChanged();  // ✅ Signal to update the parachute view

private:
    int S, T;
    QString binaryMessage;
    std::vector<int> binaryMap;

    void encodeMessage(const QString& message);  // ✅ Now a `void` function
};

#endif // PARACHUTEMODEL_H
