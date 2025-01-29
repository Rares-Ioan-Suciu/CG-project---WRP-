# CG-Project — Weighted Region Problem (WRP)

This repository contains a benchmarking framework used to extract and analyze data for the **Computational Geometry (CG)** class project. The project focuses on solving the **Weighted Region Problem (WRP)** and consists of three main programs:

## 📌 Project Overview

The framework includes three main components:

1️⃣ **Computation Module (C++)**  
   - Performs triangulation using the **CGAL** library.  
   - Computes the shortest path considering different region weights.  
   - Supports multiple discretization methods.  
   - Runs experiments and logs execution time, memory usage, and path distances.

2️⃣ **Visualization Module (Python - Tkinter GUI)**  
   - Provides a user-friendly interface to visualize results.  
   - Allows users to run the C++ module in visualization mode.  
   - Displays shortest paths for different discretization methods.  
   - Enables running experiments and collecting benchmark data.

3️⃣ **Plotting Module (Python - Matplotlib)**  
   - Processes experiment results from CSV files.  
   - Generates up to **12 plots**, comparing:  
     - Number of points vs. shortest path length.  
     - Number of points vs. memory usage.  
     - Number of points vs. execution time.

---
Make sure **CGAL** is installed on your system. I folowed this video [YouTube Guide](https://www.youtube.com/watch?v=5IMibEt5JpY) for setup instructions.
Additonally, you can check out a demo video here: [YouTube Demo](https://www.youtube.com/watch?v=0peJErZZZTw).
