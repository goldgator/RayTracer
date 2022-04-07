// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define SDL_MAIN_HANDLED

#include "Canvas.h"
#include "Image.h"
#include "Sphere.h"
#include "Scene.h"
#include "Plane.h"
#include "Math.h"
#include "Types.h"
#include "Material.h"
#include "Tracer.h"
#include "SDL.h"
#include <iostream>
#include <vector>


int main()
{
	const int width = 1000;
	const int height = 1000;
	const int samples = 50;
	const int depth = 20;

	const int numObjects = 10;
	const int numFrames = 1;
	glm::vec3 eye = glm::vec3{ 0,2,5 };
	glm::vec3 lookAt = glm::vec3{ 0,2,-5 };
	glm::vec3 translate = glm::vec3{ -0.1f,0,-0.1f };
	std::vector<Image*> images;
	

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("2D Renderer", 100, 100, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	Canvas canvas{ renderer, width, height };
	
	Tracer tracer{ samples,depth };
	Scene scene;

	//Creates a random scene
	for (int i = 0; i < numObjects; i++) {
		glm::vec3 color = glm::rgbColor(glm::vec3{ random(0, 360), 1 , 1 });
		glm::vec3 position = glm::vec3{ random(-5,5), random(-5,5), random(-2,-10) };
		float radius = random(0.5f, 1.5f);
		Material* material = nullptr;

		switch (rand() % 3) {
		case 0:
			material = new Lambertian{ color };
			break;
		case 1:
			material = new Metal{ color, random01() };
			break;
		case 2:
			material = new Dielectric{ color, random(0.0f, 4.0f) };
			break;
		}

		scene.Add(new Sphere{ position, radius, material });
	}

	scene.Add(new Plane{ {0,-4,0}, {0,1,0}, new Lambertian{{0.5f,0.5f,0.5f}} });



	for (int i = 0; i < numFrames; i++) {
		Image* image = new Image(width, height);
		Camera camera{ eye, /*eye + */lookAt, glm::vec3{0,1,0}, 80.0f, image };
		tracer.Trace(*image, scene, camera);
		images.push_back(image);

		if (i == numFrames / 2) translate = glm::vec3{ 0.1f,0,-0.1f };

		eye = eye + translate;
		std::cout << "frame: " << i << std::endl;
	}

	
	
	int frame = 0;
	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}

		canvas.Clear({0, 1, 0});
		
		canvas.DrawImage(*images[frame]);
		frame++;
		std::cout << "frameRun: " << frame << std::endl;
		if (frame == numFrames) frame = 0;

		canvas.Update();

		SDL_RenderClear(renderer);
		canvas.Draw(renderer);
		SDL_RenderPresent(renderer);

		
	}

	SDL_Quit();

	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
