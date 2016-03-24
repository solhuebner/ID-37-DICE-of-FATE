/*
  DICE SIM: http://www.team-arg.org/dice-manual.html

  Arduboy version 0.1:  http://www.team-arg.org/dice-downloads.html

  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

  2016 JO3RI - CASTPIXEL

  License: MIT : https://opensource.org/licenses/MIT

*/

#include "Arglib.h"
#include "menu.h"
#include "game.h"
#include "inputs.h"

//determine the game
#define GAME_ID 37

Arduboy arduboy;

typedef void (*FunctionPointer) ();
FunctionPointer mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuHelp,
  stateMenuPlay,
  stateMenuInfo,
  stateMenuSoundfx,
  stateDiceTypeAndAmount,
  stateDiceRolling,
  stateDiceResult,
};

byte gameState;

void setup()
{
  arduboy.start();
  arduboy.setFrameRate(60);
  gameState = STATE_MENU_INTRO;
  if (EEPROM.read(EEPROM_AUDIO_ON_OFF)) soundYesNo = true;
  menuSelection = STATE_MENU_PLAY;
  Serial.begin(9600);
}

void loop()
{
  if (!(arduboy.nextFrame())) return;
  buttons.poll();
  if (soundYesNo == true) arduboy.audio.on();
  else arduboy.audio.off();
  arduboy.clearDisplay();
  mainGameLoop[gameState]();
  arduboy.display();
}
