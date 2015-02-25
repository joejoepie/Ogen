
#include "Ogen.h"

bool Ogen::init(String windowName, int windowWidth, int windowHeight)
{
	root = new Root("", "");

	try
	{
		//Setup resource groups
		ResourceGroupManager *rgm = ResourceGroupManager::getSingletonPtr();
		rgm->addResourceLocation("resource", "FileSystem", "General");

		//Load plugins
		Strings plugins;
		plugins.push_back("RenderSystem_GL_d");
		plugins.push_back("Plugin_ParticleFX_d");
		plugins.push_back("Plugin_CgProgramManager_d");
		plugins.push_back("Plugin_OctreeSceneManager_d");

		Strings::iterator it = plugins.begin();
		for (; it != plugins.end(); it++)
		{
			root->loadPlugin((*it));
		}

		//Set rendersystem
		const RenderSystemList &renderList = root->getAvailableRenderers();
		if (renderList.size() == 0)
		{
			return false;
		}
		root->setRenderSystem(renderList[0]);

		//Create renderwindow
		root->initialise(false);

		window = root->createRenderWindow(windowName, windowWidth, windowHeight, false);

		//Create SceneManager
		sceneMgr = root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");

		//Create camera and viewport
		camera = sceneMgr->createCamera("Camera");
		camera->setPosition(Vector3(0, 60, 60));
		camera->lookAt(Vector3(0, 0, 0));
		camera->setNearClipDistance(5);

		viewport = window->addViewport(camera);
		viewport->setBackgroundColour(ColourValue(0.8f, 0.7f, 0.6f, 1.0f));

		camera->setAspectRatio(Real(viewport->getActualWidth()) / Real(viewport->getActualHeight()));
		viewport->setCamera(camera);

		//Initialize resource groups
		rgm->initialiseAllResourceGroups();

		//Setup timer
		timer = new Timer();
		timer->reset();

		window->setActive(true);
	}
	catch (Ogre::Exception ex)
	{
		Ogre::LogManager::getSingleton().createLog("Error.log", true, true, false);
		LogManager::getSingleton().getDefaultLog()->logMessage(ex.what());
		return false;
	}

		return true;
}

void Ogen::run(RunCallback runCallback)
{
	window->resetStatistics();

	bool shutdown = false;

	double timeSinceLastFrame = 0;
	double startTime = 0;

	while (!shutdown)
	{
		if (window->isClosed())
			shutdown = true;

		Ogre::WindowEventUtilities::messagePump();

		startTime = timer->getMillisecondsCPU();

		runCallback(timeSinceLastFrame);

		root->renderOneFrame();

		timeSinceLastFrame = timer->getMillisecondsCPU() - startTime;
	}
}