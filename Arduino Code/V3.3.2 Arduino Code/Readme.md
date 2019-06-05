This is V3.3.2 of the Arduino Code

Improvements:
- Weld time can be set down to 1ms (before minimum was 3ms)
- Short Pulse (preheat pulse) percentage can be adjusted down to 0% (0% turns the short pulse off)
- on weld times below 3ms the short pulse (preheat pulse) will be automatically disabled
- battery voltage only updates about every 15 seconds now
- low battery message can be canceled by clicking the rotary encoder
- code is now compatible with the newer Adafruit SSD1306 and GFX library versions
