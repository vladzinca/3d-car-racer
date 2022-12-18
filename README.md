# 3D Car Racer

## 🏎️ What is it?

This project is a 3D third-person car racing game made using an OpenGL framework called GFX, available [here](https://github.com/UPB-Graphics/gfx-framework).

I coded it in C++ and GLSL during December 2022 and it was a very rewarding experience.

THe code I wrote can be found in `3d-car-racer/src/lab_m1/Tema2/` and is run using the `main.cpp` found in `3d-car-racer/src/`.

## 🏃 How to run it?

1.  Clone this repository.
2.  Make the build files using CMake, as described [here](https://github.com/UPB-Graphics/gfx-framework).
3.  Open the project using the `GFXFramework.sln` file and run it.
4.  Enjoy!

## 🌳 What does it do?

It basically lets you drive a cyan car using the W, A, S and D keys on a pre-determined racetrack.

However, this is not all.

Alongside you, there are other two other enemy cars that you can compete with, but be careful, as hitting them will ultimately slow you down.

Also of note is that the terrain you find yourself in is virtually complex: along the racetrack there are many trees that give the game a uniquely arcade-ish vibe, and we also have a shader inside the game that I wrote with GLSL that simulates a spherical surface, so it looks like all the racing is taking place on a globe (something along the lines of being an ant on a ball).

## 📝 What did I learn?

This video game was my very first serious attempt at making a game, and considering I only worked on it briefly I was surpised on how many things I got out of it.

The main thing I realized is how simple the math behind a third-person game is. Initially you would think that translating and rotation both the car and the camera at the same time would be very complicated math-wise, and you would not be wrong, as making all the computations necessary would be quite a challenge. But by defining a forward vector to move the car back and forth and rotating it every time a rotation is performed, you can rest assured that the motion of the car will pretty much take care of itself.

Another thing I learned is how important shaders can be for a video game. Sure enough, the game you make can be computationally complex and employ a lot of fancy shapes and mechanics, but making a good yet simple shader can pull a game's graphics forward years into the future.

## 🤔 Did you know?

Because of the way vertex points are moved by the shader, the green plane would normally glitch through the race track in some places, so I designed both of these elements (the race track, and the plane) by using a lot more triangles than you would expect.

In total, more than 2 million triangles are drawn on the screen at every single frame (GPU's really are incredible). Actually, if I got it right, exactly 2,077,958 of them. 😛
