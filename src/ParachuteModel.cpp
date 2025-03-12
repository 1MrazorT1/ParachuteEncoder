#include "../include/ParachuteModel.h"

class ParachuteModel {
    public:
        ParachuteModel(int sectors, int tracks) : S(sectors), T(tracks) {}
        
        QString encodeMessage(const QString& message) {
            QString binarySequence;
            for (QChar c : message) {
                int value = c.unicode() - 64; // ASCII offset
                binarySequence += QString("%1 ").arg(value, 7, 2, QChar('0'));
            }
            return binarySequence.trimmed();
        }
    
        int getSectors() const { return S; }
        int getTracks() const { return T; }
        void setSectors(int sectors) { S = sectors; }
        void setTracks(int tracks) { T = tracks; }
    
    private:
        int S, T;
    };
    