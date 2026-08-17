# Arduino RC Car 🚗

## 🎥 Final Demonstration

> **A fully custom-built Arduino RC car featuring wireless control, a hobby gear motor, TB6612FNG motor driver, 11.1 V LiPo power, servo steering, and Ackermann steering geometry.**

### ▶️ Full RC Car Demonstration

**[WATCH THE FULL DEMONSTRATION →](INSERT-YOUTUBE-LINK-HERE)**

![Final RC Car](images/final-rc-car.jpg)

### What You're Looking At

This is the final result of the project.

The car is controlled wirelessly using an **nRF24L01+ radio system**, with a joystick controlling both propulsion and steering.

* 🎮 **Joystick-controlled acceleration and steering**
* 📡 **nRF24L01+ wireless communication**
* ⚡ **11.1 V 3S LiPo battery**
* ⚙️ **Hobby gear motor**
* 🔄 **TB6612FNG bidirectional motor control**
* 🔧 **Servo-actuated steering**
* 🚗 **Ackermann steering geometry**
* 🧱 **LEGO-based chassis**
* 🛑 **Wireless communication failsafe**

---

# 🛠️ How I Built It

This project wasn't designed perfectly on the first attempt.

It started with a simple question:

> **Can I build my own RC car from individual electrical and mechanical components?**

The answer turned into a series of engineering problems.

The final car went through several major iterations:

```text
Simple DC Motor
      ↓
Insufficient Torque
      ↓
Hobby Gear Motor
      ↓
Insufficient Speed
      ↓
11.1 V LiPo Battery
      ↓
Need Reverse Control
      ↓
L293D Motor Driver
      ↓
Excessive Voltage Drop
      ↓
TB6612FNG Motor Driver
      ↓
Need Wireless Control
      ↓
nRF24L01+ Communication
      ↓
Steering Problems
      ↓
Ackermann Steering
      ↓
LEGO Chassis
      ↓
Final RC Car
```

Every major change was made because the previous design exposed a limitation.

That iterative process became the most important part of the project.

---

# 🎯 Project Goals

The goal wasn't simply to make a motor spin.

I wanted to build a complete vehicle while learning how the following systems interact:

**Power → Motor → Motor Driver → Microcontroller → Wireless Communication → Steering → Mechanical Chassis**

The project therefore involved:

* DC motor control
* Motor driver selection
* Power-system design
* PWM control
* Wireless communication
* Embedded programming
* Servo control
* Mechanical prototyping
* Ackermann steering
* System-level troubleshooting

---

# 🚗 The Final System

The final vehicle is divided into two major systems.

### Transmitter

```text
Joystick
   ↓
Arduino
   ↓
nRF24L01+
   ↓
Wireless Communication
```

### RC Car

```text
nRF24L01+
     ↓
Receiver Arduino
     ├──────────────→ TB6612FNG → Gear Motor → Rear Wheels
     │
     └──────────────→ Servo → Ackermann Steering → Front Wheels
```

The transmitter reads the joystick and sends commands wirelessly to the vehicle.

The receiver Arduino then converts those commands into motor and steering outputs.

---

# ⚙️ The Engineering Journey

## 1. Starting With a Basic DC Motor

The project originally started with a simple **6–12 V DC motor**.

The first objective was straightforward:

> **Get an Arduino to control a motor.**

I initially used a transistor switching circuit:

```text
Arduino
   │
   ↓
NPN Transistor
   │
   ↓
DC Motor
   │
   ↓
Battery
```

This allowed the Arduino to control the motor without driving the motor directly from an Arduino output.

However, once the motor was connected to the vehicle, the first major problem appeared:

### The motor didn't have enough torque.

The motor could spin, but it struggled to provide enough torque to move the vehicle effectively.

That meant the problem wasn't simply electrical.

It was mechanical.

---

# ⚙️ 2. Switching to a Hobby Gear Motor

To solve the torque problem, I switched to a **hobby gear motor**.

The gearbox reduces the motor's rotational speed while increasing the available output torque.

```text
High-Speed Motor
       ↓
   Gear Reduction
       ↓
Lower RPM
Higher Torque
       ↓
     Wheel
```

This was much better suited to the vehicle.

The car could now actually move under load.

But there was another problem:

### It was too slow.

