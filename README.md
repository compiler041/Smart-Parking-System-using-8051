# 🅿️ Smart Car Parking System
### Using 8051 Microcontroller

> Mini-Project Report — Microprocessors and Microcontrollers (Semester IV)  
>**Vaibhav Rathod**


> **Neel Parikh**



> Department of Electronics and Computer Engineering (EXCP) 


> K. J. Somaiya School of Engineering

---

## 📋 Overview

The **Smart Car Parking System** is an embedded systems project built on the **8051 microcontroller** and simulated in the **Proteus ISIS** environment. It manages vehicle entry and exit in a parking lot, dynamically displays available slots on a **16×2 LCD**, and controls a motorized barrier gate via an **L293D motor driver**.

Firmware is written in **Embedded C** using **Keil µVision**, compiled to a HEX file, and loaded directly into the virtual AT89C51 in Proteus for real-time simulation.

---

## 🎯 Problem Statement

Conventional parking systems rely on human attendants to track slot availability — leading to miscounts, vehicles entering full lots, and no real-time feedback for drivers. This project automates the entire process:

- Tracks parking slot availability in real time
- Controls barrier gates for entry and exit
- Immediately notifies users when the lot is full
- Eliminates manual intervention

---

## ⚙️ Key Features

| Feature | Description |
|---|---|
| **Slot Counter** | Tracks available slots in real time (default: 10) |
| **LCD Display** | 16×2 LCD shows slot count or "Parking Full!" message |
| **Gate Control** | L293D H-bridge drives DC motor to open/close barrier |
| **Full Lot Detection** | Entry is blocked in software when slots reach 0 |
| **Debouncing** | 20–50 ms software debounce prevents false button triggers |

---

## 🔧 Hardware Components

- **AT89C51** — 8051-compatible microcontroller (12 MHz crystal)
- **16×2 LCD** — Interfaced in 4-bit mode via Port P1
- **L293D Motor Driver** — Drives DC motor for gate mechanism
- **2× Push Buttons** — Simulate entry and exit (with 10 kΩ pull-up resistors)
- **DC Motor** — Represents the physical barrier gate

### Port Mapping

| Port | Function |
|---|---|
| P1.0, P1.1 | LCD RS and EN control lines |
| P1.4–P1.7 | 4-bit LCD data bus |
| P3.0, P3.1 | Entry and Exit push-button inputs |
| P2.0, P2.1 | L293D direction signals (IN1, IN2) |
| P2.2 | L293D enable pin |

---

## 🧠 Firmware Architecture

The firmware follows a **sequential polling loop**:

```
main()
 ├── Initialize LCD and ports
 ├── Set total_slots = MAX_SLOTS (10)
 └── Loop forever:
     ├── Poll ENTRY button
     │   ├── if pressed AND slots > 0 → decrement slots,
     │   │   open gate, delay, close gate, update LCD
     │   └── if slots == 0 → display "Parking Full"
     └── Poll EXIT button
         ├── if pressed AND slots < MAX → increment slots,
         │   open gate, delay, close gate, update LCD
         └── else → do nothing
```

### LCD Command Routine (4-bit Mode)

```c
void lcd_cmd(unsigned char cmd) {
    P1 = (P1 & 0x0F) | (cmd & 0xF0); // Send upper nibble
    RS = 0; EN = 1; delay_ms(2); EN = 0;
    P1 = (P1 & 0x0F) | (cmd << 4);   // Send lower nibble
    EN = 1; delay_ms(2); EN = 0;
}
```

### Gate Control Routine

```c
void gate_open() {
    IN1 = 1; IN2 = 0; EN = 1;  // Open gate (forward)
    delay_ms(2000);
    IN1 = 0; IN2 = 1;           // Close gate (reverse)
    delay_ms(2000);
    EN = 0;                     // Stop motor
}
```

---

## 🖥️ Simulation Screenshots

<img width="1196" height="839" alt="image" src="https://github.com/user-attachments/assets/da93752c-b761-40aa-a340-0112dc322748" />


---

## 🎬 Simulation Video

▶️ **Watch the full Proteus simulation:**  
[**52_58_Car Parking System — Google Drive**](https://drive.google.com/file/d/1g7VUweEQ0W8Cu2jlatt7fNY2UwYXmItN/view?usp=sharing)

---

## 📊 System States

| Event | Slots Before | Action | LCD Output |
|---|---|---|---|
| Startup | 10 | Initialize | `Smart Parking / Slots: 10` |
| Entry | > 0 | Decrement, open gate | `Smart Parking / Slots: N` |
| Entry | 0 | Block entry | `Parking Full! / Slots: 00` |
| Exit | < 10 | Increment, open gate | `Smart Parking / Slots: N` |
| Exit (after full) | 0 → 1 | Resume normal operation | `Smart Parking / Slots: 01` |

---

## 🧪 MPMC Concepts Demonstrated

- **GPIO Port Configuration** — Bit-addressable and byte-addressable port usage (P1, P2, P3)
- **16×2 LCD Interfacing** — 4-bit mode with custom init, command, and data routines
- **L293D Motor Driver** — Bidirectional DC motor control via H-bridge
- **Polling-Based Input Detection** — Continuous button state monitoring in main loop
- **Software Debouncing** — 20–50 ms delay + re-sample to filter mechanical noise
- **Software Delay Subroutines** — Precise timing for LCD pulses, gate durations, refresh

---

## 🛠️ Tools Used

| Tool | Purpose |
|---|---|
| **Keil µVision** | Embedded C firmware development & HEX compilation |
| **Proteus ISIS 8** | Circuit schematic design & full system simulation |
| **AT89C51 (8051)** | Target microcontroller |

---

## 🚀 Future Enhancements

- Replace push buttons with **IR sensors** or **RFID readers** for contactless detection
- Add **wireless display** or **web dashboard** for remote monitoring
- Integrate **cloud-based management** for multi-lot systems
- Implement **token/ticket printing** at entry

---

## 📁 Repository Structure

```
├── firmware/
│   └── smart_parking.c       # Embedded C source code
├── proteus/
│   └── smart_parking.pdsprj  # Proteus ISIS project file
├── output/
│   └── smart_parking.hex     # Compiled HEX file for AT89C51
└── README.md
```

---

*K. J. Somaiya School of Engineering · EXCP A-3*
