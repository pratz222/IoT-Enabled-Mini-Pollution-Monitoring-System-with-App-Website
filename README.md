# EcoConnect: IoT-Enabled Mini Pollution Monitoring System

## Overview

**EcoConnect** is an IoT-enabled mini pollution monitoring system designed to provide real-time measurements of air quality and pollution levels. This system integrates various sensors to monitor air quality parameters, delivering data through a user-friendly Android application and a web interface. The compact design allows for portability and easy installation, making it suitable for both indoor and outdoor environments.

## Features

- **Multi-Sensor Integration**: Utilizes:
  - **MQ135 Gas Sensor**: For measuring air quality and detecting harmful gases.
  - **DHT11 Sensor**: For measuring temperature and humidity levels.
  - **BMP280 Pressure Sensor**: For measuring atmospheric pressure.
  
- **Real-Time Data Transmission**: Sensor data is transmitted to Firebase (Realtime Database), enabling real-time updates.

- **User-Friendly Application**: An Android app provides a graphical interface for users to monitor air quality levels, set thresholds, and receive alerts.

- **Alert System**: 
  - **Voice Alerts**: Notifies users through voice alerts when pollution levels exceed safe thresholds.
  - **Visual Alerts**: Changes images and sends alert notifications to inform users of potential health risks.

- **Smart Home Integration**: Easily integrates with smart home devices for enhanced automation and monitoring.

## Hardware Setup

1. **Components Required**:
   - **MQ135 Gas Sensor**: For detecting pollutants.
   - **DHT11 Sensor**: For measuring temperature and humidity.
   - **BMP280 Pressure Sensor**: For measuring atmospheric pressure.
   - **Microcontroller (e.g., ESP32 or Arduino)**: For processing sensor data and transmitting it.
   - **Power Supply**: To power the sensors and microcontroller.
  
2. **Wiring**:
   - Connect the MQ135, DHT11, and BMP280 sensors to the microcontroller following their respective pin configurations.
   - Ensure the power supply is appropriately connected to power the entire setup.

3. **Compact Design**: The hardware setup is designed to fit within the size of an iPod for portability and ease of installation.

## Software Implementation

1. **Firebase Setup**:
   - Create a Firebase project and set up the Realtime Database.
   - Configure database rules for read/write access as needed.

2. **Microcontroller Code**:
   - Write code to read data from the sensors and send it to Firebase.
   - Implement error handling for sensor readings and data transmission.

3. **Android Application**:
   - Develop an Android application that fetches data from Firebase.
   - Design a user interface to display real-time air quality metrics, temperature, humidity, and pressure.

4. **Alert System**:
   - Implement a feature to monitor pollution levels and trigger voice alerts and notifications when thresholds are exceeded.

## Future Enhancements

- **Web Interface**: Develop a web-based dashboard for users to monitor air quality from any device.
- **Data Analytics**: Implement data logging and visualization features to analyze air quality trends over time.
- **Community Integration**: Allow users to contribute data to a larger community network for collaborative pollution monitoring.

				         
![output](https://github.com/pratz222/IoT-Enabled-Mini-Pollution-Monitoring-System-with-App-Website/assets/53640877/e3eeefc8-c3c3-4fe3-961b-9ff5d99b9d34)

![Website_Output](https://github.com/pratz222/IoT-Enabled-Mini-Pollution-Monitoring-System-with-App-Website/assets/53640877/ac822dac-370c-45c3-bf62-abaa2ba6e657)