The gear reduction gave me the torque I needed, but I now needed to increase the vehicle's speed.

---

# 🔋 3. Upgrading to an 11.1 V LiPo

The next major upgrade was the power system.

I purchased an **11.1 V 3S LiPo battery** to provide more voltage and significantly more available power than the earlier battery setup.

The design became:

```text
11.1 V LiPo
     ↓
Motor Driver
     ↓
Gear Motor
     ↓
Wheels
```

The combination of:

**Gear reduction + higher motor voltage**

gave the vehicle a much better balance between torque and speed.

This was one of the first major examples of how changing one part of the system affected the entire vehicle.

---

# 🔄 4. From Transistor Control to the L293D

The transistor circuit was useful for basic motor switching, but I needed the motor to run in **both directions**.

An RC car obviously needs:

```text
FORWARD
   ↑
   │
 STOP
   │
   ↓
REVERSE
```

So I moved to an **L293D H-bridge motor driver**.

The system changed from:

```text
Arduino → Transistor → Motor
```

to:

```text
Arduino → L293D → Motor
```

The L293D allowed the Arduino to control the motor's direction.

This was a major step toward making the system behave like an actual RC vehicle.

---

# ⚡ 5. Discovering the L293D Voltage-Drop Problem

The L293D solved the direction problem, but testing revealed another limitation.

The L293D has a relatively large voltage drop across its output stage.

That meant:

```text
Battery Voltage
      ↓
    L293D
      ↓
Voltage Lost
      ↓
Lower Motor Voltage
      ↓
Reduced Motor Performance
```

Since I was already trying to get as much performance as possible from the 11.1 V battery, losing a significant amount of voltage across the motor driver was not ideal.

So I redesigned the motor-control system again.

---

# 🔥 6. Switching to the TB6612FNG

I replaced the L293D with a **TB6612FNG motor driver**.

The TB6612FNG uses MOSFET-based outputs with significantly lower ON-resistance than the L293D architecture, making it much better suited to this application.

The final motor-control system became:

```text
Arduino
   ↓
TB6612FNG
   ↓
Hobby Gear Motor
   ↓
Rear Wheels
```

The TB6612FNG also allowed me to implement:

* Forward
* Reverse
* PWM speed control
* Braking
* Standby control

This became the final propulsion system.

---

# 📡 7. Adding Wireless Communication

Once the motor system worked, I needed a way to actually control the vehicle remotely.

I chose the **nRF24L01+ 2.4 GHz transceiver**.

The system became:

```text
REMOTE CONTROLLER                  RC CAR

Joystick                           nRF24L01+
   ↓                                   ↓
Arduino                           Arduino
   ↓                                ↙     ↘
nRF24L01+                      TB6612FNG   Servo
   │                               ↓        ↓
   └──── Wireless Link ─────── Gear Motor  Steering
```

The joystick provided two control axes:

**X-axis → Steering**

**Y-axis → Motor**

The transmitter Arduino continuously read the joystick and sent the control values to the vehicle.

---

# 🛑 8. Building a Radio Failsafe

Wireless communication introduced a new problem:

### What happens if the radio connection is lost?

During testing, a disconnected or invalid joystick signal could produce unexpected values.

For example:

```text
X = 1023
Y = 1023
```

If those values were interpreted as legitimate commands, the vehicle could unexpectedly steer or drive.

So I added a communication failsafe.

```text
Valid Radio Packet
       ↓
Normal Operation


No Valid Packet
       ↓
Communication Timeout
       ↓
Failsafe
       ↓
Motor STOP
```

This was an important step because the project was no longer just about making the car work.

It was about making the car **fail safely**.

---

# 🧱 9. Building the LEGO Chassis

The physical chassis was constructed primarily using **LEGO components**.

This made rapid prototyping much easier.

Instead of permanently fabricating every component, I could quickly change:

* Motor placement
* Wheel position
* Chassis dimensions
* Steering geometry
* Battery placement
* Electronics mounting

The LEGO structure therefore became the physical platform on which the electrical and mechanical systems could be integrated.

---

# 🔧 10. Designing Ackermann Steering

Steering became one of the largest mechanical challenges.

Simply turning both front wheels by the same angle isn't ideal for a vehicle.

During a turn, the inner wheel needs to turn through a larger angle than the outer wheel.

