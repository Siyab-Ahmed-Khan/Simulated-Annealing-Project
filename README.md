# Simulated Annealing - Delivery Route Optimization 🚚📍

This project demonstrates the implementation of the **Simulated Annealing** algorithm in **C++** to solve a real-world optimization problem: **minimizing the travel distance for a delivery route**.

---

## 📌 Problem Statement

A delivery van must visit 20 addresses placed at random on a 2D map. The goal is to find the **shortest possible route** that visits each location exactly once and returns to the starting point — a variation of the **Traveling Salesman Problem (TSP)**.

---

## 🧠 About Simulated Annealing

Simulated Annealing is a **probabilistic algorithm** inspired by the process of **cooling metal slowly** to remove defects and reach a stable structure.

- It starts with a random solution.
- Makes small changes (neighbors).
- Accepts better solutions, and sometimes worse ones (to avoid local optima).
- Gradually becomes more selective as the system \"cools down\".

---

## 🔧 How It Works (Steps)

1. Generate 20 random coordinates (delivery locations).
2. Start with a random route visiting all locations.
3. In each iteration:
   - Create a neighbor by swapping two points.
   - Accept based on improvement or probability.
4. Slowly decrease temperature.
5. Return the best route found.

---

## 🛠️ Technologies Used

- **Language:** C++  
- **Libraries:** STL (`<vector>`, `<random>`, `<chrono>`, `<cmath>`, etc.)

---

## 🧪 Sample Output

