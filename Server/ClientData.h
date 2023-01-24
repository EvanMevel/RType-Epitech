//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_CLIENTDATA_H
#define R_TYPE_SERVER_CLIENTDATA_H


class ClientData {
private:
    long long lastPing;
public:
    ClientData();
    virtual ~ClientData() = default;

    long long int getLastPing() const;

    void setLastPing(long long int lastPing);
};


#endif //R_TYPE_SERVER_CLIENTDATA_H
