# 🚗 OnlineCarController

![Project Banner](public/ProjectBanner.webp)

**OnlineCarController** is an experimental project that fuses robotics with web development. It allows you to remotely control the Elegoo Smart Robot 3.0 Plus by combining two powerful technologies:

- **Arduino:** Manages motors, sensors (ultrasonic and infrared), and Bluetooth communication.
- **React:** A web interface (configured with Vite) that uses the experimental Bluetooth feature in Chromium-based browsers to control the robot via keyboard inputs or custom parameters.

---

## 📖 Project Overview

OnlineCarController integrates two key components:

- **Robotic Control:** Uses Arduino and specialized classes to manage the robot's mechanics and sensors.
- **Interactive Web Interface:** A React application that connects via Bluetooth (experimental feature must be enabled in your browser) to send intuitive commands to the robot.

This is my first project combining React and Arduino—a valuable learning and experimental experience.

---

## 🗂️ Repository Structure


OnlineCarController/

    ├── Complete_Car_With_Classes/
    
        (Arduino project: Motor control, sensors, and Bluetooth)
        
    ├── public/
        
        (Public assets for the React app)
        
    ├── src/
        
        (Source code for the React app)
        
    ├── package.json
        
        (React (Vite) configuration and dependencies)
        
    └── README.md
---

- **Complete_Car_With_Classes/**  
  Contains the Arduino project with classes for:
  - 🚀 **Motor Control**
  - 📏 **Ultrasonic Sensor**
  - 👁️ **Infrared Sensor** (using the [IRremote](https://github.com/z3t0/Arduino-IRremote) library)
  - 🔵 **Bluetooth Communication**

- **React Application (in the root):**  
  - 🖥️ Interactive web interface for controlling the robot.
  - 🎮 Enables control via keyboard or by entering specific parameters (distance, angle, and speed).
  - 🔗 Connects via Bluetooth (requires the experimental feature to be activated in Chromium-based browsers).

---

## ⚙️ Requirements and Dependencies

### For the Arduino Project:
- **Arduino IDE:** Latest version.
- **Library:**  
  - [IRremote](https://github.com/z3t0/Arduino-IRremote) (for the infrared sensor).

### For the React Application:
- **Vite:** Used to configure and build the application.
- **Browser Bluetooth:**  
  The experimental Bluetooth feature in Chromium-based browsers must be activated for proper functionality.

---

## 🌟 Features and Functionality

### Arduino:
- **Motor Control:** Precise management of the robot's movement.
- **Sensors:**
  - **Ultrasonic:** Measures distances to avoid obstacles.
  - **Infrared:** Detects using the *IRremote* library.
- **Bluetooth Communication:** Receives commands for remote control.

### React Application:
- **Interactive Web Interface:** Modern and responsive app to control the robot.
- **Keyboard Control:** Sends commands via key presses.
- **Customizable Parameters:** Set distance, angle, and speed through a form.
- **Experimental Bluetooth:** Connect to the robot by enabling the experimental feature in your browser and using the correct keys defined in the code.

---

## 🔌 Additional Notes

- **Bluetooth Connection:**  
  Ensure the experimental Bluetooth feature is activated in your browser (available in Chromium-based browsers). Then, enter the correct keys specified in the code to establish the connection with the robot.

- **Experimental Project:**  
  This is my first project integrating React and Arduino, full of valuable learning experiences and exciting challenges!

---

## 👤 Author

- **[ALVNF](https://github.com/alvnf)**

---

## 💡 Contributions

Your suggestions and improvements are welcome! If you have ideas to expand or enhance the project, feel free to open an *issue* or submit a *pull request*.

---

Have fun exploring and experimenting with **OnlineCarController**! 🚀
