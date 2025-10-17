#include "Music.h"

void Music::Load()
{
    if (!m_music.openFromFile("assets/sounds/test.wav"))
        return;
    m_music.setLoop(true);

    m_music.play();
}
