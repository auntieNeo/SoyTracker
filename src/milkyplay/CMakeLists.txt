add_library(milkyplay AudioDriverBase.cpp AudioDriverManager.cpp AudioDriver_NULL.cpp AudioDriver_WAVWriter.cpp ChannelMixer.cpp ExporterXM.cpp LittleEndian.cpp Loader669.cpp LoaderAMF.cpp LoaderAMS.cpp LoaderCBA.cpp LoaderDBM.cpp LoaderDIGI.cpp LoaderDSM.cpp LoaderDTM.cpp LoaderFAR.cpp LoaderGDM.cpp LoaderIMF.cpp LoaderIT.cpp LoaderMDL.cpp LoaderMOD.cpp LoaderMTM.cpp LoaderMXM.cpp LoaderOKT.cpp LoaderPLM.cpp LoaderPSM.cpp LoaderPTM.cpp LoaderS3M.cpp LoaderSTM.cpp LoaderULT.cpp LoaderUNI.cpp LoaderXM.cpp MasterMixer.cpp PlayerBase.cpp PlayerGeneric.cpp PlayerSTD.cpp ResamplerFactory.cpp SampleLoaderAIFF.cpp SampleLoaderALL.cpp SampleLoaderAbstract.cpp SampleLoaderGeneric.cpp SampleLoaderIFF.cpp SampleLoaderWAV.cpp XIInstrument.cpp XMFile.cpp XModule.cpp drivers/alsa/AudioDriver_ALSA.cpp drivers/jack/AudioDriver_JACK.cpp drivers/sdl/AudioDriver_SDL.cpp)

find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})
set(LIBS ${LIBS} ${SDL_LIBRARY})
find_package(SDL_sound REQUIRED)
set(LIBS ${LIBS} ${SDL_SOUND_LIBRARIES})
target_link_libraries(milkyplay ${LIBS})

include_directories(drivers/generic drivers/jack drivers/sdl)
