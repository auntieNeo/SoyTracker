#include "MilkyPlay.h"

int main(int argc, char **argv)
{
  if(argc != 2)
    return 1;

  MasterMixer *mixer = new MasterMixer(48000);
  XModule *module = new XModule();
  PlayerSTD *player = new PlayerSTD(48000);
  module->loadModule(argv[1]);
  player->startPlaying(module);
  mixer->addDevice(player);
  mixer->start();
  while(mixer->isPlaying())
  {
    ;  // hurr, need to call something to get it to "tick"
  }
  delete player;
  delete module;
  delete mixer;

  return 0;
}
