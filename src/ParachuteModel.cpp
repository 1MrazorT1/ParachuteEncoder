#include "ParachuteModel.h"
#include <QDebug>

ParachuteModel::ParachuteModel(int sectors, int tracks) : S(sectors), T(tracks) {}

int ParachuteModel::getSectors() const { return S; }
int ParachuteModel::getTracks() const { return T; }
void ParachuteModel::setSectors(int sectors) { S = sectors; }
void ParachuteModel::setTracks(int tracks) { T = tracks; }

void ParachuteModel::setMessage(const QString& message) {
    encodeMessage(message);  // ✅ Encode the message
    emit binaryMapChanged(); // ✅ Notify UI that binary data changed
}

QString ParachuteModel::getBinaryMessage() const {
    return binaryMessage;
}

std::vector<int> ParachuteModel::getBinaryMap() const {
    return binaryMap;
}

void ParachuteModel::encodeMessage(const QString& message) {
    binaryMap.clear();  // ✅ Reset before filling
    binaryMessage.clear(); // ✅ Also clear binaryMessage before refilling

    if (message.isEmpty()) {
        qDebug() << "Error: Empty message. Cannot encode.";
        binaryMap.assign(S * T, 0);  // Fill with zeros
        binaryMessage = "";
        return;
    }

    for (QChar c : message) {
        int value = c.unicode() - 64; // ASCII offset
        QString binaryString = QString("%1").arg(value, 7, 2, QChar('0'));

        for (QChar bit : binaryString) {
            binaryMap.push_back(bit == '1' ? 1 : 0);
            binaryMessage += bit;
        }
    }

    qDebug() << "Binary message size:" << binaryMap.size();
}
