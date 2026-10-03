# ⏰ Smart Digital Clock with Calendar & EEPROM-Based Alarm

A **PIC18F4580-based digital clock** that displays time and date on a 16x2 LCD. The project supports RTC editing, date-specific alarm setting, and stores alarm settings in the microcontroller's internal EEPROM.

---

## ✨ Features

- Real-time clock display: **HH:MM:SS**
- Calendar display: **DD-MM-YYYY**
- RTC time and date editing
- Date-specific alarm
- Alarm storage using internal EEPROM
- Buzzer indication when alarm matches
- Leap year support
- 3 operating modes
- 3x4 matrix keypad for user input

---

## 🛠️ Technologies Used

- **Microcontroller:** PIC18F4580
- **Language:** Embedded C
- **IDE:** MPLAB X IDE
- **Compiler:** XC8
- **LCD:** 16x2 Character LCD
- **Input:** 3x4 Matrix Keypad
- **Memory:** Internal EEPROM
- **Timer:** Timer0
- **Crystal:** 20 MHz

---

## 🎛️ Operating Modes

**Mode 0 — Normal Clock(Run Mode)**

Displays the current time and date.

    12:30:45
    01-10-2026

**Mode 1 — RTC Edit**

Allows the user to edit:

    Hour → Minute → Second → Date → Month → Year

- SW1 → Increment selected field
- SW2 → Decrement selected field
- SW3 → Select next field
- SW4 → Change operating mode

**Mode 2 — Alarm Edit**

Allows the user to set a date-specific alarm:

    Hour → Minute → Second → Date → Month → Year

- SW1 → Increment selected field
- SW2 → Decrement selected field
- SW3 → Select next field
- SW4 → Change operating mode
- SW5 → Save alarm settings

The alarm is triggered only when **hour, minute, second, date, month, and year** all match the current date and time.

---

## 🔔 Alarm Working

1. Set the alarm date and time using the keypad.
2. Press **SW5** to save the alarm settings.
3. The alarm data is stored in the internal EEPROM.
4. The system continuously checks the current date and time.
5. When all alarm values match the current date and time, the buzzer is activated.
6. Press **SW6** to turn OFF the active buzzer.

---

## 💾 EEPROM Storage

| Address | Stored Data |
|---------|-------------|
| 0 | Alarm Hour |
| 1 | Alarm Minute |
| 2 | Alarm Second |
| 3 | Alarm Date |
| 4 | Alarm Month |
| 5–8 | Alarm Year |
| 9 | Validity Marker `0xAA` |

The validity marker is used to identify whether valid alarm data is stored in EEPROM.

---

## 🔌 Hardware Connections

| Component | PIC18F4580 Pins |
|-----------|------------------|
| LCD Data | PORTD |
| LCD RS | RC1 |
| LCD RW | RC0 |
| LCD EN | RC2 |
| Keypad Rows | RB5–RB7 |
| Keypad Columns | RB1–RB4 |
| Buzzer | RE0 |

---

## 📁 Project Structure

    Smart-Digital-Clock/
    │
    ├── main.c
    ├── alarm.c
    ├── alarm.h
    ├── clcd.c
    ├── clcd.h
    ├── eeprom.c
    ├── eeprom.h
    ├── matrix_keypad.c
    ├── matrix_keypad.h
    ├── rtc.c
    ├── rtc.h
    ├── timer.c
    ├── timer.h
    ├── isr.c
    └── README.md

---

