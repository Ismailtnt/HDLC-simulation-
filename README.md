# HDLC Protocol Simulator in C

This project is a simple **simulation of the HDLC (High-Level Data Link Control)** protocol written in C, using `pipes` and `fork` to mimic communication between a sender and receiver process.

## 📡 What is HDLC?

HDLC is a **bit-oriented data link layer protocol** developed by ISO. It is widely used for synchronous communication over point-to-point and multipoint links. HDLC defines a framing method that ensures data integrity and synchronization between nodes.

### Key Features of HDLC:

- Frame delimiters (`01111110`) to define boundaries
- Bit stuffing for transparency
- Error detection using FCS (Frame Check Sequence)
- Address and control fields for protocol management

---

## 🎯 Role of this Simulation

This simulation demonstrates:
- Construction of HDLC frames with address, control, data, and FCS fields
- Application of **bit stuffing** for data transparency
- Communication between two processes via `pipe`
- Visualization of sent and received frames

---

## ⚠️ Limitations

- This is a **simplified version** of HDLC — it doesn't simulate real transmission delays or line errors.
- No real CRC (FCS) computation — FCS is simulated with static values.
- Only one direction of communication (unidirectional: sender → receiver)
- Only runs on **Unix/Linux systems** due to usage of `fork()` and `pipe()`. Windows users should use **WSL** or a Linux VM.

---

## 🛠️ How to Compile and Run

### Prerequisites
- GCC Compiler
- Linux/Unix system (or WSL on Windows)

### Compile
```bash
gcc main.c -o hdlc
