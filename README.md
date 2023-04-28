# Handling-Motion-Sensor-With-ESPNOW
Motion sensors play a crucial role in the functioning of IoT devices as they enable them to detect movement and react accordingly. They have versatile applications, including security systems, energy-efficient lighting, and smart home automation. Motion sensors can trigger actions like turning on lights or sending alerts to a user's phone, making them an essential tool for both convenience and safety. Moreover, they can be combined with other sensors, like temperature and humidity sensors, to build more advanced and responsive IoT systems that can adapt to their surroundings. Overall, motion sensors enhance the capabilities of IoT devices, making them more efficient and effective in their tasks.

The Motion Sensor that we chose for this experiment is Panasonic EKMC160311. The decision is based on the following comparision:

| Motion Sensors | AM312 | AM/BM612 | HC-SR505 | HC-SR501 | EKMC1603111|
| -------------- | ----- | -------- | -------- | -------- | ---------- |
| Max. Distance | 8m | NA | 6m | 10m | 12m |
| 3.3 Volt | Yes | Yes | No | No | Yes |
| Selectable Range | No | Yes | No | Yes | No |
| Minimal On-time (s) | 4.5 | 2.3 | 5 to 15 | 2.5 | Less than 1 |
| Re-trigger time (s) | 8 | 8 | 8 | 8 | Less than 8 |

The Motion Sensor module (depicted below) comprises a Pyroelectric Sensor that produces energy upon exposure to heat. As a result, when a human or an animal body enters the sensor's range, it detects the movement since the body emits heat energy in the form of infrared radiation. The sensor doesn't use any energy for detection; it only operates by sensing energy emitted by other objects. For this reason, it's also known as a Passive Infrared Sensor or PIR Sensor.

![Motion Sensor](https://user-images.githubusercontent.com/11557572/235118671-452e3983-997a-44bd-bd39-786f2398b59a.png)</br>
 _((a) Pyroelectric Sensor along with circuit; (b) Fresnel Lens; (c) Motion Sensor Module; by [Rahul Siyanwal](https://github.com/rsiyanwal))_
 
When a Pyroelectric sensor is in a stable temperature environment, it doesn't produce any voltage. However, it generates a temporary voltage when it is heated or cooled. This is what happens when a Passive Infrared (PIR) sensor detects a temperature change in its field of view. PIR sensors typically have two or four Pyroelectric elements, each detecting a slightly different area. As depicted below, when an object with a different temperature enters the field of view, it is detected by one element first and then another, creating a temperature difference between them. This temperature difference in two or more elements is interpreted as motion. With two elements, the sensor can only detect motion along one plane (up-down or left-right, depending on the orientation of the elements). With four elements, the sensor can detect motion in all directions.
![Motion Sensor 2](https://user-images.githubusercontent.com/11557572/235132286-ee79a1e5-cc10-41f5-bba4-1c15d82f0918.png)</br>
 _(A PIR Sensor detecting a movement using four Pyroelectric Elements; by [Rahul Siyanwal](https://github.com/rsiyanwal))_

Careful mounting of motion sensors is crucial for proper detection of movement. Improper mounting can result in failure to detect movement, as shown below, where mounting the sensor in such a way that the motion is generally in the z-axis may lead to undetected movement. Additionally, if the motion does not cause a change in temperature that can be detected by the Pyroelectric elements, detection may be uncertain. Higher detection zones in the sensor can improve the chances of detecting movement and reduce the risk of missed detections.
![Motion Detection Uncertain](https://user-images.githubusercontent.com/11557572/235132812-514763a3-985f-4a8f-a8cf-db8951bf715e.png)</br>
 _( A PIR Sensor may not detect movement if it is on Z-axis; by [Rahul Siyanwal](https://github.com/rsiyanwal))_

This repository comes with three files:
- [Motion-Detection-Basic.ino](Motion-Detection-Basic.ino): This is a very simple program designed to detect motion using a PIR sensor.
- [Motion Data Sender ESPNOW.ino](https://github.com/rsiyanwal/Handling-Motion-Sensor-With-ESPNOW/blob/b5ca8fd53c560df2fedc9001a19678475b8fd1ff/Motion%20Data%20Sender%20ESPNOW.ino): This code detects motion using a motion sensor and then sends the motion data to a specific MAC address using the ESP-NOW protocol.
- [Motion Data Receiver ESPNOW.ino](https://github.com/rsiyanwal/Handling-Motion-Sensor-With-ESPNOW/blob/6fddce8c957dd676b4904b374b9096bc24ce725b/Motion%20Data%20Receiver%20ESPNOW.ino): This code runs on the receiver node and receives the motion sensor data sent using the ESP-NOW protocol.

The last two codes provide the necessary functionality to send and receive motion sensor data using ESP-NOW protocol.
