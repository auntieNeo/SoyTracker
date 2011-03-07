#include <MilkyPlay.h>

int main(int argc, char **argv)
{
  AudioDriverManager *audioDriverManager = new AudioDriverManager();
  if(audioDriverManager->getPreferredAudioDriver() == NULL)
  {
    delete audioDriverManager;
    return 1;
  }
  delete audioDriverManager;
  return 0;
}
