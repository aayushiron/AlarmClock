# Arduino Alarm Clock
Code for an alarm clock that can play music files stored on an SD card (designed for the Arduino 
Mega 2560).

## Dependencies
* [Eclipse for C++](https://www.eclipse.org/downloads/packages/release/kepler/sr2/eclipse-ide-cc-developers)
* [Sloeber plugin for Arduino](https://github.com/Sloeber/arduino-eclipse-plugin)
* Arduino libraries:
  * [ArduinoSTL](https://github.com/mike-matera/ArduinoSTL)
  * [ds3231](https://github.com/rodan/ds3231)
  * [SD Library](https://www.arduino.cc/en/Reference/SD)
  * [SPI Library](https://www.arduino.cc/en/Reference/SPI}
  * [TFT_HX8357](https://github.com/Bodmer/TFT_HX8357)
  * [TMRpcm](https://github.com/TMRh20/TMRpcm)
  * [Wire Library](https://www.arduino.cc/en/Reference/Wire)

### Build Instructions (Windows)
1) Install Eclipse for C++
2) Clone this repository to your computer
2) In the Eclipse menu bar, navigate to `File->Open Projects from File System`
3) Open this repository from your computer
4) Download all required Arduino libraries from Dependencies (SD, SPI, and WIRE come preinstalled)
5) Unzip all libraries (if needed) and move them to `Documents->Arduino->libraries`
6) In the Eclipse menu bar, navigate to `Arduino->Add a library to the selected project` and select all libraries in the dependencies list
7) Connect your Arduino Mega 2560 to your computer, make sure the correct COM port is selected, and then click `Arduino->Run Sketch` in the Eclipse menu bar.

## Credits
* Bodmer for the TFT_HX8357 library
* Mike Matera (mike-matera) for the ArduinoSTL library
* TMRh20 for the TMRpcm library
* Petre Rodan (rodan) for the ds3231 library