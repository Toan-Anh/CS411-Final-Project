#include "GameManager.h"
#include <ctime>

GameManager* GameManager::instance = nullptr;
bool GameManager::_running = false;

GameManager::GameManager()
{
	_running = false;
}

GameManager::~GameManager()
{
	if (instance != nullptr)
		delete instance;
}

void GameManager::Initialize(int * argcp, char ** argv, int const & win_width, int const & win_height)
{
	// New Instance
	instance = new GameManager();

	// --- Initialize OpenGL and GLUT
	glutInit(argcp, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	// Initialize Window size and position
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - win_width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - win_height) / 2);

	// Create the window
	glutCreateWindow("Bomberman");

	glClearColor(0, 0, 0, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, WIDTH_WINDOW_SCREEN, HEIGHT_WINDOW_SCREEN);
	gluOrtho2D(0, win_width, 0, win_height);

	// --- Event callbacks
	//glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard_handler);
	glutSpecialFunc(special_handler);
	glutCloseFunc(GameManager::Shutdown);

	// --- Load Textures
	TextureManager::Initialize("Texture List.txt");

	SceneManager::AddScene(new Scene_Start());

	// --- Indicate that the game is running
	_running = true;
}

void GameManager::GameLoop(int frame_rate)
{
	long long time_per_frame = 1000 / frame_rate;
	time_t current_time = clock();
	long long t = 0, accumulator = 0;

	while (_running)
	{	
		// update timer
		time_t new_time = clock();
		long long frame_time = new_time - current_time;
		current_time = new_time;

		accumulator += frame_time;

		while (accumulator >= time_per_frame)
		{
			// Glut main loop routine, where event can be caught
			glutMainLoopEvent();
			// Update the scene;
			update(t, time_per_frame);
			// update the time
			accumulator -= time_per_frame;
			t += time_per_frame;

			KeyboardManager::Reset();
		}

		// Draw the scene
		draw();
	}
}

void GameManager::ExitGame()
{
	_running = false;
}

void GameManager::Shutdown()
{
	SceneManager::CleanUp();
}

void GameManager::update(long long const & totalTime, long long const & elapsedTime)
{
	// update the scene
	if (SceneManager::CurrentScene() != nullptr)
		SceneManager::CurrentScene()->Update(totalTime, elapsedTime);
}
void GameManager::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	// draw the scene
	if (SceneManager::CurrentScene() != nullptr)
		SceneManager::CurrentScene()->Draw();
	glutSwapBuffers();
}
void GameManager::keyboard_handler(unsigned char key, int x, int y)
{
	// send information to the current scene to handle
	KeyboardManager::set_key(key);
}
void GameManager::special_handler(int key, int x, int y)
{
	// send information to the current scene to handle
	KeyboardManager::set_special(key);
}
void GameManager::reshape(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}