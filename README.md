# HID Guitar Controller - Converting a Wii Guitar into a Windows Compatible HID Device

## Table of Contents

If your README is long, add a table of contents to make it easy for users to find what they need.

- [Description](#description)
- [Design](#design)
- [What would I do differently? What changes would I make?](#what-would-i-do-differently-what-changes-would-i-make)
- [Installation](#installation)
- [Usage](#usage)
- [Credits](#credits)
- [License](#license)

## Description

Provide a short description explaining the what, why, and how of your project. Use the following questions as a guide:

- What was your motivation?
- Why did you build this project? (Note: the answer is not "Because it was a homework assignment.")
- What problem does it solve?
- What did you learn? 

This project aims to create a device that will take the data from a Wii Guitar Extension Controller and transmit that data to a computer as an HID Device. 

I am a fan of Guitar Hero and rhythm games in general. Guitar Hero was the first rhythm game I ever played and I played it on the Wii using the extension device that came with the game. I long sold the Wii, but I found out that there was a PC version of Guitar Hero called Clone Hero. Since I still had the extension device so I looked into connecting a Wii Remote to a windows computer. While you are able to connect a Wii controller via bluetooth to a Windows Computer it requires the use of third party uncertified drivers. This requires certain settings to turned off in Windows, such as test-signing. The downside of this is that it triggers anti-cheat softwares in competitive video games such as Valorant, making you unable to play those games with the settings turned off. Since these settings require a Computer Restart everytime they are changed, it makes it tedious to switch between games. 

Since I am an electrical engineering major, I decided to make a device that will practically replace the Wii Remote and be able to read the controller inputs from the Wii Guitar Extension Controller and interface with windows as an HID device. I also wanted to make this a battery-powered bluetooth device to remove any cables while using the controller. 

## Design

A lot of information exists on how the Wii works including how the Wii Remote communicates with extension devices such as the Nunchuk or the Wii Guitar. The communication protocol used is a 3.3V I2C signal(s) with nearly all extension devices having an address of 0x52. By default, the data is encrypted but more ‘modern’ extension devices, such as the Wii Guitar, can be set in a decrypted communication mode using the following I2C sequence:

Start, 0xF0, 0x55, Stop, Start, 0xFB, 0x00, Stop

The data is formatted into 6 bytes with the following bit structure with the default bit value being 1 for all of the buttons, changing to 0 when the button is pressed:

(Insert Image Here)
SX and SY refer to the x and y-axis of the analog stick. 
WB refers to the analog whammy bar. 
BD and BU refer to the strum bar. 
BO, BR, BB, BG, and BY refer to the Fretbuttons.
B- and B+ are the final two buttons on the 
TB refer to the analog touch bar which is only found on some Wii Guitars

(Insert Image Here)

The block diagram above shows the basic outline for the circuit that will take in the data from the Wii Guitar and output via Bluetooth. The necessary power systems for battery power are also included. 

The ESP32, specifically the ESP32-WROOM-32D module, was chosen for the microcontroller because of its inbuilt Bluetooth Low Energy (BLE) Capability as well as my prior experience with designing custom boards for it from my Senior Design Class. My previous design already had the USB Controller (USB-to-UART Converter) and the ESP32, so the only thing that needed to be added was a Battery Management System (BMS) and a 3.3V Regulator. While the old 3.3V regulator Circuit would have worked, I did not know that at the time so I used TI’s WeBench to make a circuit capable of inputting 3.5V-5V and outputting a stable 5V. The circuit that was recommended used the TPS63001. The BQ24090 was chosen for the BMS circuit as one of the guides that I found used that IC for their own custom microcontroller. Another circuit that was added to the schematic was a reverse current protection circuit using the LM66100.

(Insert Link to KiCad Schematic & PCB (Make a PDF for both SCH and PCB))

I chose to use a Vertical USB-C connector for two reasons. One is because USB-C is becoming much more common. The second reason is so that in the future, I can attach the board to a piece of acrylic and have the connector flush or near flush with the acrylic once the board is mounted. This idea of mounting is also why I have the programming button and JST connectors (for the battery and connection to the Wii Guitar) on the bottom of the board. Since the USB-C connector is an SMD component, I decided to have all of the SMD components on the same side, but in order for the USB-C to be placed correctly, I needed the other connectors to sit on the other side. Since this was being assembled by hand having all the SMD components on the same side would make it easier to assemble. 

Three libraries are needed to program the board. The first is the Wire library which is needed to communicate with the Wii Guitar via I2C. The second library is LemmingDev’s ESP32-BLE-Gamepad library. This library makes it very easy to turn an ESP32 into a BLE Gamepad that can connect and send data to the computer. The final library that is needed is a dependence for the ESP32-BLE-Gamepad, the NimBLE-Arduino Library. 

## What would I do differently? What changes would I make?



## Installation

What libraries and files are needed for this project?
How do you upload code?

## Usage

Provide instructions and examples for use. Include screenshots as needed.

To add a screenshot, create an `assets/images` folder in your repository and upload your screenshot to it. Then, using the relative filepath, add it to your README using the following syntax:

    ```md
    ![alt text](assets/images/screenshot.png)
    ```

## Credits

List your collaborators, if any, with links to their GitHub profiles.

If you used any third-party assets that require attribution, list the creators with links to their primary web presence in this section.

If you followed tutorials, include links to those here as well.

## License

The last section of a high-quality README file is the license. This lets other developers know what they can and cannot do with your project. If you need help choosing a license, refer to [https://choosealicense.com/](https://choosealicense.com/).

---

🏆 The previous sections are the bare minimum, and your project will ultimately determine the content of this document. You might also want to consider adding the following sections.

## Features

If your project has a lot of features, list them here.

## Tests
