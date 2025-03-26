#include "ParachuteModel.h"
#include <QDebug>

ParachuteModel::ParachuteModel(int sectors, int tracks) : S(sectors), T(tracks) {}

int ParachuteModel::getSectors() const { return S; }
int ParachuteModel::getTracks() const { return T; }
void ParachuteModel::setSectors(int sectors) { S = sectors; }
void ParachuteModel::setTracks(int tracks) { T = tracks; }

void ParachuteModel::setMessage(const QString& message) {
    encodeMessage(message);
    emit binaryMapChanged();
}

QString ParachuteModel::getBinaryMessage() const {
    return binaryMessage;
}

std::vector<int> ParachuteModel::getBinaryMap() const {
    return binaryMap;
}

void ParachuteModel::setReferenceChar(QChar ref) { referenceChar = ref; }

QChar ParachuteModel::getReferenceChar() const { return referenceChar; }

void ParachuteModel::encodeMessage(const QString& message) {
    binaryMap.clear();
    binaryMessage.clear();
    if (message.isEmpty()) {
        qDebug() << "Error: Empty message. Cannot encode.";
        binaryMap.assign(S * T, 0);
        binaryMessage = "";
        return;
    }
    int offset = referenceChar.unicode();
    for (QChar c : message) {
        int value = c.unicode() - offset;
        if (value < 0) value = 0;
        QString binaryString = QString("%1").arg(value, 7, 2, QChar('0'));
        for (QChar bit : binaryString) {
            binaryMap.push_back(bit == '1' ? 1 : 0);
            binaryMessage += bit;
        }
    }
}
