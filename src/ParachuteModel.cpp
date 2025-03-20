#include "ParachuteModel.h"
#include <QDebug>

ParachuteModel::ParachuteModel(int sectors, int tracks) : S(sectors), T(tracks) {}

int ParachuteModel::getSectors() const { return S; }
int ParachuteModel::getTracks() const { return T; }
void ParachuteModel::setSectors(int sectors) { S = sectors; }
void ParachuteModel::setTracks(int tracks) { T = tracks; }

void ParachuteModel::setMessage(const QString& message) {
    encodeMessage(message);
}

QString ParachuteModel::getBinaryMessage() const {
    return binaryMessage;
}

std::vector<int> ParachuteModel::getBinaryMap() const {
    return binaryMap;
}

QString ParachuteModel::encodeMessage(const QString& message) {
    binaryMap.clear();  // ✅ Reset before filling
    if (message.isEmpty()) {
        qDebug() << "Error: Empty message. Cannot encode.";
        binaryMap.assign(10, 0);
        return "";
    }

    QString binarySequence;
    for (QChar c : message) {
        int value = c.unicode() - 64; // ASCII offset
        QString binaryString = QString("%1").arg(value, 7, 2, QChar('0'));

        for (QChar bit : binaryString) {
            binaryMap.push_back(bit == '1' ? 1 : 0);
        }
    }
    qDebug() << "Binary message size:" << binaryMap.size();  // ✅ Debug binary size
    return binarySequence.trimmed();
}



