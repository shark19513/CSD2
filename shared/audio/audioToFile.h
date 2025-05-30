#pragma once
#include "audiocomponent.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sys/stat.h>


class WriteToFile {
public:
  WriteToFile (std::string fileName, bool overwrite = false);
  ~WriteToFile();

  bool write (const std::string& text);

private:
  static bool fileExists (const std::string& fileName);
  bool openFile (const std::string& fileName);
  std::ofstream file;
};


class AudioToFile {
public:
  // TODO: add functionality to set numFrames and channels
  AudioToFile (const std::string& fileName,
               int numInputchannels = 1,
               int numOutputChannels = 1,
               int numFrames = 22049);
  ~AudioToFile();
  // TODO: add functionality to write a given range to file
  void write (AudioCallback& callback);

private:
  std::unique_ptr<WriteToFile> fileWriter;
  std::unique_ptr<AudioBuffer> audioBuffer;

  int numInputChannels = 1;
  int numOutputChannels = 1;
  int numFrames = 256;
  float** inputChannel;
  float** outputChannel;
};