```text
           FRONT

       / Inner
      /
     /
    /________________
                   \
                    \ Outer

              TURN →
```

In simplified form:

```text
δ_inner > δ_outer
```

This is the basic principle of **Ackermann steering geometry**.

I therefore built a mechanical linkage that allowed the servo to control the front wheels while producing the required steering relationship.

The servo became the steering actuator:

```text
Joystick
   ↓
Arduino
   ↓
Servo
   ↓
Steering Linkage
   ↓
Front Wheels
```

---

# 🏎️ Final Electrical Architecture

```text
                    ┌─────────────────┐
                    │  11.1 V LiPo   │
                    └────────┬────────┘
                             │
                             ▼
                    ┌─────────────────┐
                    │   TB6612FNG     │
                    │  Motor Driver   │
                    └────────┬────────┘
                             │
                             ▼
                    ┌─────────────────┐
                    │ Hobby Gear Motor│
                    └────────┬────────┘
                             │
                             ▼
                       Rear Wheels


Joystick
   │
   ▼
┌──────────────┐
│ Transmitter  │
│   Arduino    │
└──────┬───────┘
       │
       ▼
┌──────────────┐
│  nRF24L01+   │
└──────┬───────┘
       │
       │ 2.4 GHz Wireless Link
       │
       ▼
┌──────────────┐
│  nRF24L01+   │
└──────┬───────┘
       │
       ▼
┌──────────────┐
│   Receiver   │
│    Arduino   │
└──────┬───────┘
       │
       ├───────────────→ TB6612FNG
       │
       └───────────────→ Servo
                              │
                              ▼
                       Ackermann Steering
```

---

# 📊 Design Evolution

| Problem               | Initial Solution    | Limitation               | Final Solution     |
| --------------------- | ------------------- | ------------------------ | ------------------ |
| Insufficient torque   | Basic DC motor      | Not enough wheel torque  | Hobby gear motor   |
| Insufficient speed    | Gear motor          | Vehicle too slow         | 11.1 V LiPo        |
| No reverse control    | Transistor          | One-direction control    | L293D              |
| Voltage loss          | L293D               | Significant voltage drop | TB6612FNG          |
| No remote control     | Manual/wired        | Limited mobility         | nRF24L01+          |
| Lost radio connection | Continuous commands | Unsafe behavior          | Failsafe           |
| Poor steering         | Basic linkage       | Poor geometry            | Ackermann steering |
| Chassis prototyping   | Rigid construction  | Difficult to modify      | LEGO chassis       |

---

# 📐 Project Documentation

The following diagrams document the system and its development.

### Development Flowchart

![Development Flowchart](diagrams/PROJECT-DEVELOPMENT-FLOWCHART.png)

### Final System Block Diagram

![System Block Diagram](diagrams/FINAL-SYSTEM-BLOCK-DIAGRAM.png)

### Motor Control Evolution

![Motor Control Evolution](diagrams/MOTOR-CONTROL-EVOLUTION.png)

### Final Electrical Schematic

![Final Electrical Schematic](diagrams/FINAL-ELECTRICAL-SCHEMATIC.png)

### Ackermann Steering Geometry

![Ackermann Steering](diagrams/ACKERMANN-STEERING-DIAGRAM.png)

---

# 💻 Software

The software is divided into two Arduino programs.

## Transmitter

The transmitter:

1. Reads the joystick.
2. Applies the appropriate mapping/dead zone.
3. Creates a command packet.
4. Sends the packet through the nRF24L01+.

```text
Joystick
   ↓
Analog Input
   ↓
Mapping / Dead Zone
   ↓
Command Packet
   ↓
nRF24L01+
```

## Receiver

The receiver:

1. Receives the wireless packet.
2. Processes the joystick commands.
3. Determines motor direction and speed.
4. Controls the TB6612FNG.
5. Maps steering commands to the servo.
6. Monitors communication.
7. Activates the failsafe if communication is lost.

---

# 🧪 Testing & Troubleshooting

The majority of the project consisted of testing and solving problems.

Some of the major problems encountered were:

### Motor

* Insufficient torque
* Insufficient speed
* Motor performance under load
* Battery limitations

### Motor Driver

* One-direction control
* L293D voltage drop
* Driver replacement
* PWM speed control

