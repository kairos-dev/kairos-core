
![Logo](https://i.imgur.com/tEk3mT5.jpg)

Under develompent... 

# Table of Contents

* [Description](#description)

* [Setup](#setup)

* [Team](#team)

* [License](#license)

# Description

KairOS is an open source embedded operating system based on [FreeRTOS](https://www.freertos.org) kernel, meant to be used on embedded devices. Actually, KairOS only works on ESP32 microcontroller, but probably we will port to other devices such as Texas Instruments ARM M4, STM32, and Nordic microcontrollers.

## KairOS Files Architecture

The KairOS Architecture is arranged in the scheme showed below:

| drivers | > | hal | > | lib | > | res |
|:-------:|:--:|:---:|:--:|:---:|:--:|:---:|
| Code you wrote to run your hardware | | KairOS hardware Abstraction | | KairOS libraries | | KairOS Application Framework |
*The structure used may be changed in the future

Basically, to run KairOS in your embedded system you will need to write the code for hardware elements such as bluetooth, display, touch driver, keypad, flash storage, wifi modules, and sensors. And that's it, KairOS is running.
Now you can write your apps as you wish, or run the default apps.

# Setup

Comming soon...

Copy **lvgl_component.mk** to: Libs/lvgl.

## Strategy

Coming soon...

## TODO

Coming soon...

# Team

| <img src="https://github.com/Calebe94.png?size=200" alt="Edimar Calebe Castanho"> | <img src="https://github.com/arturgoms.png?size=200" alt="Artur Gomes"> |
|:---------------------------------------------------------------------------------:|:-----------------------------------------------------------------------:|
| [Edimar Calebe Castanho (Calebe94)](https://github.com/Calebe94)                  | [Artur Gomes (arturgoms)](https://github.com/arturgoms/)                |

## Contributing

Comming soon...

# License

All software is covered under [MIT License](https://opensource.org/licenses/MIT).

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
