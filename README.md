# NEPTR
NEPTR (Never Ending Pie Throwing Robot), a freshman project about a bot that follows you around.

A robotics project inspired by **Adventure Time’s NEPTR**, built during my first semester of Computer Science.  
This custom 3D-printed robot combines **mechanical design, Arduino logic, and sensors** to create a character that can *follow you around and wave hello.*

<div align="center">
  <img src="images/Neptr.jpg" width="450"><br/>
  <em>NEPTR 3D Model – Designed from scratch for motor and sensor integration</em>
</div>

---

##  Features

-  **Animated Arm:** Controlled with a 9g servo motor that waves and gestures.  
-  **Follow Mode:** Two DC motors guided by **ultrasonic sensors** to follow a nearby person.  
-  **LED Illumination:** A yellow LED lights up the compartment — a nod to NEPTR’s “microwave” core.  
-  **Back Display:** 16x2 LCD showing:
  - Elapsed time since activation  
  - Mode switching info  
-  **Button Control:** Switch between **Idle** and **Follow You** modes.  
-  **3D-Printed Body:** Custom-designed to fit electronics and motors seamlessly.  

---

##  Hardware Used

- Arduino board 4.27$
- 4x AAA Batteries 2$ Each (8$)
- LCD screen 2.7$
- 3x Ultrasonic sensors 3.4$ each (10.2$)
- 9G servo motor 3$
- 2 DC motors pack 1.8$
- motor controller 1.5$
- Push Button 0.06$
- Switch 
- Yellow LED 0.1$
- Jumper wires 1$
- Female to Male wires
- 2x Universal Wheels 1$ (2$)
- Solder wire
- Soldering Iron 6.29$


---

##  How It Works

The robot constantly checks distance using ultrasonic sensors.  
If it detects a person within range, it activates the **follow mode**, adjusting both DC motors to track movement.  
The **servo arm** moves periodically to simulate a friendly wave.  
The **LCD** alternates between a timer and “Follow Mode” status when the button is pressed.

---

##  Skills Learned

- Arduino programming (sensors, servos, and motor control)  
- Sensor calibration and analog-to-digital timing  
- 3D design for mechanical fit and cable management  
- Circuit design and prototyping  
- Combining software logic with physical motion  

---

##  Schematic Overview

<div align="center">
  <img src="images/Wiring.jpg" width="450"><br/>
  <em>The NEPTR robot is powered by an **Arduino Uno**, with three ultrasonic sensors, a servo for the waving arm, two DC motors for movement, an LCD for display, and a button for mode switching.</em>
</div>

### 🔌 Pin Connections

| Component | Pin | Description |
|------------|-----|-------------|
| **Servo Motor (Arm)** | D6 | Controls arm waving movement |
| **Ultrasonic Sensor (Front)** | Trig → D8, Echo → D7 | Measures distance ahead |
| **Ultrasonic Sensor (Left)** | Trig → D3, Echo → D2 | Detects objects on the left |
| **Ultrasonic Sensor (Right)** | Trig → D13, Echo → D12 | Detects objects on the right |
| **Motor Driver (L298N)** | IN1 → D4, IN2 → D5, IN3 → D9, IN4 → D10 | Controls two DC motors for motion |
| **LCD (I2C)** | SDA → A4, SCL → A5 | Displays elapsed time and mode |
| **Mode Button** | A3 | Switches between Time and Follow modes |
| **LED (Indicator)** | Any digital pin (e.g., D11) | Glows yellow for "microwave" effect |
| **Power** | 5V / GND | Common power and ground |

###  Control Logic

- **Mode 0:** Displays elapsed time on LCD. Robot stays idle.  
- **Mode 1:** Activates “Follow Mode.”  
  - Uses 3 ultrasonic sensors to locate the nearest object (you).  
  - Moves toward the closest direction (forward, left, or right).  
  - Waves arm when approaching or during idle proximity.  
  - Stops and resets arm when too close (<15 cm).  

###  Behavior Flow

**Button Press → Toggle Mode**

→ **Mode 0:** Timer (Idle)  
  Displays elapsed time on LCD.  

→ **Mode 1:** Follow You Mode  
  • Front sensor drives forward motion  
  • Left/right sensors steer heading  
  • Servo waves near detected user  


---

##  3D Modeling & Design Process

<div align="center">
  <img src="images/3dmodel.png" width="450">
  <img src="images/wiringencased.jpg" width="450"><br/>
  <em>NEPTR 3D Model – Designed from scratch for motor and sensor integration</em>
</div>

Designing NEPTR’s body was one of the most intricate parts of the build.  
Every dimension was measured to ensure that internal components — motors, servo, ultrasonic sensors, LCD, and the LED compartment — fit *snugly and symmetrically*.

###  Modeling Details

- **CAD Software:** Created entirely from scratch using precise metric units for alignment.  
- **Tolerance Calibration:** Each fitting point (motor slots, sensor holes, servo mount) was tested with ±0.2 mm clearance to ensure tight fits without forcing or friction wear.  
- **Internal Space Optimization:** The inner cavity was modeled around the Arduino and L298N driver dimensions, keeping wiring neat and airflow sufficient for safe operation.  
- **Servo Mounting Geometry:** The arm servo sits in a recessed slot to balance torque and maintain clean visual symmetry.  
- **LED and Compartment Design:** A small compartment was modeled to mimic NEPTR’s “microwave” door, internally lit with a warm yellow LED for the characteristic glow.  

The result is a **densely packed, functional miniature robot** that feels engineered rather than assembled.  
It’s not just a printed shell — it’s a structural enclosure tailored to every electronic detail.

<div align="center">
  <img src="images/neptr3drender.png" width="450">
  <img src="images/neptr3drender2.png" width="450"><br/>
  <em>*Note: The full STL and 3D source files are not publicly shared to protect the original design. Photos and renders are provided for educational and reference purposes.*</em>
</div>


##  Notes on Design

- The **servo wave** is a friendly motion to make NEPTR feel alive.  
- The **triple ultrasonic setup** provides rough 3D awareness, enough for basic person-following.  
- The **I2C LCD** uses minimal pins, keeping the build neat and modular.  
- The **L298N motor driver** allows independent wheel control for turning and forward motion.  

---

---

##  Summary

NEPTR brings together **sensor fusion**, **motion control**, and **character design** into one compact, personality-driven bot.  
This project demonstrates a working grasp of:
- Arduino control structures  
- Servo and motor synchronization  
- Real-time sensor-based decision making  
- Embedded UI design with LCD feedback  

---

## Demo

<div align="center">
  <img src="images/neptrdemo.gif" width="450"><br/>
  <em>NEPTR following mode demo</em>
</div>