## 📊 Flowchart

    ┌──────────────────┐
    │      START       │
    └────────┬─────────┘
             │
             ▼
    ┌──────────────────────────────┐
    │ Initialize Timer0, LCD,      │
    │ Keypad and Alarm             │
    └────────────┬─────────────────┘
                 │
                 ▼
    ┌──────────────────────────────┐
    │ Load Alarm Settings          │
    │ from Internal EEPROM         │
    └────────────┬─────────────────┘
                 │
                 ▼
          ┌──────────────┐
          │  MAIN LOOP   │◄─────────────────────────────────┐
          └──────┬───────┘                                  │
                 │                                          │
                 ▼                                          │
    ┌──────────────────────────────┐                        │
    │ Read Keypad Input            │                        │
    └────────────┬─────────────────┘                        │
                 │                                          │
                 ▼                                          │
    ┌──────────────────────────────┐                        │
    │ Check Operating Mode         │                        │
    └────────────┬─────────────────┘                        │
                 │                                          │
       ┌─────────┼──────────┐                               │
       │         │          │                               │
       ▼         ▼          ▼                               │
    ┌───────┐ ┌───────┐ ┌───────┐                           │
    │Mode 0 │ │Mode 1 │ │Mode 2 │                           │
    │Normal │ │RTC    │ │Alarm  │                           │
    │Clock  │ │Edit   │ │Edit   │                           │
    └───┬───┘ └───┬───┘ └───┬───┘                           │
        │         │          │                              │
        ▼         ▼          ▼                              │
    Display    SW1 → +    SW1 → +                           │
    Time &     SW2 → -    SW2 → -                           │
    Date       SW3 → Next SW3 → Next                        │
               Field      Field                             │
                          SW5 → Save                        │
                              │                             │
        └─────────┬──────────┴──────────────┐               │
                  │                         │               │
                  ▼                         ▼               │
          ┌──────────────────────────────────────┐          │
          │ Check Current Date & Time Against    │          │
          │ Saved Alarm                          │          │
          └──────────────────┬───────────────────┘          │
                             │                              │
                             ▼                               │
                    ┌─────────────────┐                      │
                    │   Alarm Match?  │                      │
                    └───────┬─────────┘                      │
                            │                                │
                       ┌────┴────┐                           │
                      NO        YES                          │
                       │          │                          │
                       │          ▼                          │
                       │   ┌───────────────┐                 │
                       │   │ Turn ON       │                 │
                       │   │ Buzzer        │                 │
                       │   └───────┬───────┘                 │
                       │           │                         │
                       │           ▼                         │
                       │   ┌────────────────┐                │
                       │   │  SW6 Pressed?  │                │
                       │   └───────┬────────┘                │
                       │           │                         │
                       │      ┌────┴────┐                    │
                       │     NO        YES                   │
                       │      │          │                   │
                       │      │          ▼                   │
                       │      │   ┌──────────────┐           │
                       │      │   │ Turn OFF     │           │
                       │      │   │ Buzzer       │           │
                       │      │   └──────┬───────┘           │
                       │      │          │                   │
                       └──────┴──────────┴───────────────────┘
                                      │
                                      ▼
                                 MAIN LOOP

---

## 🎛️ Switch Functions

| Switch | Function |
|--------|----------|
| **SW1** | Increment selected field |
| **SW2** | Decrement selected field |
| **SW3** | Select next field |
| **SW4** | Change operating mode |
| **SW5** | Save alarm settings |
| **SW6** | Turn OFF active alarm |

---

## ▶️ How to Run

1. Open the project in **MPLAB X IDE**.
2. Select **PIC18F4580** as the target device.
3. Select the **XC8 compiler**.
4. Add all `.c` and `.h` files to the project.
5. Build the project.
6. Program the generated HEX file into the PIC18F4580.
7. Connect the LCD, matrix keypad and buzzer according to the configured pins.
8. Power ON the system.
9. The clock and calendar will be displayed on the LCD.

---

## 🖥️ Output

**Normal Clock (Run Mode)**

    12:30:45
    01-10-2026

**RTC Edit Mode**

    12:30:45 E
    01-10-2026

`E` indicates RTC editing mode and the selected field blinks.

**Alarm Edit Mode**

    06:45:00 A
    05-10-2026

`A` indicates alarm editing mode and the selected field blinks.

**Alarm Trigger**

When the configured date and time match the current date and time:

    ALARM!

The buzzer is activated and can be turned OFF using **SW6**.

---

## 📚 Concepts Demonstrated

- Embedded C programming
- PIC18F4580 programming
- Timer0 interrupts
- Interrupt Service Routine
- 16x2 LCD interfacing
- Matrix keypad interfacing
- Internal EEPROM read/write
- Date and time management
- Leap year calculation
- Modular programming
- Mode-based application development

---

## ⚠️ Challenges

- Implementing timekeeping using Timer0 interrupts
- Managing multiple operating modes
- Handling date and month transitions
- Implementing leap year calculation
- Storing the alarm year in EEPROM
- Comparing both date and time for the alarm
- Handling keypad input while editing different fields

---

## 💡 Key Learnings

- PIC18F4580 microcontroller programming
- Embedded C programming
- Timer0 interrupt handling
- LCD and matrix keypad interfacing
- Internal EEPROM read/write operations
- Date and time management
- Leap year calculation
- Modular and mode-based programming

---

## ✅ Result

Successfully developed a **PIC18F4580-based Smart Digital Clock and Calendar** with RTC editing and a **date-specific EEPROM-based alarm system**.

The system displays the current time and date, allows the user to configure an alarm through the matrix keypad, stores the alarm settings in internal EEPROM, and activates the buzzer when the configured date and time are reached.

---

## 👩‍💻 Author

**Sk Shabeena**

📧 Email: [skshabeena33@gmail.com](mailto:skshabeena33@gmail.com)

🔗 LinkedIn: [Shaik Shabeena](https://www.linkedin.com/in/shaik-shabeena-36a7b933/)

💻 GitHub: [shabeena1703](https://github.com/shabeena1703)
