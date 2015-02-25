
typedef std::vector<String> Strings;
typedef void(*RunCallback)(double);

class Ogen
{
public:
	bool init(String windowName, int windowWidth, int windowHeight);
	void run(RunCallback runCallback);

private:
	Root* root;
	RenderWindow* window;
	Camera* camera;
	SceneManager* sceneMgr;
	Viewport* viewport;
	RunCallback runCallback;
	Timer* timer;
};