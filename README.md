# Ray tracer
This program uses ray tracing concepts to generate images.

## Table of Contents
* [General Info](#general-information)
* [Technologies Used](#technologies-used)
* [Screenshots](#screenshots)
* [Setup](#setup)
* [Acknowledgements](#acknowledgements)
* [License](#license)

## General Information
- images can be of any size
- images contain spheres of different types and sizes
- the program can create images with a custom camera that has a position and look direction
- spheres can have matte, metal, or dielectric material. 
- spheres can have material that emits light.
- spheres can use a texture with solid color, checker pattern, or image.
- the final image is shown on screen by a window created with OpenGL, GLFW, and Dear ImGui
- the program uses parallel std::for_each to generate images faster while analyzing each pixel
- the process of generating image pixel by pixel can be seen on the screen


## Technologies Used
- OpenGL - version 3.0
- GLFW - version 3.3.8
- Glad
- Dear ImGui
- stb_image

## Screenshots
![alt text{caption=some caption}](/img/window_proccess.png)
*Image generation proccess*

![First window example](/img/window.png)
*Example of a final image*

![Another image](/img/window_2.png)
*Another example*

## Setup
All necessary dependencies are already inside the "include" folder. This is a visual studio project. The project was tested with Microsoft Visual Studio 2022 on Windows 11.

## Acknowledgements
- This project was based on a series of books by Peter Shirley, Trevor David Black, and Steve Hollasch, including
[_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html), [_Ray Tracing: The Next Week_](https://raytracing.github.io/books/RayTracingTheNextWeek.html) and [_Ray Tracing: The Rest of Your Life_](https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html).
- Project was also inspired by [Ray tracing series](https://www.youtube.com/playlist?list=PLlrATfBNZ98edc5GshdBtREv5asFW3yXl) from "The Cherno" YouTube channel.

## License
This project is licensed under the terms of the **MIT** license.