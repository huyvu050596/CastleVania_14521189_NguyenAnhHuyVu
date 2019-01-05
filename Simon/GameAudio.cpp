
#include "GameAudio.h"


int GameAudio::Init_DirectSound(HWND hwnd)
{
    HRESULT result;

    dsound = new GSoundManager();

    result = dsound->Initialize(hwnd, DSSCL_PRIORITY);
    if (result != DS_OK)
    {
		GLTrace("[FAILED] Can not init directx sound");
		return 0;
	}

    result = dsound->SetPrimaryBufferFormat(2, 22050, 16);
    if (result != DS_OK)
    {
		GLTrace("[FAILED] Can not set the primary buffer");
		 return 0;
	}
	GLTrace("Directx Sound has been success init");
    return 1;
}

GSound* GameAudio::LoadSound(char *filename)
{
    HRESULT result;

    GSound *wave;

    result = dsound->Create(&wave, filename);
    if (result != DS_OK)
    {
		GLTrace("[Failed] Can not load sound file");
		 return NULL;
	}
	GLTrace("Sound file has been loaded");
    return wave;
}

void GameAudio::PlaySound(GSound *sound)
{
    sound->Play();
	GLTrace("Sound file has been played");
}

void GameAudio::LoopSound(GSound *sound)
{
    sound->Play(0, DSBPLAY_LOOPING);
}

void GameAudio::StopSound(GSound *sound)
{
    sound->Stop();
}
