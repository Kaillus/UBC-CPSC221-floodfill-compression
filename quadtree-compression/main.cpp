// File:        main.cpp
// Author:      will
// Date:        2019-11-11
// Description: Partial test of PA3 functionality


#include "QTree.h"


void testClear() {
  PNG im1;
  im1.readFromFile("images/small.png");
  QTree t1(im1,10,RGBAPixel(0,0,0));
}


int main()
{
  // read in an image
  PNG im1, result, expected;
  im1.readFromFile("images/small.png");
  // use it to build a Qtree with approximately
  // 200 leaves and with each leaf square framed by
  // a black 1-pixel border
  QTree t1(im1,10,RGBAPixel(0,0,0));
  // write it to a file
  t1.write("images/out-smallFrame.png");

  result.readFromFile("images/out-smallFrame.png");
  expected.readFromFile("images/given-smallFrame.png");
  if (expected == result) cout << "smallFrame \033[1;32mPASSED\033[0;37m" << endl;
  else cout << "smallFrame \033[1;31mFAILED\033[0;37m" << endl;

  // use image to build a balanced QTree
  QTree t1b(im1,10,RGBAPixel(0,0,0),true);
  t1b.write("images/out-smallFrameBal.png");

  result.readFromFile("images/out-smallFrameBal.png");
  expected.readFromFile("images/given-smallFrameBal.png");
  if (expected == result) cout << "smallFrameBal \033[1;32mPASSED\033[0;37m" << endl;
  else cout << "smallFrameBal \033[1;31mFAILED\033[0;37m" << endl;

  // check copy
  QTree t1copy(t1);
  t1copy.write("images/out-smallFrameCopy.png");

  result.readFromFile("images/out-smallFrameCopy.png");
  expected.readFromFile("images/out-smallFrame.png");
  if (expected == result) cout << "smallFrameCopy \033[1;32mPASSED\033[0;37m" << endl;
  else cout << "smallFrameCopy \033[1;31mFAILED\033[0;37m" << endl;

  // check assignment
  t1copy = t1b;
  t1copy.write("images/out-smallFrameBalCopy.png");

  result.readFromFile("images/out-smallFrameBalCopy.png");
  expected.readFromFile("images/out-smallFrameBal.png");
  if (expected == result) cout << "smallFrameBalCopy \033[1;32mPASSED\033[0;37m" << endl;
  else cout << "smallFrameBalCopy \033[1;31mFAILED\033[0;37m" << endl;
  
  // check clear
  testClear();
  
  // read in an image
  PNG im2;
  im2.readFromFile("images/colour.png");
  QTree t2(im2,200,RGBAPixel(0,0,0));
  t2.write("images/out-colourFrame.png");

  result.readFromFile("images/out-colourFrame.png");
  expected.readFromFile("images/given-colourFrame.png");
  if (expected == result) cout << "colourFrame \033[1;32mPASSED\033[0;37m" << endl;
  else cout << "colourFrame \033[1;31mFAILED\033[0;37m" << endl;

  // use image to build a balanced QTree
  QTree t2b(im2,200,RGBAPixel(0,0,0),true);
  t2b.write("images/out-colourFrameBal.png");

  result.readFromFile("images/out-colourFrameBal.png");
  expected.readFromFile("images/given-colourFrameBal.png");
  if (expected == result) cout << "colourFrameBal \033[1;32mPASSED\033[0;37m" << endl;
  else cout << "colourFrameBal \033[1;31mFAILED\033[0;37m" << endl;


  // read in an image
  PNG im3;
  im3.readFromFile("images/ada.png");
  QTree t3(im3,2000);
  t3.write("images/out-ada.png");

  result.readFromFile("images/out-ada.png");
  expected.readFromFile("images/given-ada.png");
  if (expected == result) cout << "ada \033[1;32mPASSED\033[0;37m" << endl;
  else cout << "ada \033[1;31mFAILED\033[0;37m" << endl;

  // use image to build a balanced QTree
  QTree t3b(im3,2000,true);
  t3b.write("images/out-adaBal.png");

  result.readFromFile("images/out-adaBal.png");
  expected.readFromFile("images/given-adaBal.png");
  if (expected == result) cout << "adaBal \033[1;32mPASSED\033[0;37m" << endl;
  else cout << "adaBal \033[1;31mFAILED\033[0;37m" << endl;

  // read in an image
  PNG im4;
  im4.readFromFile("images/geo.png");
  QTree t4(im4,200);
  t4.write("images/out-geo.png");

  result.readFromFile("images/out-geo.png");
  expected.readFromFile("images/given-geo.png");
  if (expected == result) cout << "geo \033[1;32mPASSED\033[0;37m" << endl;
  else cout << "geo \033[1;31mFAILED\033[0;37m" << endl;

  // use image to build a balanced QTree
  QTree t4b(im4,200,true);
  t4b.write("images/out-geoBal.png");

  result.readFromFile("images/out-geoBal.png");
  expected.readFromFile("images/given-geoBal.png");
  if (expected == result) cout << "geoBal \033[1;32mPASSED\033[0;37m" << endl;
  else cout << "geoBal \033[1;31mFAILED\033[0;37m" << endl;


  // read in an image
  PNG im5;
  im5.readFromFile("images/klee.png");
  QTree t5(im5,5000,RGBAPixel(100,100,100));
  t5.write("images/out-kleeFrame.png");

  result.readFromFile("images/out-kleeFrame.png");
  expected.readFromFile("images/given-kleeFrame.png");
  if (expected == result) cout << "kleeFrame \033[1;32mPASSED\033[0;37m" << endl;
  else cout << "kleeFrame \033[1;31mFAILED\033[0;37m" << endl;

  // use image to build a balanced QTree
  QTree t5b(im5,5000,RGBAPixel(100,100,100),true);
  t5b.write("images/out-kleeFrameBal.png");

  result.readFromFile("images/out-kleeFrameBal.png");
  expected.readFromFile("images/given-kleeFrameBal.png");
  if (expected == result) cout << "kleeFrameBal \033[1;32mPASSED\033[0;37m" << endl;
  else cout << "kleeFrameBal \033[1;31mFAILED\033[0;37m" << endl;

  return 0;
}
