# AVR Morse Code Transmitter & Receiver

## 📡 Project Overview

This project implements a **Morse Code Transmitter and Receiver** using two **ATmega2560** microcontrollers. The system allows users to input Morse code through a push button, convert it into ASCII characters, and transmit the data over a **bit-banged UART**. The receiver decodes the incoming data, displays it on a **16×2 I2C LCD**, and provides visual feedback using an LED when the transmission is complete.

---

## 🎯 Features

- Morse code input using a push button
- Dot and dash detection based on press duration
- Morse-to-ASCII conversion using a lookup table
- Software (bit-banged) UART communication at **9600 baud**
- Character display on a **16×2 I2C LCD**
- Special Morse control sequences:
  - `........` → Backspace (`0x08`)
  - `-.-.-.-` → Clear Display (`0x0C`)
  - `.-.-.-` → Transmission Complete (`0x04`)
- LED indication when transmission is complete
- Modular bare-metal AVR implementation

---

## ⚙️ Hardware Requirements

### Transmitter
- ATmega2560 Development Board
- Push Button
- Connecting Wires
- Power Supply

### Receiver
- ATmega2560 Development Board
- 16×2 I2C LCD
- LED
- 220Ω Resistor
- Connecting Wires
- Power Supply

---

## 🛠️ Software Requirements

- AVR-GCC
- AVRDUDE
- Arduino IDE / Microchip Studio (for programming)
- USBasp or compatible AVR programmer

---

## 📂 Repository Structure

```
AVR-Morse-Transmitter-Receiver/
│
├── transmitter/
│   ├── main.c
│   ├── morse.c
│   ├── morse.h
│   ├── timer.c
│   ├── timer.h
│   └── Makefile
│
├── receiver/
│   ├── main.c
│   ├── lcd.c
│   ├── lcd.h
│   ├── uart.c
│   ├── uart.h
│   └── Makefile
│
├── docs/
│   ├── circuit_diagram.png
│   └── block_diagram.png
│
├── LICENSE
└── README.md
```

---

## 🚀 Working Principle

### Transmitter

1. User enters Morse code using the push button.
2. Short press is detected as a **dot (.)**.
3. Long press is detected as a **dash (-)**.
4. The Morse sequence is matched with a lookup table.
5. The corresponding ASCII character or control code is generated.
6. The character is transmitted through a software UART at **9600 baud**.

### Receiver

1. Receives serial data through bit-banged UART.
2. Decodes the received ASCII character.
3. Displays the character on the I2C LCD.
4. Executes control functions when special codes are received:
   - Backspace
   - Clear Display
   - Transmission Complete
5. When transmission is complete:
   - LCD displays **"DONE"**
   - LED turns ON for 1 second

---

## 📡 Morse Control Codes

| Morse Sequence | Function | ASCII Code |
|---------------|----------|------------|
| `........` | Backspace | `0x08` |
| `-.-.-.-` | Clear Display | `0x0C` |
| `.-.-.-` | Transmission Complete | `0x04` |

---

## 🔄 Data Flow

```
Push Button
      │
      ▼
Morse Detection
      │
      ▼
Morse Lookup Table
      │
      ▼
ASCII Character
      │
      ▼
Bit-Banged UART
      │
────────Serial Link────────
      │
      ▼
UART Receiver
      │
      ▼
LCD Display
      │
      ▼
LED Notification
```

---

## 📸 Project Demonstration

Add the following images or GIFs to showcase your project:

- Circuit Diagram
- Hardware Setup
- LCD Output
- Working Demonstration GIF

---

## 🔮 Future Improvements

- Hardware UART implementation
- Interrupt-based Morse detection
- Adjustable Morse speed
- Error detection using checksum
- Wireless communication using Bluetooth or RF modules
- EEPROM storage for transmitted messages

---

## 👨‍💻 Author

**Jesi**

Embedded Systems | AVR Programming | Bare-Metal Development

---

## 📄 License

This project is licensed under the MIT License.
