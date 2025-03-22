//
// Created by Semuel Leijten on 18/03/2025.
//

#include "CustomOscServer.h"

CustomOscServer::CustomOscServer() : m_oscMessage(0){}

CustomOscServer::~CustomOscServer(){}

float CustomOscServer::getOscMessage(){
  return m_oscMessage;
}

int CustomOscServer::realcallback(const char *path,const char *types,
                                  lo_arg **argv,int argc) {
    std::string msgpath=path;
    if(!msgpath.compare("/breath")){
        m_oscMessage = argv[0]->f;
    }
    return 0;
}