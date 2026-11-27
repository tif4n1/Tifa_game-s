# 🏎️ CAR RACE sederhana
### A Terminal-Based Arcade Racing Game Built with C++ and Ncurses

<p align="center">
  A lightweight arcade racing game where reflexes, timing, and precision determine how long you survive on the road.
</p>

---

## Overview

**Car Race** is a terminal-based arcade racing game developed in C++ using the Ncurses library. Players control a racing car, navigate through incoming traffic, avoid collisions, and earn points by surviving as long as possible.

Designed to bring an arcade-style gaming experience to the command-line environment, Car Race combines interactive terminal graphics, keyboard-based controls, multiple difficulty levels, and a simple account system.

The project demonstrates how C++ can be used to build interactive, real-time terminal applications beyond conventional command-line programs.

---

## Game Preview

```text
           =================================
                  C A R   R A C E
           =================================

                |        🚘       |
                |                  |
                |                  |
                |   🚗             |
                |                  |
                |          🚙      |
                |                  |
                |       🏎️          |
                |                  |
           =================================
           SCORE: 120       LEVEL: 2
           
           ← →  Move    ESC  Exit
```

> The preview above is conceptual. The actual game uses ASCII car sprites rendered inside the terminal.

---

## Features

| Feature | Description |
|---|---|
| Interactive Main Menu | Navigate through game options using keyboard controls. |
| Login System | Authenticate players using a username and password. |
| Password Reset | Change the account password through the reset menu. |
| Difficulty Selection | Choose from three gameplay difficulty levels. |
| Real-Time Gameplay | Control the player's car while avoiding incoming vehicles. |
| Enemy Traffic | Five enemy cars are generated and move down the road. |
| Collision Detection | Detect collisions between the player's car and enemy vehicles. |
| Scoring System | Earn 10 points whenever an enemy car is successfully passed. |
| Dynamic Game Speed | Gameplay speed changes according to the selected difficulty. |
| Terminal Graphics | Display cars, road boundaries, lane markings, and game information using Ncurses. |

---

## Gameplay

The objective is simple:

- Control your car and avoid incoming traffic.
- Stay on the road.
- Avoid collisions with enemy vehicles.
- Survive as long as possible.
- Earn points by passing enemy cars.
- Challenge yourself by playing at higher difficulty levels.

Each successfully passed enemy vehicle rewards the player with **10 points**.

A collision ends the current run.

---

## Controls

| Key | Action |
|---|---|
| `↑` | Move the player's car upward |
| `↓` | Move the player's car downward |
| `←` | Move the player's car left |
| `→` | Move the player's car right |
| `Enter` | Confirm a menu selection |
| `Esc` | Exit the current gameplay session |

---

## Difficulty Levels

Car Race provides three difficulty settings.

| Level | Name | Game Speed |
|---|---|---|
| Level 1 | Easy / Relaxed | 120 ms |
| Level 2 | Medium | 85 ms |
| Level 3 | Fast | 55 ms |

<sub>Lower delay values produce faster gameplay.</sub>

---

## Getting Started

### Prerequisites

To build and run Car Race, you need:

- A Linux-based operating system or compatible Unix environment
- C++ compiler (G++)
- Ncurses development library
- Terminal with keyboard input support

### Installation

**1. Clone the repository**

```bash
git clone https://github.com/tif4n1/Tifa_game-s.git
```

**2. Navigate to the project directory**

```bash
cd Tifa_game-s
```

**3. Install Ncurses**

Ubuntu / Debian:

```bash
sudo apt update
sudo apt install g++ libncurses-dev
```

**4. Compile the game**

```bash
g++ gamerace.cpp -o car-race -lncurses
```

> Replace `gamerace.cpp` with the actual source filename if it differs.

**5. Run the game**

```bash
./car-race
```

---

## Default Account

The game currently uses a simple built-in account for login.

| Credential | Value |
|---|---|
| Username | `pemain` |
| Password | `1234` |

Players can use the reset password feature from the main menu.

> **Security Note:** The current authentication system is designed for demonstration purposes. Credentials are stored in memory and are not intended for secure production authentication.

---

## Technical Details

| Component | Implementation |
|---|---|
| Programming Language | C++ |
| Terminal Interface | Ncurses |
| Input Handling | Keyboard input |
| Rendering | ASCII-based terminal graphics |
| Randomization | C++ standard library (`rand`, `srand`) |
| Game Loop | Real-time loop with timed input |
| Collision System | Position-based collision checking |
| Platform | Linux / Unix-like terminal environments |

### Core Gameplay Logic

The game follows a continuous loop:

1. Render the game environment.
2. Display the player's car and enemy vehicles.
3. Receive keyboard input.
4. Update the player's position.
5. Move enemy cars.
6. Detect collisions.
7. Update the score.
8. Repeat until the player exits or collides.

---

## Project Structure

```text
Tifa_game-s/
│
├── gamerace.cpp        # Main source code
├── README.md            # Project documentation
└── ...
```

<sub>File names and structure may change as the project evolves.</sub>

---

## Development Roadmap

Planned improvements for future releases:

- [ ] High-score leaderboard and persistent score storage
- [ ] Pause and resume functionality
- [ ] Improved collision detection using bounding boxes
- [ ] Sound effects and gameplay feedback
- [ ] Enhanced terminal interface and visual effects
- [ ] Additional vehicle sprites and obstacles
- [ ] Story mode with progressive challenges
- [ ] Interactive tutorial
- [ ] Persistent user profiles
- [ ] Cross-platform compatibility improvements

---

## Team

Developed as a collaborative programming project.

**Project Team:** Tifa_game-s

| Contributor | Role |
|---|---|
| Team Member 1 | Programming & Development |
| Team Member 2 | Gameplay Design |
| Team Member 3 | Testing & Quality Assurance |
| Team Member 4 | Documentation & Integration |

<sub>Replace the placeholder contributor names and roles with the actual team information.</sub>

---

## Learning Objectives

This project explores the practical implementation of:

- C++ programming fundamentals
- Functions and modular programming
- Arrays and data management
- Conditional statements and loops
- Random number generation
- Keyboard event handling
- Terminal-based graphical interfaces
- Basic game development logic
- Collision detection
- Interactive application design

---

## Contributing

Contributions, ideas, bug reports, and improvements are welcome.

If you would like to improve Car Race:

1. Fork the repository.
2. Create a new branch.
3. Implement your changes.
4. Test your implementation.
5. Submit a pull request.

---

## License

The licensing terms for this project have not yet been specified.

A license may be added to define how the project can be used, modified, and distributed.

---

<p align="center">
  <b>Stay focused. Avoid traffic. Beat your high score.</b>
  
  <br>
  
  Made with C++ and Ncurses.
</p>
