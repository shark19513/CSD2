//
// Created by Semuel Leijten on 18/03/2025.
//

#ifndef CUSTOMOSCSERVER_H
#define CUSTOMOSCSERVER_H

#include "osc.h"

class CustomOscServer : public OSC
{
    public:
    CustomOscServer();
    ~CustomOscServer() override;

    float getOscMessage();

private:
    int realcallback(const char *path,const char *types,
                       lo_arg **argv,int argc) override;

    std::atomic<float> m_oscMessage;
};


#endif //CUSTOMOSCSERVER_H
