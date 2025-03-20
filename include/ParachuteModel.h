#ifndef PARACHUTEMODEL_H
#define PARACHUTEMODEL_H

#include <QString>
#include <vector>

class ParachuteModel {
public:
    ParachuteModel(int sectors, int tracks);
    
    void setMessage(const QString& message);
    QString getBinaryMessage() const;
    
    int getSectors() const;
    int getTracks() const;
    void setSectors(int sectors);
    void setTracks(int tracks);

    std::vector<int> getBinaryMap() const;

private:
    int S, T;
    QString binaryMessage;
    std::vector<int> binaryMap;
    
    QString encodeMessage(const QString& message);
};

#endif // PARACHUTEMODEL_H
