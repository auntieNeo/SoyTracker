#include "MilkyPlay.h"
#include "PlayerSTD.h"
#include "XMFile.h"

int main(int argc, char **argv)
{
  if(argc != 2)
    return 1;

  /*
  AudioDriverManager *audioDriverManager = new AudioDriverManager();
  if(audioDriverManager->getPreferredAudioDriver() == NULL)
  {
    delete audioDriverManager;
    return 1;
  }
  */
  XModule *module = new XModule();
  PlayerSTD *player = new PlayerSTD(48000);
  module->loadModule(argv[1]);
  player->startPlaying(module);
  delete player;
  delete module;
//  delete audioDriverManager;

  

  return 0;
}
