# Arduino Keystroke Injection Project

## Usage Instructions

- **Serial Input:** Send commands via the serial monitor:
  - `\1-text`: Assigns "text" to button 1.
  - `\2-text`: Assigns "text" to button 2.
  - `\3-text`: Assigns "text" to button 3.
  - Simple text (without prefix): Defaults to button 1.
  - `\enter`: Sends an Enter keystroke when the button is pressed.
  - `\ctrl-<char>`: Sends Control + the specified character when the button is pressed.

- **Button Pressing:** Connect buttons to digital pins:
  - **Pin 2**: Button 1 (default)
  - **Pin 3**: Button 2
  - **Pin 4**: Button 3
  - Each button is connected between the pin and GND; pull-up is enabled internally in code.

- **Triggering Actions:** When a button is pressed, the board injects the stored text (or command) as keystrokes.

## Available Functions

- **Store Commands:** Assign specific strings or commands to each button using serial input.
- **Special Commands:**
  - `\enter` sends an Enter keystroke.
  - `\ctrl-<char>` sends Control + the specified character.
- **Default Behavior:** If no specific command is assigned, pressing a button will type the stored string.

## Flexibility

- **Single Button Usage:** If you don’t assign commands to buttons (leave additional buttons unused), pressing the primary button (pin 2) will still function as intended.
- **Serial and Button Control:** The system can be operated via serial commands for configuration and via physical button presses for injection.

---

This setup works on any Arduino board that supports USB HID and the Keyboard library, with buttons connected to pins 2, 3, and 4[web:127].
