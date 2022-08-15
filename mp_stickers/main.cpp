#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  alma.readFromFile("alma.png");
  
  Image pika;
  pika.readFromFile("pika.png");

  Image miaowa;
  miaowa.readFromFile("miaowa.png");

  Image jieni;
  jieni.readFromFile("jieni.png");

  StickerSheet _stickers(alma, 3);
  _stickers.addSticker(pika, 660, 480);
  _stickers.addSticker(miaowa, 30, 400);
  _stickers.addSticker(jieni, 20, 50);
  Image myImage = _stickers.render();

  myImage.writeToFile("myImage.png");

  return 0;
}