### Wireless

* Communication loss
* Invalid joystick values
* Unexpected control commands
* Failsafe implementation

### Steering

* Servo torque
* Mechanical resistance
* Steering geometry
* Wheel alignment
* Ackermann linkage

### Mechanical

* Chassis rigidity
* Motor mounting
* Battery placement
* Wheel alignment
* Steering linkage

Each problem resulted in a redesign, modification, or software improvement.

---

# 🧠 What I Learned

This project taught me that building an electromechanical system is an **iterative engineering process**.

The final vehicle wasn't created by selecting the perfect components from the beginning.

Instead:

```text
BUILD
  ↓
TEST
  ↓
FIND LIMITATION
  ↓
UNDERSTAND WHY
  ↓
REDESIGN
  ↓
TEST AGAIN
  ↓
INTEGRATE
```

The most important lessons I learned were:

* Motor torque and speed must be considered together.
* Gear reduction can dramatically increase usable wheel torque.
* Battery voltage has a direct impact on motor performance.
* Motor-driver losses matter in battery-powered systems.
* Wireless communication systems must account for communication failure.
* Mechanical design is just as important as electrical design.
* Ackermann steering provides better steering geometry than simply rotating both wheels equally.
* Rapid prototyping makes mechanical iteration much easier.
* Testing often reveals problems that aren't obvious during the initial design.

---

# 🛠️ Skills Demonstrated

### Electrical Engineering

* DC motor control
* H-bridge motor drivers
* PWM
* Power distribution
* Battery selection
* Voltage-drop analysis
* Motor driver selection
* Inductive-load considerations

### Embedded Systems

* Arduino
* C/C++
* Analog input processing
* PWM
* Servo control
* Failsafe programming
* State-based control

### Wireless Communication

* nRF24L01+
* 2.4 GHz communication
* Packet-based communication
* CRC/error detection
* Acknowledgement
* Communication timeout handling

### Mechanical Engineering

* Gear reduction
* Torque analysis
* Chassis design
* Wheel alignment
* Servo linkage
* Ackermann steering
* Mechanical prototyping

### Engineering Design

* Iterative prototyping
* Troubleshooting
* Hardware selection
* System integration
* Failure analysis
* Design optimization

---

# 📁 Repository Structure

```text
RC-Car/
│
├── README.md
│
├── transmitter/
│   └── transmitter.ino
│
├── receiver/
│   └── receiver.ino
│
├── diagrams/
│   ├── PROJECT-DEVELOPMENT-FLOWCHART.png
│   ├── FINAL-SYSTEM-BLOCK-DIAGRAM.png
│   ├── MOTOR-CONTROL-EVOLUTION.png
│   ├── FINAL-ELECTRICAL-SCHEMATIC.png
│   ├── TRANSMITTER-SCHEMATIC.png
│   ├── RECEIVER-SCHEMATIC.png
│   └── ACKERMANN-STEERING-DIAGRAM.png
│
└── images/
    ├── final-rc-car.jpg
    ├── transmitter.jpg
    ├── receiver-electronics.jpg
    ├── lego-chassis.jpg
    └── ackermann-steering.jpg
```

---

# 🔩 Components

| Component        | Purpose                |
| ---------------- | ---------------------- |
| Arduino Uno      | Microcontroller        |
| nRF24L01+        | Wireless communication |
| Joystick         | User input             |
| TB6612FNG        | Motor driver           |
| Hobby Gear Motor | Propulsion             |
| Servo Motor      | Steering               |
| 11.1 V 3S LiPo   | Motor power            |
| LEGO Components  | Chassis                |
| Wheels           | Vehicle movement       |
| Capacitors       | Power decoupling       |

---

# 🚀 Final Result

What started as a simple attempt to control a DC motor became a complete wireless RC vehicle.

The final system combines:

**Embedded Systems**

*

**Power Electronics**

*

**Wireless Communication**

*

**Motor Control**

*

**Mechanical Design**

*

**Vehicle Steering**

into one integrated project.

The most valuable part of the project wasn't simply getting the car to drive.

It was learning how to identify a limitation, understand its cause, select a better solution, test it, and integrate it into the larger system.

### **Build → Test → Diagnose → Redesign → Repeat**

That was the engineering process behind the RC car.
