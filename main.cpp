#include "raylib.h"
#include <vector>




//create a structure for the paddle to define its properties.
struct paddle
{
	float x, y;
	float speed;
	float width, height;

	Rectangle GetDimensions()
	{
		return Rectangle{ x - width / 2, y - height / 2, 10, 100};
	}

	void Draw() 
	{
		DrawRectangle(x-width/2, y-height/2, 10, 100, WHITE);
	}
};


int main()
{
	//build a window of desired dimensions and the window name 
	InitWindow(800, 600, "Two Player Pong");

	//set the x,y coordinates of the ball
	float ball_x = GetScreenWidth() / 2.0f;
	float ball_y = GetScreenHeight() / 2.0f;

	//define the radius of the ball 
	float ball_radius = 7;

	//define variabel for the speed of the ball.
	//this will allow for the speed of the ball to be altered through one step for each instance of speed in the rest of the code
	float ball_speedx = -150;
	float ball_speedy = 150;

	
	//use the paddle structure to create a left player paddle
	paddle left_paddle;
	left_paddle.x = 50;
	left_paddle.y = GetScreenHeight() / 2;
	left_paddle.width = 15;
	left_paddle.height = 110;
	left_paddle.speed = 400;


	//use the paddle structure to create a CPU player paddle
	paddle CPU_paddle;
	CPU_paddle.x = GetScreenWidth() -50;
	CPU_paddle.y = GetScreenHeight() / 2;
	CPU_paddle.width = 15;
	CPU_paddle.height = 110;
	CPU_paddle.speed = 400;


	//create a predefined variable for winner 
	const char* winner_text = nullptr;

	int player_score = 0;
	int CPU_score = 0;



	while (!WindowShouldClose())
	{

		//+= will increment the x,y position of the ball, making it move.
		// multiplying it by the computers frame rate will decide how fast the ball moves. Faster FPS will make the ball move slower
		ball_x += ball_speedx*GetFrameTime();
		ball_y += ball_speedy*GetFrameTime();

		// if the ball reaches the bottom of the window or top, reverse direction of the ball
		if (ball_y > GetScreenHeight() || ball_y < 0)
		{
			ball_speedy *= -1;
		}

		if (CPU_paddle.y + CPU_paddle.height / 2 < ball_y)
		{
			CPU_paddle.y += CPU_paddle.speed * GetFrameTime();
		}
		if (CPU_paddle.y + CPU_paddle.height / 2 > ball_y)
		{
			CPU_paddle.y -= CPU_paddle.speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_UP))
		{
			left_paddle.y -= left_paddle.speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_DOWN))
		{
			left_paddle.y += left_paddle.speed * GetFrameTime();
		}

		if (CheckCollisionCircleRec(Vector2{ ball_x,ball_y }, ball_radius, Rectangle{ left_paddle.GetDimensions() }))
		{
			ball_speedx *= -1;
		}

		if (CheckCollisionCircleRec(Vector2{ ball_x,ball_y }, ball_radius, Rectangle{ CPU_paddle.GetDimensions() }))
		{
			ball_speedx *= -1;
		}

		if (ball_x < 0)
		{
			winner_text = "Right PLayer has Won";
			CPU_score++;
		}

		if (ball_x > GetScreenWidth())
		{
			winner_text = "Left Player has Won ";
			player_score++;
		}

		if (winner_text)
		{
			float ball_x = GetScreenWidth() / 2.0f;
			float ball_y = GetScreenHeight() / 2.0f;
			float ball_speedx = -150;
			float ball_speedy = 150;
			winner_text = nullptr;
		}

		//start the rendering process to draw and implement designs
		BeginDrawing();
			
			//create black background
			ClearBackground(BLACK);

			if (player_score == 3 || CPU_score == 3)
			{
				DrawText(winner_text, GetScreenWidth()/2- MeasureText(winner_text,45)/2, GetScreenHeight() / 2 - 30, 45, RAYWHITE);
			}

			DrawCircle(ball_x, ball_y, ball_radius, WHITE);
			left_paddle.Draw();
			CPU_paddle.Draw();

			DrawText(TextFormat("%i",CPU_score), GetScreenWidth() / 4 - 20, 20, 80, RAYWHITE);
			DrawText(TextFormat("%i",player_score), 3*GetScreenWidth() / 4 - 20, 20, 80, RAYWHITE);

		EndDrawing();
	}

	//close window when game is over or player decides to quit 
	CloseWindow();
	
	return 0;
}