//
// Created by Nuno Levezinho on 07/02/2018.
//

#include <Locator.h>
#include <Audio/DesktopAudioPlayer.h>
#include <FileSystem/DesktopFileSystem.h>
#include <Logger/DesktopLogger.h>
#include "Game.hpp"

int main() {

    srand(static_cast<unsigned int>(time(nullptr)));

    av::Locator::Initialize();
    av::Locator::Provide(new av::DesktopLogger());
    av::Locator::Provide(new av::DesktopAudioPlayer());
    av::Locator::Provide(new av::DesktopFileSystem());

    av::Game(av::Locator::GetFileSystem().GetConfiguration()).Run();
}
